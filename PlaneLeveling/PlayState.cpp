#include "pch.h"
#include <GL/glut.h>
#include "Renderer.h"
#include "RandomForceApplier.h"
#include "Plane.h"
#include "Game.h"
#include "Timer.h"
#include "State.h"
#include "MenuState.h"
#include "PlayState.h"

PlayState::PlayState(Game *game, int width, int height) : State(game, width, height), 
	_human_force(0.0f), _a_pressed(false), _d_pressed(false) {
	this->_renderer = new Renderer(width, height, new Plane(200, 1, new RandomForceApplier(0, 0, 0, 0)));
}

PlayState::~PlayState() {
	delete this->_renderer;
}

void PlayState::draw_scene(float current_time) {
	_renderer->draw_plane(current_time, this->_human_force);
	if (_renderer->get_timer()->get_passed_time() > this->get_game()->get_game_length()) {
		this->_menu_state->set_last_score(_renderer->get_points());
		this->get_game()->swap_state();
	}
}

void PlayState::keyboard_function(unsigned char theKey, int X, int Y) {
	switch (theKey) {
	case 'a':
		this->_human_force = 1;
		this->_a_pressed = true;
		break;
	case 'd':
		this->_human_force = -1;
		this->_d_pressed = true;
		break;
	}
}

void PlayState::keyboard_function_up(unsigned char theKey, int X, int Y) {
	switch (theKey) {
	case 'a':
		this->_a_pressed = false;
		if (!this->_d_pressed) {
			this->_human_force = 0;
		}
		else {
			this->_human_force = -1;
		}
		break;
	case 'd':
		this->_d_pressed = false;
		if (!this->_a_pressed) {
			this->_human_force = 0;
		}
		else {
			this->_human_force = 1;
		}
		break;
	}
}

void PlayState::mouse_function(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		//reshape_f(width, height);
		//glFlush();
	}
}

void PlayState::set_rfa_parameters(float min_period, float max_period, float min_amplitude, float max_amplitude) {
	this->_renderer->get_plane()->get_random_force_applier()->set_min_period(min_period);
	this->_renderer->get_plane()->get_random_force_applier()->set_max_period(max_period);
	this->_renderer->get_plane()->get_random_force_applier()->set_min_amplitude(min_amplitude);
	this->_renderer->get_plane()->get_random_force_applier()->set_max_amplitude(max_amplitude);
}

MenuState* PlayState::get_menu_state() {
	return this->_menu_state;
}

void PlayState::set_menu_state(MenuState *state) {
	this->_menu_state = state;
}

void PlayState::reset() {
	this->_renderer->get_plane()->set_plane_angle(0.0f);
	this->_renderer->get_plane()->set_plane_angular_velocity(0.0f);
	this->_renderer->get_timer()->set_start_time((float)glutGet(GLUT_ELAPSED_TIME) / 1000.0);
	this->_renderer->get_plane()->get_random_force_applier()->set_reference_time((float)glutGet(GLUT_ELAPSED_TIME) / 1000.0);
	this->_renderer->get_plane()->get_random_force_applier()->set_passed_time(this->_renderer->get_plane()->get_random_force_applier()->get_max_period() + 1);
	this->_renderer->set_points(0.0f);
	this->_renderer->set_reference_time((float)glutGet(GLUT_ELAPSED_TIME) / 1000.0);
	this->_human_force = 0.0f;
	this->_a_pressed = false;
	this->_d_pressed = false;
	srand(5);
}
