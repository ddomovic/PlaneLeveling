#pragma once

class Renderer {
private:
	float _reference_time;
	Plane *_plane;
public:
	Renderer(Plane *plane);
	float get_reference_time();
	void set_reference_time(float new_reference_time);
	Plane* get_plane();
	//calculates random force and plane angle, draws the plane and adjusts reference time
	void draw_plane(float current_time, float human_force);
};