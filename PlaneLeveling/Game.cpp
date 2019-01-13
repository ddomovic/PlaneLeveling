#include "pch.h"
#include "State.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"

Game::Game(float game_length, int width, int height) : game_length(game_length), screen_width(width), screen_height(height) {
	PlayState *temp_play = new PlayState(this, width, height);
	MenuState *temp_menu = new MenuState(this, width, height);
	temp_play->set_menu_state(temp_menu);
	temp_menu->set_play_state(temp_play);
	this->_states.push_back(temp_menu);
	this->_states.push_back(temp_play);
}

void Game::draw(float current_time) {
	this->_states[current_state]->draw_scene(current_time);
}

void Game::swap_state() {
	current_state = 1 - current_state;
}

State* Game::get_current_state() {
	return this->_states[current_state];
}

void Game::set_game_length(float game_length) {
	this->game_length = game_length;
}

float Game::get_game_length() {
	return this->game_length;
}
