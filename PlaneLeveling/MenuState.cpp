#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include "Button.h"
#include "Game.h"
#include "State.h"
#include "PlayState.h"
#include "MenuState.h"

MenuState::MenuState(Game *game, int width, int height) : State(game, width, height), _last_score(-1.0f) {
	this->_buttons.push_back(new Button("EASY", -100, 100, 200, 50));
	this->_buttons.push_back(new Button("NORMAL", -100, 0, 200, 50));
	this->_buttons.push_back(new Button("HARD", -100, -100, 200, 50));
	this->_buttons.push_back(new Button("QUIT", -100, -200, 200, 50));
}

MenuState::~MenuState() {
	delete this->_buttons[3];
	delete this->_buttons[2];
	delete this->_buttons[1];
	delete this->_buttons[0];
}

void MenuState::add_button(Button *button) {
	this->_buttons.push_back(button);
}

std::vector<class Button*>& MenuState::get_buttons() {
	return this->_buttons;
}

void MenuState::draw_scene(float current_time) {
	
	for (int i = 0; i < this->_buttons.size(); i++) {
		glColor3f(0.514f, 0.529f, 0.549f);
		glBegin(GL_QUADS);
		glVertex2f(this->_buttons[i]->get_position_X(), this->_buttons[i]->get_position_Y());
		glVertex2f(this->_buttons[i]->get_position_X(), this->_buttons[i]->get_position_Y() + this->_buttons[i]->get_dimension_Y());
		glVertex2f(this->_buttons[i]->get_position_X() + this->_buttons[i]->get_dimension_X(), this->_buttons[i]->get_position_Y() + this->_buttons[i]->get_dimension_Y());
		glVertex2f(this->_buttons[i]->get_position_X() + this->_buttons[i]->get_dimension_X(), this->_buttons[i]->get_position_Y());
		glEnd();
		std::string text = this->_buttons[i]->get_text();
		int len = (int)text.length();
		glColor3f(0.1f, 0.1f, 0.1f);
		glRasterPos2d(this->_buttons[i]->get_position_X() + 4, this->_buttons[i]->get_position_Y() + 4);
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
		}
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	std::string text = "LAST SCORE: ";
	if (this->_last_score < 0) {
		text += "n/a";
	}
	else {
		text += std::to_string(this->_last_score);
	}
	int len = (int)text.length();
	glRasterPos2d(0, this->get_screen_height()/2.0f - 10);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void MenuState::keyboard_function(unsigned char theKey, int X, int Y) {
}

void MenuState::keyboard_function_up(unsigned char theKey, int X, int Y) {
}

void MenuState::mouse_function(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		int pressed_button = -1;
		for (int i = 0; i < this->_buttons.size(); i++) {
			if (x >= this->_buttons[i]->get_position_X() &&
				x <= this->_buttons[i]->get_dimension_X() + this->_buttons[i]->get_position_X() &&
				y >= this->_buttons[i]->get_position_Y() &&
				y <= this->_buttons[i]->get_dimension_Y() + this->_buttons[i]->get_position_Y()) {
				pressed_button = i;
			}
		}
		
		if (pressed_button == -1) {
			return;
		}
		else if (pressed_button == 0) {
			this->_play_state->set_rfa_parameters(EASY_MIN_PERIOD, EASY_MAX_PERIOD, EASY_MIN_AMPLITUDE, EASY_MIN_AMPLITUDE);
			this->_play_state->reset();
			this->get_game()->swap_state();
		}
		else if (pressed_button == 1) {
			this->_play_state->set_rfa_parameters(NORMAL_MIN_PERIOD, NORMAL_MAX_PERIOD, NORMAL_MIN_AMPLITUDE, NORMAL_MIN_AMPLITUDE);
			this->_play_state->reset();
			this->get_game()->swap_state();
		}
		else if (pressed_button == 2) {
			this->_play_state->set_rfa_parameters(HARD_MIN_PERIOD, HARD_MAX_PERIOD, HARD_MIN_AMPLITUDE, HARD_MIN_AMPLITUDE);
			this->_play_state->reset();
			this->get_game()->swap_state();
		}
		else if (pressed_button == 3) {
			exit(0);
		}
	}
}

void MenuState::set_play_state(PlayState *play_state) {
	this->_play_state = play_state;
}

PlayState* MenuState::get_play_state() {
	return this->_play_state;
}

void MenuState::set_last_score(float last_score) {
	this->_last_score = last_score;
}
