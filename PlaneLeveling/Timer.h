#pragma once

class Timer {
private:
	float _start_time;
public:
	Timer();
	float get_start_time();
	void set_start_time(float time);
	float get_passed_time();
	void draw_timer(int xpos, int ypos);
};