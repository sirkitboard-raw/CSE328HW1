/*
*	Made by Aditya balwani
*	SBUID : 109353920
*/

#include "stdafx.h"
#include "vector"
#include "GL/glut.h"


static int win(0);
static int menu_id(0);
static int win_width(600), win_height(600);
static float mouse_x(0.0), mouse_y(0.0);
static int mouseMode(-1);

struct Vertex {
	float x;
	float y;

	Vertex() :x(-1), y(-1){};
	Vertex(float a, float b) :x(a), y(b){};
	Vertex(double a, double b) :x(a), y(b){};

	void draw() {
		glColor3f(0.2, 0.5, 0.8);
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
};

void drawMidPointAlgo(Vertex a, Vertex b) {
	float x0 = a.x, y0 = a.y, x1 = b.x, y1 = b.y;
	float dx, dy, incE, incNE, x, y, d, z;
	float slope = (y1 - y0) / (x1 - x0);
	printf("Slope : %.2f\n", slope);
	glBegin(GL_POINTS);
	glColor3f(0.8, 0.5, 0.2);
	if (x1 < x0) {
		float tempx = x0;
		float tempy = y0;
		x0 = x1;
		y0 = y1;
		x1 = tempx;
		y1 = tempy;
	}

	if (slope >= 0 && slope<1) {
		dx = x1 - x0;
		dy = y1 - y0;
		d = (2 * dy) - dx;
		incE = 2 * dy;
		incNE = 2 * (dy - dx);
		y = y0;
		x = x0;
		z = x1;
		for (; x < z; x += 0.005) {
			glVertex2f(x, y);
			if (d>0) {
				d += incNE;
				y += 0.005;
			}

			else {
				d += incE;
			}
		}
	}
	else if (slope > 1) {
		dx = x1 - x0;
		dy = y1 - y0;
		d = (2 * dx) - dy;
		incE = 2 * dx;
		incNE = 2 * (dx - dy);
		y = x0;
		x = y0;
		z = y1;
		for (; x < z; x += 0.005) {
			glVertex2f(y, x);
			if (d>0) {
				d += incNE;
				y += 0.005;
			}

			else {
				d += incE;
			}
		}
	}
	glEnd();
}


struct Polygon {
	std::vector<Vertex> vertices;
	bool polyComplete;
	Polygon() {
		polyComplete = false;
	};

	int size() {
		return vertices.size();
	}

	bool is_empty() {
		return vertices.empty();
	}

	void clear() {
		vertices.clear();
	}

	void draw() {
		for (int i = 1; i < vertices.size(); i++) {
			drawMidPointAlgo(vertices[i], vertices[i-1]);
		}
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].draw();
		}
	}
};

Polygon temp;

void mousefunc(int button, int state, int x, int y) {
	mouse_x = (x*2.0) / win_width - 1.0;
	mouse_y = 1.0 - (y*2.0) / win_height;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		temp.vertices.push_back(Vertex(mouse_x, mouse_y));
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		temp.vertices.push_back(temp.vertices[0]);
		temp.polyComplete = true;
	}
}

void keyboardfunc(unsigned char key, int x, int y) {
	if (key == 'c') {
		temp.vertices.clear();
		glutPostRedisplay();
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	temp.draw();

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
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
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