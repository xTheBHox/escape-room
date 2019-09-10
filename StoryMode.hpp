
/*
 * StoryMode implements a story about The Planet of Choices.
 *
 */

#include "Mode.hpp"
#include "Sprite.hpp"

#include <string>
#include <vector>
#include <unordered_map>

#include <fstream>
#include <sstream>
#include <functional>

struct StoryMode : Mode {
	StoryMode();
	virtual ~StoryMode();

	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//called to create menu for current scene:
	void enter_scene();


  struct Scene {
    struct SceneChoice {
      SceneChoice(std::string const &st, std::string const &next, std::function< bool() > const &pred_, std::function< void() > const &res_) :
        st(st), next_scene(next), pred(pred_), res(res_) { }
      std::string st;
      std::string next_scene;
      std::function< bool() > pred;
      std::function< void() > res;
    };
    std::vector< SceneChoice > choices;
    struct SceneText {
      SceneText(std::string const &st, std::function< bool() > const &pred_) :
        st(st), pred(pred_) { }
      std::string st;
      std::function< bool() > pred;
    };
    std::vector< SceneText > texts;
    struct SceneSprite {
      SceneSprite(Sprite const *sp_, std::function< bool() > const &pred_) :
        sp(sp_), pred(pred_) { }
      Sprite const *sp;
      std::function< bool() > pred;
    };
    std::vector< SceneSprite > sprites;
  };

	//------ story state -------
  std::string location;
	bool have_stone = false;
	bool added_stone = false;
	struct {
		bool first_visit = true;
		bool wont_leave = false;
	} dunes;
	struct {
		bool first_visit = true;
		bool took_stone = false;
	} oasis;
	struct {
		bool first_visit = true;
		bool added_stone = false;
	} hill;

	glm::vec2 view_min = glm::vec2(0,0);
	glm::vec2 view_max = glm::vec2(256, 224);
};
