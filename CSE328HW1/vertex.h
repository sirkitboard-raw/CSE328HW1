#pragma once
#include "stdafx.h"

struct Vertex {
	float x;
	float y;
	bool clickable = true;

	Vertex() :x(-1), y(-1){};
	Vertex(float a, float b) :x(a), y(b){};
	Vertex(double a, double b) :x(a), y(b){};

	float getDistance(float a, float b) {
		float dist = sqrt(pow((x - a), 2) + pow((y - b), 2));
		return dist;
	}

	void drawHandle() {
		glLineWidth(2.0);
		glColor3f(0.9, 0.9, 0.1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(x + 0.02, y + 0.02);
		glVertex2f(x + 0.02, y - 0.02);
		glVertex2f(x - 0.02, y - 0.02);
		glVertex2f(x - 0.02, y + 0.02);
		glEnd();
	}

	bool clicked(float a, float b) {
		if (clickable == false) {
			return false;
		}
		if (getDistance(a, b) < 0.2) {
			return true;
		}
		return false;
	}
	void draw() {
		glVertex2f(x, y);

	}

};
