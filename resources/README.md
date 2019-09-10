# The .story file format

The story file is a text file used to describe sprites to draw and actions to take in a text adventure game.
The story file is broken up into two major sections:

Conditions_List
<blank_line>
Scene_List

The Conditions_List section is simply a line-separated list of names of integer variables.
These variables can be incremented/decremented when the user picks options.
Sprites, text and choices can be conditioned to appear if selected variables are zero/non-zero.

The Scene_List section is a line-separated list of scenes. Each scene is further broken down into four parts
in the following format:

Name
Sprite_List
<blank_line>
Text_List
<blank_line>
Choice_List

Name is the name of the scene. Unique names only please.
Sprite_List is a line-separated list of possibly-conditional sprites, drawn in order from frist to last.
Each sprite is defined as such:

conditions|Sprite_Name

Text_List is a line-separated list of scene text, in order. Each line of text is written in the following
format:

conditions|Text

Choice_List is a line-separated list of player-selectable choices, in order. Each is in the following format:

conditions|modify_var|next_scene|Text

conditions is a comma-separated list of variables defined in Conditions_List. For the sprite, text or choice
to appear, all conditions in the comma-separated list must be satisfied (big AND). A variable is satisfied if
its value is greater than 0. You can also negate a variable so it is satisfied if the variable's value is zero.
Negation is done by placing an exclaimation point before the variable name in the comma-separated list. (Note:
to use OR, just make two choices with the same text.)

modify_var is the variable to modify when the choice is selected. The variable listed is incremented by 1. To
decrement instead, place an exclaimation point before the variable name

next_scene is the name of the scene to load when the player selects the choice. This could be the name of
the current screen.