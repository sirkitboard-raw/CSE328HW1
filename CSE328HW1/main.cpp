/*
*	Made by Aditya balwani
*	SBUID : 109353920
*/

#include "main.h"
#include "vertex.h"

float min(float a, float b) {
	return((a > b) ? b : a);
}
float max(float a, float b) {
	return((a < b) ? b : a);
}

void drawMidPointAlgo(Vertex a, Vertex b, float lineWidth)
{
	float x0 = a.x, y0 = a.y, x1 = b.x, y1 = b.y;
	float dx, dy, incE, incNE, x, y, d, z, increment;
	float slope = (y1 - y0) / (x1 - x0);

	increment = lineWidth;
	if (x1 < x0) {
		float tempx = x0;
		float tempy = y0;
		x0 = x1;
		y0 = y1;
		x1 = tempx;
		y1 = tempy;
	}

	if (slope <= 1 && slope >= -1) {
		if (slope >= 0) {
			dx = x1 - x0;
			dy = y1 - y0;
			d = (2 * dy) - dx;
			incE = 2 * dy;
			incNE = 2 * (dy - dx);
			y = y0;
			x = x0;
			z = x1;
		}
		else {
			dx = x1 - x0;
			dy = y0 - y1;
			d = (2 * dy) - dx;
			incE = 2 * dy;
			incNE = 2 * (dy - dx);
			y = y0;
			x = x0;
			z = x1;
			increment *= -1;
		}
		for (; x < z; x += lineWidth) {
			glVertex2f(x, y);
			if (d>0) {
				d += incNE;
				y += increment;
			}

			else {
				d += incE;
			}
		}
	}

	else {
		float tempx = x0;
		float tempy = x1;
		x0 = y0;
		x1 = y1;
		y0 = tempx;
		y1 = tempy;

		if (slope>0) {

			dx = x1 - x0;
			dy = y1 - y0;
			d = (2 * dy) - dx;
			incE = 2 * dy;
			incNE = 2 * (dy - dx);
			y = y0;
			x = x0;
			z = x1;
		}
		else {
			float tempx = x0;
			float tempy = y0;
			x0 = x1;
			y0 = y1;
			x1 = tempx;
			y1 = tempy;


			dx = x1 - x0;
			dy = y0 - y1;
			d = (2 * dy) - dx;
			incE = 2 * dy;
			incNE = 2 * (dy - dx);
			y = y0;
			x = x0;
			z = x1;
			increment *= -1;
		}
		for (; x < z; x += lineWidth) {
			glVertex2f(y, x);
			if (d>0) {
				d += incNE;
				y += increment;
			}

			else {
				d += incE;
			}
		}
	}

}

float getXIntercept(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {

	float A1 = y1 - y0;
	float B1 = x0 - x1;
	float C1 = (A1*x0) + (B1*y0);

	float A2 = y3 - y2;
	float B2 = x2 - x3;
	float C2 = (A2*x2) + (B2*y2);
	float det = (A1*B2 - A2*B1);

	float x, y;
	x = (B2*C1 - B1*C2) / det;
	return x;
	
}

bool doLinesIntersect(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	
	float A1 = y1 - y0;
	float B1 = x0 - x1;
	float C1 = (A1*x0) + (B1*y0);

	float A2 = y3 - y2;
	float B2 = x2 - x3;
	float C2 = (A2*x2) + (B2*y2);
	float det = (A1*B2 - A2*B1);

	float x, y;

	if (det<0.001 && det>-0.001) {
		return false;
	}
	else {
		x = (B2*C1 - B1*C2) / det;
		y = (A1*C2 - A2*C1) / det;
	}

	int flag = 0;

	if (min(x0, x1) < x && max(x0, x1) > x) {
		if (min(y0, y1) < y && max(y0, y1) > y) {
			flag++;
		}
	}
	if (min(x2, x3) < x && max(x2, x3) > x) {
		if (min(y2, y3) < y && max(y2, y3) > y) {
			flag++;
		}
	}
	return (flag==2);
}

void fillPolygon(std::vector<Vertex> vertices) {
	std::vector<float> intercepts;
	for (float i = 1; i > -1; i -= 0.0025) {
		for (int j = 0; j < vertices.size(); j++) {
			if (i <(max(vertices[j].y, vertices[(j + 1) % vertices.size()].y))) {
				if (i >(min(vertices[j].y, vertices[(j + 1) % vertices.size()].y))) {
					intercepts.push_back(getXIntercept(-1.0, i, 1.0, i, vertices[j].x, vertices[j].y, vertices[(j + 1) % vertices.size()].x, vertices[(j + 1) % vertices.size()].y));
				}
			}
		}
		std::sort(intercepts.begin(), intercepts.end());
		for (int j = 0; j < intercepts.size(); j += 2) {
			drawMidPointAlgo(Vertex((intercepts[j]+0.005f), i+0.005f), Vertex(intercepts[j + 1]-0.005f, i-0.005f),0.005);
		}
		intercepts.clear();
	}
}



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

void scale(int sf) {
	float sfactor = sf / 100.0;
	temp.scale(sfactor);
	for (int i = 0; i < polyList.size(); i++) {
		polyList[i].scale(sfactor);
	}
	glutPostRedisplay();
}

void rotate(int ra) {
	float rads = ra*PI / 180.0;
	temp.rotate(rads);
	for (int i = 0; i < polyList.size(); i++) {
		polyList[i].rotate(rads);
	}
	glutPostRedisplay();
}

void reflect() {
	temp.reflect();
	for (int i = 0; i < polyList.size();i++) {
		polyList[i].reflect();
	}
	glutPostRedisplay();
}

void shear(int sf, char type) {
	float sfactor = sf / 100.0;
	if (type == 'h') {
		temp.horShear(sfactor);
		for (int i = 0; i < polyList.size(); i++) {
			polyList[i].horShear(sfactor);
		}
	}
	else if (type == 'v') {
		temp.verShear(sfactor);
		for (int i = 0; i < polyList.size(); i++) {
			polyList[i].verShear(sfactor);
		}
	}
	glutPostRedisplay();
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
	for (Polygon &a : polyList) {
		a.draw();
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