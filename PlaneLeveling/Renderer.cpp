#include "pch.h"
#include <GL/glut.h>
#include "RandomForceApplier.h"
#include "Plane.h"
#include "Renderer.h"

Renderer::Renderer(Plane *plane) : _plane(plane) {
	this->_reference_time = (float)glutGet(GLUT_ELAPSED_TIME)/1000.0;
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

void Renderer::draw_plane(float current_time, float human_force) {
	float random_force = this->_plane->get_random_force_applier()->calculate_current_force(current_time - this->_reference_time);
	this->_plane->calculate_plane_angle(current_time - this->_reference_time, human_force, random_force);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(this->_plane->get_plane_angle(), 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-1 * this->_plane->get_plane_size()/2.0, 0);
	glVertex2f(this->_plane->get_plane_size()/2.0, 0);
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