#include "pch.h"
#include "Button.h"

Button::Button(const std::string &text, float position_X, float position_Y, float dimension_X, float dimension_Y) {
	this->_pos_X = position_X;
	this->_pos_Y = position_Y;
	this->_dim_X = dimension_X;
	this->_dim_Y = dimension_Y;
	this->_text = text;
}

float Button::get_position_X() {
	return this->_pos_X;
}

float Button::get_position_Y() {
	return this->_pos_Y;
}

float Button::get_dimension_X() {
	return this->_dim_X;
}

float Button::get_dimension_Y() {
	return this->_dim_Y;
}

const std::string & Button::get_text() {
	return this->_text;
}

void Button::set_position_X(float position_X) {
	this->_pos_X = position_X;
}

void Button::set_position_Y(float position_Y) {
	this->_pos_Y = position_Y;
}

void Button::set_dimension_X(float dimension_X) {
	this->_dim_X = dimension_X;
}

void Button::set_dimension_Y(float dimension_Y) {
	this->_dim_Y = dimension_Y;
}

void Button::set_text(const std::string &text) {
	this->_text = text;
}
