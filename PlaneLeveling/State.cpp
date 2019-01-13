#include "pch.h"
#include "Game.h"
#include "State.h"

State::State(Game *game, int screen_width, int screen_height) : _game(game), screen_width(screen_width), screen_height(screen_height) {
}

int State::get_screen_width() {
	return this->screen_width;
}

int State::get_screen_height() {
	return this->screen_height;
}

Game* State::get_game() {
	return this->_game;
}

void State::set_game(Game *game) {
	this->_game = game;
}
