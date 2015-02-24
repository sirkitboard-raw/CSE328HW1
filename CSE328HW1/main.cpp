/*
*	Made by Aditya balwani
*	SBUID : 109353920
*/

#include "stdafx.h"
#include "main.h"
#include "vertex.h"
#include "polygon.h"
#include "lineFunctions.h"

Polygon temp;
std::vector<Polygon> polyList;

void mousefunc(int button, int state, int x, int y) {
	mouse_x = (x*2.0) / win_width - 1.0;
	mouse_y = 1.0 - (y*2.0) / win_height;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		temp.vertices.push_back(Vertex(mouse_x, mouse_y));
		if (temp.polyComplete) {
			temp.checkSimple();
		}
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		temp.polyComplete = true;
		temp.checkSimple();
		polyList.push_back(temp);
		temp.clear();
		glutPostRedisplay();
	}
}

void keyboardfunc(unsigned char key, int x, int y) {
	if (key == 'c') {
		temp.vertices.clear();
		temp.polyComplete = false;
		glutPostRedisplay();
	}
	if (key == 'r') {
		int rotateAngle;
		cout << "Enter rotation angle in degrees : ";
		cin >> rotateAngle;
		rotate(rotateAngle);
	}
	else if (key == 's') {
		int scaleFactor;
		cout << "Enter scale factor in percentage : ";
		cin >> scaleFactor;
		scale(scaleFactor);
	}
	else if (key == 'e') {
		reflect();
	}
	else if (key == 'h') {
		int shearFactor;
		cout << "Enter the horizontal shear factor : ";
		cin >> shearFactor;
		shear(shearFactor,'h');
	}
	else if (key == 'v') {
		int shearFactor;
		cout << "Enter the vertical shear factor : ";
		cin >> shearFactor;
		shear(shearFactor, 'v');
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	temp.draw();
	for (int i = 0; i < polyList.size();i++) {
		polyList[i].draw();
	}
	glFlush();
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_MULTISAMPLE);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(100, 100);

	win = glutCreateWindow("Homework 1");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glutMouseFunc(mousefunc);
	glutKeyboardFunc(keyboardfunc);
	glDisable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	glutReshapeFunc(windowSizeResize);

	glutMainLoop();
	return 0;
}