// PlaneLeveling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/glut.h>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef _WIN64
#include <windows.h>
#endif
#ifdef _unix
#include <unistd.h>
#endif
#include "RandomForceApplier.h"
#include "Plane.h"
#include "Renderer.h"

#define MIN_PERIOD 1.5
#define MAX_PERIOD 2.5
#define MIN_AMPLITUDE 0.5
#define MAX_AMPLITUDE 1.1

GLuint window;
//GLuint width = 1366, height = 768;
GLuint width = 500, height = 400;
GLuint object;

Renderer *renderer;
float human_force = 0;

void display_f() {

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(width/2.0, height/2.0, 0);
	glBegin(GL_LINES);
	glVertex2f((-1) * renderer->get_plane()->get_plane_size()/4.0, 50);
	glVertex2f((-1) * renderer->get_plane()->get_plane_size()/4.0, -50);
	glVertex2f(renderer->get_plane()->get_plane_size()/4.0, 50);
	glVertex2f(renderer->get_plane()->get_plane_size()/4.0, -50);
	glEnd();
	float current_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	renderer->draw_plane(current_time, human_force);
	glFlush();
}

void reshape_f(int w, int h) {

	width = w;
	height = h;

	//glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	//glOrtho(0, width, 0, height, -1000, 1024);
	//gluPerspective(45.0f, ((double)width/height), 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glColor3f(0.0f, 0.0f, 0.0f);

}

void mouse_f(int button, int state, int x, int y) {

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		//reshape_f(width, height);
		//glFlush();
	}
}

void keyboard_f(unsigned char theKey, int mouseX, int mouseY) {
	switch (theKey) {
	case 'a':
		human_force += 0.5;
		break;
	case 'd':
		human_force -= 0.5;
		break;
	}
}

int main(int argc, char *argv[]) {

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);

	window = glutCreateWindow("Plane Leveling");
	srand(time(NULL));
	RandomForceApplier *rfa = new RandomForceApplier(MIN_PERIOD, MAX_PERIOD, MIN_AMPLITUDE, MAX_AMPLITUDE);
	Plane *plane = new Plane(200, 1, rfa);
	renderer = new Renderer(width, height, plane);
	//glutFullScreen();
	glutReshapeFunc(reshape_f);
	glutDisplayFunc(display_f);
	glutIdleFunc(display_f);
	glutMouseFunc(mouse_f);
	glutKeyboardFunc(keyboard_f);
	glutMainLoop();

	return 0;
}
