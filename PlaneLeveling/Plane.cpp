#include "pch.h"
#include "RandomForceApplier.h"
#include "Plane.h"

Plane::Plane(int plane_size, int plane_mass, RandomForceApplier *rfa) : _plane_angle(0), _plane_size(plane_size), _plane_mass(plane_mass), 
			_angular_velocity(0), _rfa(rfa), _plane_sprite_file("") {
}

Plane::Plane(int plane_size, int plane_mass, RandomForceApplier *rfa, std::string plane_sprite_file) : _plane_angle(0), _plane_size(plane_size), 
			_plane_mass(plane_mass), _angular_velocity(0), _rfa(rfa), _plane_sprite_file(plane_sprite_file) {
}

//applied forces ->  (force > 0) for tilting to the left, (force < 0) for tilting to the right
void Plane::calculate_plane_angle(float delta_time, float human_force_applied, float random_force_applied) {
	float angular_acceleration = (human_force_applied + random_force_applied) * this->_plane_size/2.0;
	this->_plane_angle += this->_angular_velocity*delta_time + 0.5 * angular_acceleration * pow(delta_time, 2);
	this->_angular_velocity += angular_acceleration * delta_time;
}

void Plane::set_plane_size(int plane_size) {
	this->_plane_size = plane_size;
}
void Plane::set_plane_angle(float plane_angle) {
	this->_plane_angle = plane_angle;
}
void Plane::set_plane_sprite_file(std::string plane_sprite_file) {
	this->_plane_sprite_file = plane_sprite_file;
}
void Plane::set_random_force_applier(RandomForceApplier * rfa){
	this->_rfa = rfa;
}

int Plane::get_plane_size() {
	return this->_plane_size;
}
float Plane::get_plane_angle() {
	return this->_plane_angle;
}
std::string Plane::get_plane_sprite_file() {
	return this->_plane_sprite_file;
}

RandomForceApplier * Plane::get_random_force_applier() {
	return this->_rfa;
}
