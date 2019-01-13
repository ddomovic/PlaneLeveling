#pragma once

#include <vector>

#define EASY_MIN_PERIOD 0.5
#define EASY_MAX_PERIOD 1.0
#define EASY_MIN_AMPLITUDE 0.3
#define EASY_MAX_AMPLITUDE 0.5
#define NORMAL_MIN_PERIOD 0.2
#define NORMAL_MAX_PERIOD 0.5
#define NORMAL_MIN_AMPLITUDE 0.5
#define NORMAL_MAX_AMPLITUDE 0.8
#define HARD_MIN_PERIOD 0.2
#define HARD_MAX_PERIOD 0.5
#define HARD_MIN_AMPLITUDE 0.8
#define HARD_MAX_AMPLITUDE 1.5

class MenuState : public State {
private:
	float _last_score;
	std::vector<class Button*> _buttons;
	class PlayState *_play_state;
public:
	MenuState(class Game *game, int width, int height);
	~MenuState();
	void add_button(class Button *button);
	std::vector<class Button*>& get_buttons();
	void draw_scene(float current_time);
	void keyboard_function(unsigned char theKey, int X, int Y);
	void keyboard_function_up(unsigned char theKey, int X, int Y);
	void mouse_function(int button, int state, int x, int y);
	void set_play_state(class PlayState *play_state);
	class PlayState* get_play_state();
	void set_last_score(float last_score);
};