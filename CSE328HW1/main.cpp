/*
*	Made by Aditya balwani
*	SBUID : 109353920
*/

#include "stdafx.h"
#include "GL/glut.h"

static int win(0);
static int menu_id(0);
static int win_width(600), win_height(600);
static int mouse_x(0.0), mouse_y(0.0);
static int mouseMode(-1);

void display(){

}

void windowSizeResize(int w, int h) {
	win_height = h;
	win_width = w;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(100, 100);

	win = glutCreateWindow("Homework 1");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	glDisable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	glutReshapeFunc(windowSizeResize);

	glutMainLoop();
}