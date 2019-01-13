#pragma once

#include <vector>

class Game {
private:
	std::vector<class State*> _states;
	int current_state;
	int screen_width;
	int screen_height;
	float game_length;
public:
	Game(float game_length, int width, int height);
	void draw(float current_time);
	void swap_state();
	class State *get_current_state();
	void set_game_length(float game_length);
	float get_game_length();
};