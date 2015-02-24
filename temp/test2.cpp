/****************************************************************
*  Copyright@2011
*  OpenGL 2D example for CSE328
*  shuchu.han@gmail.com
*  21th-Feb-2011
*  ****************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <GL/glut.h>

/* global variables */
static int win(0);
static int primitive(2); //set to teapot
static int menid(0);

void menu2(int value);

/* menu creation */
void createMenu2(void)
{
	menid = glutCreateMenu(menu2);

	//create an entry
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Teapot", 2);
	glutAddMenuEntry("Cube", 3);
	glutAddMenuEntry("Torus", 4);
	glutAddMenuEntry("Quit", 0);

	//let the menu respnd on the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* menu setting */
void menu2(int value)
{
	if (value == 0){
		//the user clicks "quit"
		glutDestroyWindow(win);
		exit(0);
	}
	else{
		//set the geometric primitive
		primitive = value;
	}

	//redraw the scene
	glutPostRedisplay();
}

/* display */
void disp2(void)
{
	//clean the scene
	glClear(GL_COLOR_BUFFER_BIT);

	//draw objects
	if (primitive == 1){
		// glutPostRedisplay();
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else if (primitive == 2){
		glutWireTeapot(0.5);
	}
	else if (primitive == 3){
		glutWireCube(0.5);
	}
	else if (primitive == 4){
		glutWireTorus(0.3, 0.6, 100, 10);
	}

	//Flush the buffer
	glFlush();
};

/* MAIN */
int main3(int argc, char* argv[])
{
	//step 1. initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	//step 2. Open a window named "GLUT DEMO"
	win = glutCreateWindow("GLUT DEMO");
	glClearColor(0.0, 0.0, 0.0, 0.0); //set background

	//create menu
	createMenu2();

	//step 3. register the display function
	glutDisplayFunc(disp2);

	//step 4. enter the event processing loop
	glutMainLoop();
	return 0;
}
