#include "pch.h"
#include <GL/glut.h>
#include <string>
#include "Timer.h"

Timer::Timer() : _start_time((float)glutGet(GLUT_ELAPSED_TIME) / 1000.0) {
}

void Timer::set_start_time(float time) {
	this->_start_time = time;
}

float Timer::get_start_time() {
	return this->_start_time;
}

float Timer::get_passed_time() {
	float temp = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	return temp - this->_start_time;
}

void Timer::draw_timer(int xpos, int ypos) {
	glRasterPos2d(xpos, ypos);
	float time = this->get_passed_time();
	int seconds = (int)(time);
	int centiseconds = (int)(time * 100.0) % 100;
	std::string timer_string = std::to_string(seconds) + ":" ;
	if (centiseconds < 10) {
		timer_string += "0";
	}
	timer_string += std::to_string(centiseconds);
	int len = (int)timer_string.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, timer_string[i]);
	}
}