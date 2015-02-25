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
Vertex* selected;
Polygon* selectedPoly;

void mousefunc(int button, int state, int x, int y) {
	mouse_x = (x*2.0) / win_width - 1.0;
	mouse_y = 1.0 - (y*2.0) / win_height;
	if (mouseMode == 1){
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
	if (mouseMode == 2) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			leftButtonState = 1;
			for (int j = 0; j < polyList.size(); j++) {
				for (int i = 0; i < polyList[j].vertices.size(); i++) {
					if (polyList[j].vertices[i].clicked(mouse_x, mouse_y)) {
						cout << "CLICKED!";
						selected = &(polyList[j].vertices[i]);
						selectedPoly = &polyList[j];
					}
				}
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			leftButtonState = 0;
		}
	}
}

void mouseMoveFunc(int x, int y) {
	if (leftButtonState == 1) {
		float mouse_x = (x*2.0) / win_width - 1.0;
		float mouse_y = 1.0 - (y*2.0) / win_height;
		selected->x = mouse_x;
		selected->y = mouse_y;
		selectedPoly->checkSimple();
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
	else if (key == 'f') {
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
	else if (key == 'e') {
		temp.clear();
		mouseMode = 2;
		glutPostRedisplay();
	}
	else if (key == 'd') {
		temp.clear();
		mouseMode = 1;
		glutPostRedisplay();
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
	if (mouseMode == 2) {
		for (int j = 0; j < polyList.size(); j++) {
			for (int i = 0; i < polyList[j].vertices.size(); i++) {
				polyList[j].vertices[i].drawHandle();
			}
		}
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
	glutMotionFunc(mouseMoveFunc);
	glutKeyboardFunc(keyboardfunc);
	glDisable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	glutReshapeFunc(windowSizeResize);

	glutMainLoop();
	return 0;
}