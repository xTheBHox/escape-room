#include "StoryMode.hpp"

#include "Sprite.hpp"
#include "DrawSprites.hpp"
#include "Load.hpp"
#include "data_path.hpp"
#include "gl_errors.hpp"
#include "MenuMode.hpp"
#include <iostream>

std::unordered_map< std::string, StoryMode::Scene > scenes;
std::unordered_map< std::string, uint32_t > resources;
std::vector< std::vector< std::pair< uint32_t &, bool >>> preds;
std::string init_location = "";
Load< SpriteAtlas > sprites(LoadTagDefault, []() -> SpriteAtlas const * {
  SpriteAtlas const *ret = new SpriteAtlas(data_path("escape-room"));
  std::ifstream scene_data;
  scene_data.open(data_path("escape-room.story"));
  std::string line;
  assert(scene_data.is_open() && "Story file not found");

  enum {
    CONDITIONS,
    SCENE_TITLE,
    SCENE_SPRITES,
    SCENE_TEXT,
    SCENE_CHOICES
  } fsm = CONDITIONS;
  StoryMode::Scene *curr_scene;

  auto parse_pred = [](std::string &csl) -> std::function< bool () > {
    std::istringstream iss(csl);
    std::string tmp;
    preds.emplace_back();
    auto &conditions = preds.back();
    while (std::getline(iss, tmp, ',')) {
      if (tmp[0] == '!') {
        tmp.erase(0, 1);
        conditions.emplace_back(resources.at(tmp), false);
      }
      else {
        conditions.emplace_back(resources.at(tmp), true);
      }
    }
    auto const &conditions_ref = preds.back();
    auto pred_fn = [conditions_ref]() -> bool {
      for (auto &p : conditions_ref) {
        if (p.second && p.first == 0) return false;
        if (!p.second && p.first > 0) return false;
      }
      return true;
    };
    return pred_fn;

  };

  while (std::getline(scene_data, line)) {

    std::cout << line << std::endl;
    switch (fsm) {
      case CONDITIONS: {
        if (line.empty()) {
          fsm = SCENE_TITLE;
          break;
        }
        resources.emplace(line, 0);
        break;
      }
      case SCENE_TITLE: {
        auto current_scene_pair = scenes.emplace(
          std::piecewise_construct,
          std::forward_as_tuple(line),
          std::forward_as_tuple()
        );
        if (init_location.empty()) init_location = line;
        assert(current_scene_pair.second && "Duplicate scene titles");
        curr_scene = &current_scene_pair.first->second;
        fsm = SCENE_SPRITES;
        break;
      }
      case SCENE_SPRITES: {
        if (line.empty()) {
          fsm = SCENE_TEXT;
          break;
        }
        std::istringstream iss(line);
        std::string tok;
        //bool negate;
        std::function< bool() > pred;
        std::getline(iss, tok, '|');
        if (tok.empty()) {
          pred = [](){ return true; };
        }
        else pred = parse_pred(tok);
        std::getline(iss, tok);
        curr_scene->sprites.emplace_back(&ret->lookup(tok), pred);
        break;
      }
      case SCENE_TEXT: {
        if (line.empty()) {
          fsm = SCENE_CHOICES;
          break;
        }
        std::istringstream iss(line);
        std::string tok;
        //bool negate;
        std::function< bool() > pred;
        std::getline(iss, tok, '|');
        if (tok.empty()) {
          pred = [](){ return true; };
        }
        else pred = parse_pred(tok);
        std::getline(iss, tok);
        curr_scene->texts.emplace_back(tok, pred);
        break;
      }

      case SCENE_CHOICES: {
        if (line.empty()) {
          fsm = SCENE_TITLE;
          break;
        }
        std::istringstream iss(line);
        std::string tok, tok1;
        bool negate;
        std::function< bool() > pred;
        std::function< void() > res;
        std::getline(iss, tok, '|');
        if (tok.empty()) {
          pred = [](){ return true; };
        }
        else pred = parse_pred(tok);
        std::getline(iss, tok, '|'); // This is the condition fulfilled
        if (tok.empty()) {
          res = [](){};
        }
        else {
          if (tok[0] == '!') {
            negate = true;
            tok.erase(0, 1);
          }
          else {
            negate = false;
          }
          auto &res_count_ref = resources.at(tok);
          if (!negate) res = [&res_count_ref]() { return res_count_ref++; };
          else res = [&res_count_ref]() { return res_count_ref--; };
        }
        std::getline(iss, tok, '|');
        std::getline(iss, tok1);
        curr_scene->choices.emplace_back(tok1, tok, pred, res);
        break;
      }

    }

  }

	return ret;

});

StoryMode::StoryMode() {
  location = init_location;
}

StoryMode::~StoryMode() {
}

bool StoryMode::handle_event(SDL_Event const &, glm::uvec2 const &window_size) {
	if (Mode::current.get() != this) return false;

	return false;
}

void StoryMode::update(float elapsed) {
	if (Mode::current.get() == this) {
		//there is no menu displayed! Make one:
		enter_scene();
	}
}

void StoryMode::enter_scene() {
	//just entered this scene, adjust flags and build menu as appropriate:
	std::vector< MenuMode::Item > items;
	glm::vec2 at(3.0f, view_max.y - 20.0f);
	auto add_text = [&items, &at](Scene::SceneText const &st) {
		items.emplace_back(st.st, nullptr, 1.0f, nullptr, at);
    at.y -= 14.0f;
		at.y -= 4.0f;
	};
	auto add_choice = [this, &items, &at](Scene::SceneChoice const &st) {
    std::function< void() > modres = [&st, this]() {
      st.res();
      this->location = st.next_scene;
			Mode::current = shared_from_this();
    };
		items.emplace_back(st.st, nullptr, 1.0f, modres, at);
    at.y -= 14.0f;
		at.y -= 4.0f;
	};

  for (Scene::SceneText const &st : scenes.at(location).texts) {
    if (!st.pred()) continue;
    add_text(st);
  }
  at.y -= 4.0f;
  for (Scene::SceneChoice const &st : scenes.at(location).choices) {
    if (!st.pred()) continue;
    add_choice(st);
  }

	std::shared_ptr< MenuMode > menu = std::make_shared< MenuMode >(items);
	// menu->left_select = &sprites->lookup("text-select-left");
	// menu->right_select = &sprites->lookup("text-select-right");
	menu->view_min = view_min;
	menu->view_max = view_max;
	menu->background = shared_from_this();
	Mode::current = menu;
}

void StoryMode::draw(glm::uvec2 const &drawable_size) {
	//clear the color buffer:
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//use alpha blending:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//don't use the depth test:
	glDisable(GL_DEPTH_TEST);

	{ //use a DrawSprites to do the drawing:
		DrawSprites draw(*sprites, view_min, view_max, drawable_size, DrawSprites::AlignPixelPerfect);
		glm::vec2 ul = glm::vec2(view_min.x, view_max.y);
    for (Scene::SceneSprite const &sp : scenes.at(location).sprites) {
      if (sp.pred()) {
        draw.draw(*(sp.sp), ul);
      }
    }
	}
	GL_ERRORS(); //did the DrawSprites do something wrong?
}
