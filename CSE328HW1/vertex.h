#include "stdafx.h"

struct Vertex {
	float x;
	float y;

	Vertex() :x(-1), y(-1){};
	Vertex(float a, float b) :x(a), y(b){};
	Vertex(double a, double b) :x(a), y(b){};

	void draw() {
		glVertex2f(x, y);

	}
};