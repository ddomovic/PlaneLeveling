#pragma once
#include <string>

class Plane {
private:
	float _plane_angle; //current plane angle
	int _plane_size; // wing span
	int _plane_mass; // will probably be removed in the future
	float _angular_velocity;
	std::string _plane_sprite_file;
	RandomForceApplier *_rfa;
public:
	//use this one if there's no plane sprite file, otherwise use the second one
	Plane(int plane_size, int plane_mass, RandomForceApplier *rfa);
	Plane(int plane_size, int plane_mass, RandomForceApplier *rfa, std::string plane_sprite_file);
	//applied forces ->  (force > 0) for tilting to the left, (force < 0) for tilting to the right
	void calculate_plane_angle(float delta_time, float human_force_applied, float random_force_applied);
	void set_plane_size(int plane_size);
	void set_plane_angle(float plane_angle);
	void set_plane_sprite_file(std::string plane_sprite_file);
	void set_random_force_applier(RandomForceApplier *rfa);
	int get_plane_size();
	float get_plane_angle();
	std::string get_plane_sprite_file();
	RandomForceApplier* get_random_force_applier();
};