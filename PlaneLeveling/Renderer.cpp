#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include "RandomForceApplier.h"
#include "Plane.h"
#include "Timer.h"
#include "Renderer.h"

Renderer::Renderer(int screen_width, int screen_height, Plane *plane) : _screen_width(screen_width),
		_screen_height(screen_height), _plane(plane), _points(0) {
	this->_reference_time = (float)glutGet(GLUT_ELAPSED_TIME)/1000.0;
	this->_timer = new Timer();
}

Renderer::~Renderer() {
	delete this->_timer;
	delete this->_plane;
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

float Renderer::get_points() {
	return this->_points;
}

//calculates random force and plane angle, draws the plane and adjusts reference time
void Renderer::draw_plane(float current_time, float human_force) {
	float random_force = this->_plane->get_random_force_applier()->calculate_current_force(current_time - this->_reference_time);
	this->_plane->calculate_plane_angle(current_time - this->_reference_time, human_force, random_force);
	this->_plane->set_plane_angle(fmod(this->_plane->get_plane_angle(), 360));
	this->_timer->draw_timer(0.7*this->_screen_width/2.0, 0.5 * this->_screen_height - 40);
	
	if (fabs(this->_plane->get_plane_angle()) > 180.0f) {
		this->_points += (360.0f - fabs(this->_plane->get_plane_angle())) / 60.0f;
	}
	else {
		this->_points += (fabs(this->_plane->get_plane_angle())) / 60.0f;
	}

	glColor3f(1.0, 0.0, 0.0);
	std::string current_points = "ERROR:" + std::to_string(this->_points);
	std::string current_human_force = "FORCE: " + std::to_string(human_force);
	int len = (int)current_points.length();
	glRasterPos2d(-0.7*this->_screen_width / 2.0, 0.5*this->_screen_height - 40.0);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, current_points[i]);
	}
	len = (int)current_human_force.length();
	glRasterPos2d(-0.7*this->_screen_width / 2.0, 0.5*this->_screen_height - 80.0);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, current_human_force[i]);
	}

	glPushMatrix();
	glLineWidth(2.0f);
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
	/*glBegin(GL_LINES);
	glVertex2f(this->_plane->get_plane_size() / 2.0, 0);
	glVertex2f(this->_plane->get_plane_size() / 2.0, 30*random_force);
	glEnd();*/
	glColor3f(1.0, 0.0, 0.0);
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-1 * this->_plane->get_plane_size(), this->_plane->get_plane_size());
	glVertex2f(this->_plane->get_plane_size(), this->_plane->get_plane_size());
	glVertex2f(this->_plane->get_plane_size(), -1 * this->_plane->get_plane_size());
	glVertex2f(-1 * this->_plane->get_plane_size(), -1 * this->_plane->get_plane_size());
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1 * this->_plane->get_plane_size(), 10);
	glVertex2f(-1 * this->_plane->get_plane_size() + 20, 0);
	glVertex2f(-1 * this->_plane->get_plane_size(), -10);

	glVertex2f(this->_plane->get_plane_size(), 10);
	glVertex2f(this->_plane->get_plane_size() - 20, 0);
	glVertex2f(this->_plane->get_plane_size(), -10);

	glVertex2f(-10, this->_plane->get_plane_size());
	glVertex2f(0, this->_plane->get_plane_size() - 20);
	glVertex2f(10, this->_plane->get_plane_size());

	glVertex2f(-10, -this->_plane->get_plane_size());
	glVertex2f(0, -this->_plane->get_plane_size() + 20);
	glVertex2f(10, -this->_plane->get_plane_size());

	glLineWidth(1.0f);
	glEnd();

	this->_reference_time = current_time;
	//this->_reference_time = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0;
}

void Renderer::set_points(float points) {
	this->_points = points;
}
