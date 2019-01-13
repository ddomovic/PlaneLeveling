#pragma once

class Renderer {
private:
	int _screen_width;
	int _screen_height;
	float _reference_time;
	class Plane *_plane;
	class Timer *_timer;
	float _points;
public:
	Renderer(int screen_width, int screen_height, class Plane *plane);
	~Renderer();
	float get_reference_time();
	void set_reference_time(float new_reference_time);
	class Plane* get_plane();
	class Timer* get_timer();
	float get_points();
	//calculates random force and plane angle, draws the plane and adjusts reference time
	void draw_plane(float current_time, float human_force);
	void set_points(float points);
};