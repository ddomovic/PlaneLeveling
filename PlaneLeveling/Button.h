#pragma once

#include <string>

class Button {
private:
	float _pos_X;
	float _pos_Y;
	float _dim_X;
	float _dim_Y;
	std::string _text;
public:
	Button(const std::string &text, float position_X, float position_Y, float dimension_X, float dimension_Y);
	float get_position_X();
	float get_position_Y();
	float get_dimension_X();
	float get_dimension_Y();
	const std::string& get_text();
	void set_position_X(float position_X);
	void set_position_Y(float position_Y);
	void set_dimension_X(float dimension_X);
	void set_dimension_Y(float dimension_Y);
	void set_text(const std::string &text);
};