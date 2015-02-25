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
Polygon* selectedPoly, *poly1, *poly2;
std::vector<Vertex*> vertList1, vertList2;

static bool morphing = false;
static int FPS = 16;
std::vector<float> increments;
static int animationCounter;


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

	if (mouseMode == 3) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			for (int j = 0; j < polyList.size(); j++) {
				for (int i = 0; i < polyList[j].vertices.size(); i++) {
					if (polyList[j].vertices[i].clicked(mouse_x, mouse_y)) {
						if (vertList1.empty()) {
							poly1 = &polyList[j];
							vertList1.push_back(&polyList[j].vertices[i]);
							polyList[j].vertices[i].clickable = false;
							selected = &polyList[j].vertices[i];
						}
						else {
							if (poly1 == &polyList[j]) {
								vertList1.push_back(&polyList[j].vertices[i]);
								polyList[j].vertices[i].clickable = false;
								selected = &polyList[j].vertices[i];
							}
							else if (poly2 == &polyList[j]){
								vertList2.push_back(&polyList[j].vertices[i]);
								polyList[j].vertices[i].clickable = false;
								selected = &polyList[j].vertices[i];
							}
						}
					}
				}
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			for (int j = 0; j < polyList.size(); j++) {
				for (int i = 0; i < polyList[j].vertices.size(); i++) {
					if (polyList[j].vertices[i].clicked(mouse_x, mouse_y)) {
						if (!vertList1.empty() && vertList2.empty()) {
							poly2 = &polyList[j];
							if (poly2 != poly1 && (poly2->vertices.size() == poly1->vertices.size())) {
								vertList2.push_back(&polyList[j].vertices[i]);
								polyList[j].vertices[i].clickable = false;
								
							}
							else {
								selected->clickable = true;
								vertList1.clear();
							}
						}
						else {
							if (vertList1.size() > vertList2.size()) {
								if (poly2 == &polyList[j]) {
									vertList2.push_back(&polyList[j].vertices[i]);
									polyList[j].vertices[i].clickable = false;
								}
								else {
									selected->clickable = true;
									vertList2.pop_back();
								}
							}
							else if (vertList1.size() < vertList2.size()) {
								if (poly1 == &polyList[j]) {
									vertList1.push_back(&polyList[j].vertices[i]);
									polyList[j].vertices[i].clickable = false;
								}
								else {
									selected->clickable = true;
									vertList2.pop_back();
								}
							}
						}
					}
				}
			}
			glutPostRedisplay();
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

void calculateIncrement() {
	for (int i = 0; i < vertList1.size(); i++) {
		float dist = vertList2[i]->y - vertList1[i]->y;
		increments.push_back(dist / 48.0);
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
	else if (key == 'm') {
		if (polyList.size() <= 1) {
			cout << "You need 2 or more polygons to morph\n";
		}
		else if (mouseMode == 3) {
			if (vertList1.size() == poly1->vertices.size()) {
				calculateIncrement();
				animationCounter = 0;
				morphing = true;
			}
			else {
				cout << "Not enough nodes selected\n";
			}
		}
		else {
			mouseMode = 3;
		}
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
	if (mouseMode >=2) {
		for (int j = 0; j < polyList.size(); j++) {
			for (int i = 0; i < polyList[j].vertices.size(); i++) {
				polyList[j].vertices[i].drawHandle();
			}
		}
	}
	if (mouseMode == 3) {
		if (vertList1.size() == vertList2.size()) {
			glPointSize(2.0);
			glColor3f(0.8, 0.1, 0.8);
			glBegin(GL_POINTS);
			for (int i = 0; i < vertList1.size(); i++) {
				drawMidPointAlgo(*vertList1[i], *vertList2[i], 0.01);
			}
			glEnd();
		}
	}
	glFlush();
	glutSwapBuffers();
}

void timer(int v) {
	if (morphing) {
		if (animationCounter > 47) {
			morphing = false;
			mouseMode = 1;
		}
		else {
			for (int i = 0; i < vertList1.size(); i++) {
				float x = getXIntercept(-1.0, vertList1[i]->y + increments[i], 1.0, vertList1[i]->y + increments[i], vertList1[i]->x, vertList1[i]->y, vertList2[i]->x, vertList2[i]->y);
				vertList1[i]->x = x;
				vertList1[i]->y += increments[i];
			}
			animationCounter++;
		}
		poly1->checkSimple();
		glutPostRedisplay();
	}
	glutTimerFunc(1000 / FPS, timer, v);
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(100, 100);

	win = glutCreateWindow("Homework 1");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glutMouseFunc(mousefunc);
	glutMotionFunc(mouseMoveFunc);
	glutKeyboardFunc(keyboardfunc);
	glutTimerFunc(100, timer, 0);
	glDisable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	glutReshapeFunc(windowSizeResize);

	glutMainLoop();
	return 0;
}