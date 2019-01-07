#pragma once

class Renderer {
private:
	int _screen_width;
	int _screen_height;
	float _reference_time;
	Plane *_plane;
	class Timer *_timer;
	float _points;
public:
	Renderer(int screen_width, int screen_height, Plane *plane);
	float get_reference_time();
	void set_reference_time(float new_reference_time);
	Plane* get_plane();
	Timer* get_timer();
	//calculates random force and plane angle, draws the plane and adjusts reference time
	void draw_plane(float current_time, float human_force);
};