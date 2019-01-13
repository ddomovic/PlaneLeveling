#pragma once

class PlayState : public State {
private:
	float _human_force;
	bool _a_pressed;
	bool _d_pressed;
	class Renderer *_renderer;
	class MenuState *_menu_state;
public:
	PlayState(class Game *game, int width, int height);
	~PlayState();
	void draw_scene(float current_time);
	void keyboard_function(unsigned char theKey, int X, int Y);
	void keyboard_function_up(unsigned char theKey, int X, int Y);
	void mouse_function(int button, int state, int x, int y);
	void set_rfa_parameters(float min_period, float max_period, float min_amplitude, float max_amplitude);
	class MenuState* get_menu_state();
	void set_menu_state(class MenuState *state);
	void reset();
};