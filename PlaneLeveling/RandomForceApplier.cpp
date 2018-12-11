#include "pch.h"
#include <GL/glut.h>
#include <cmath>
#include "RandomForceApplier.h"

RandomForceApplier::RandomForceApplier(float min_period, float max_period, float min_amplitude, float max_amplitude) : 
	_min_period(min_period), _max_period(max_period), _min_amplitude(min_amplitude), 
	_max_amplitude(max_amplitude), _passed_time(max_period + 1) {
	this->_reference_time = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
}

float RandomForceApplier::calculate_current_force(float delta_time) {
	this->_passed_time += delta_time;
	if (this->_passed_time > this->_current_period) {
		this->_current_amplitude = this->_min_amplitude + static_cast<float> (rand() * (this->_max_amplitude - this->_min_amplitude)) / (static_cast<float> (RAND_MAX));
		this->_current_period = this->_min_period + static_cast<float> (rand() * (this->_max_period - this->_min_period)) / (static_cast<float> (RAND_MAX));
		this->_passed_time = 0;
	}
	return this->_current_amplitude * sin((2*PI/this->_current_period) * this->_passed_time);
}

float RandomForceApplier::get_min_period() {
	return this->_min_period;
}

float RandomForceApplier::get_max_period() {
	return this->_max_period;
}

float RandomForceApplier::get_min_amplitude() {
	return this->_min_amplitude;
}

float RandomForceApplier::get_max_amplitude() {
	return this->_max_amplitude;
}

float RandomForceApplier::get_current_period() {
	return this->_current_period;
}

float RandomForceApplier::get_current_amplitude() {
	return this->_current_amplitude;
}

float RandomForceApplier::get_reference_time() {
	return this->_reference_time;
}

float RandomForceApplier::get_passed_time() {
	return this->_passed_time;
}

void RandomForceApplier::set_min_period(float min_period) {
	this->_min_period = min_period;
}

void RandomForceApplier::set_max_period(float max_period) {
	this->_max_period = max_period;
}

void RandomForceApplier::set_min_amplitude(float min_amplitude) {
	this->_min_amplitude = min_amplitude;
}

void RandomForceApplier::set_max_amplitude(float max_amplitude) {
	this->_max_amplitude = max_amplitude;
}

void RandomForceApplier::set_current_period(float current_period) {
	this->_current_period = current_period;
}

void RandomForceApplier::set_current_amplitude(float current_amplitude) {
	this->_current_amplitude = current_amplitude;
}

void RandomForceApplier::set_reference_time(float reference_time) {
	this->_reference_time = reference_time;
}

void RandomForceApplier::set_passed_time(float passed_time) {
	this->_passed_time = passed_time;
}

void RandomForceApplier::add_passed_time(float delta_time) {
	this->_passed_time += delta_time;
}
