/****************************************************************
*  Copyright@2011
*
* example of world coordiantes and screen pixel cooridnates for CSE328;
*
* This program project the Quad area :
*      -- bottom left (-1.0,-1.0)
*      -- top right (1.0,1.0)
* to the screen (GLUT window);
*
* make you Math operations in world coordinate
*
* get you mouse position from screen(pixel coordinates)
* and transform it into world coordinate. In this program,
* we do this transform by our own code. (OpenGL libs has gluUnproject()
* function to do this).
*
* shuchu.han@gmail.com
*  26th-Feb-2011
****************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <GL/glut.h>

/* global variables */
static int win(0); // GLUT window ID
static int menuid(0);
int primitive;

static int win_width(600), win_height(600); // window's width and height
static float mouse_x(0.0), mouse_y(0.0);

void menu(int value)
{
	if (value == 0)
	{
		glutDestroyMenu(win);
	}
	else
	{
		primitive = value;
	}
	glutPostRedisplay();
}

void createMenu()
{
	menuid = glutCreateMenu(menu);
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Teapot", 2);
	glutAddMenuEntry("Cube", 3);
	glutAddMenuEntry("Torus", 4);
	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void disp()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (primitive == 1)
	{
		glutPostRedisplay();
	}
	else if (primitive == 2)
	{
		glutWireTeapot(0.5);
	}
	else if (primitive == 3)
	{
		glutWireCube(0.5);
	}
	else if (primitive == 4)
	{
		glutWireTorus(0.3, 0.6, 100, 100);
	}

	glFlush();
}

/* MAIN */
int main2(int argc, char* argv[])
{
	//step 1. initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(100, 100);

	//step 2. Open a window named "GLUT DEMO"
	win = glutCreateWindow("GLUT DEMO");
	glClearColor(0.0, 0.0, 0.0, 0.0); //set background

	createMenu();

	glutDisplayFunc(disp);
	//step 4. enter the event processing loop
	glutMainLoop();
	return 0;
}


