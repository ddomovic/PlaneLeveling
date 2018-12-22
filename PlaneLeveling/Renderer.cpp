#include "pch.h"
#include <GL/glut.h>
#include "RandomForceApplier.h"
#include "Plane.h"
#include "Timer.h"
#include "Renderer.h"

Renderer::Renderer(int screen_width, int screen_height, Plane *plane) : _screen_width(screen_width),
		_screen_height(screen_height), _plane(plane) {
	this->_reference_time = (float)glutGet(GLUT_ELAPSED_TIME)/1000.0;
	this->_timer = new Timer();
}

float Renderer::get_reference_time() {
	return this->_reference_time;
}

void Renderer::set_reference_time(float new_reference_time) {
	this->_reference_time = new_reference_time;
}

Plane* Renderer::get_plane() {
	return this->_plane;
}

Timer* Renderer::get_timer() {
	return this->_timer;
}

//calculates random force and plane angle, draws the plane and adjusts reference time
void Renderer::draw_plane(float current_time, float human_force) {
	float random_force = this->_plane->get_random_force_applier()->calculate_current_force(current_time - this->_reference_time);
	this->_plane->calculate_plane_angle(current_time - this->_reference_time, human_force, random_force);
	this->_timer->draw_timer(0.7*this->_screen_width/2.0, 0.5*this->_screen_height/2.0);
	std::string current_human_force = "FORCE:" + std::to_string(human_force);
	int len = (int)current_human_force.length();
	glRasterPos2d(-0.7*this->_screen_width / 2.0, 0.5*this->_screen_height / 2.0);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, current_human_force[i]);
	}
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(this->_plane->get_plane_angle(), 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-1 * this->_plane->get_plane_size()/2.0, 0);
	glVertex2f(this->_plane->get_plane_size()/2.0, 0);
	glVertex2f(this->_plane->get_plane_size() / 20.0, 0);
	glVertex2f(0, sqrt(2) * this->_plane->get_plane_size() / 20.0);
	glVertex2f(-1 * this->_plane->get_plane_size() / 20.0, 0);
	glVertex2f(0, sqrt(2) * this->_plane->get_plane_size() / 20.0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(this->_plane->get_plane_size() / 2.0, 0);
	glVertex2f(this->_plane->get_plane_size() / 2.0, 30*random_force);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glPopMatrix();
	this->_reference_time = current_time;
	//this->_reference_time = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0;
}