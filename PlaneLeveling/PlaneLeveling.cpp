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
#include "State.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"

#define FPS 60
#define GAME_LENGTH_SECONDS 60

GLuint window;
//GLuint width = 1366, height = 768;
GLuint width = 700, height = 600;
GLuint object;
GLfloat start_time_fps;

Game *game;

void display_f() {

	float current_time_fps = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	if (current_time_fps - start_time_fps > 1.0f/FPS) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTranslatef(width / 2.0, height / 2.0, 0);
		float current_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		game->draw(current_time);
		//renderer->draw_plane(current_time, human_force);
		glFlush();
		start_time_fps = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	}
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
	game->get_current_state()->mouse_function(button, state, -1 * (width / 2.0f) + x, -1 * (height / 2.0f) + height - y);
}

void keyboard_f(unsigned char theKey, int X, int Y) {
	game->get_current_state()->keyboard_function(theKey, -1 * (width / 2.0f) + X, -1 * (height / 2.0) + height - Y);
}

void keyboard_up_f(unsigned char theKey, int X, int Y) {
	game->get_current_state()->keyboard_function_up(theKey, -1 * (width / 2.0f) + X, -1 * (height / 2.0) + height - Y);
}

int main(int argc, char *argv[]) {

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);

	window = glutCreateWindow("Plane Leveling");
	//srand(time(NULL));
	srand(5);
	start_time_fps = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	game = new Game(GAME_LENGTH_SECONDS, width, height);
	//temp_play->set_rfa_parameters(MIN_PERIOD, MAX_PERIOD, MIN_AMPLITUDE, MAX_AMPLITUDE);
	//current_state = temp_play;
	//glutFullScreen();
	glutReshapeFunc(reshape_f);
	glutDisplayFunc(display_f);
	glutIdleFunc(display_f);
	glutMouseFunc(mouse_f);
	glutKeyboardFunc(keyboard_f);
	glutKeyboardUpFunc(keyboard_up_f);
	glutMainLoop();

	return 0;
}
