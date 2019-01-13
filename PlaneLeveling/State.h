#pragma once

class State {
private:
	int screen_width;
	int screen_height;
	class Game *_game;
public:
	State(class Game *game, int screen_width, int screen_height);
	virtual void draw_scene(float current_time) = 0;
	virtual void keyboard_function(unsigned char theKey, int X, int Y) = 0;
	virtual void keyboard_function_up(unsigned char theKey, int X, int Y) = 0;
	virtual void mouse_function(int button, int state, int x, int y) = 0;
	int get_screen_width();
	int get_screen_height();
	class Game* get_game();
	void set_game(class Game *game);
};