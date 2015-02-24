#pragma once
#include "stdafx.h"
#include "main.h"
#include "lineFunctions.h"
#include "vertex.h"

struct Polygon {
	std::vector<Vertex> vertices;
	bool polyComplete;
	bool isSimple;
	Polygon() {
		polyComplete = false;
		isSimple = true;
	};

	int size() {
		return vertices.size();
	}

	bool is_empty() {
		return vertices.empty();
	}

	void clear() {
		vertices.clear();
		polyComplete = false;
		isSimple = true;
	}

	void scale(float sf) {
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].x *= sf;
			vertices[i].y *= sf;
		}
	}

	void rotate(float ra) {
		for (int i = 0; i < vertices.size(); i++) {
			float tempx = vertices[i].x;
			float tempy = vertices[i].y;
			vertices[i].x = tempx*cos(ra) - tempy*sin(ra);
			vertices[i].y = tempx*sin(ra) + tempy*cos(ra);
		}
	}

	void horShear(float sf) {
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].x = vertices[i].x + sf*vertices[i].y;
		}
	}

	void verShear(float sf) {
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].y = vertices[i].y + sf*vertices[i].x;
		}
	}

	void reflect() {
		for (int i = 0; i < vertices.size(); i++) {
			float tempx = vertices[i].x;
			float tempy = vertices[i].y;
			vertices[i].x = tempy * -1;
			vertices[i].y = tempx * -1;
		}
	}

	void draw() {
		glPointSize(4.0);
		glBegin(GL_POINTS);
		if (isSimple) glColor3f(0.1, 0.9, 0.1);
		else glColor3f(0.9, 0.1, 0.1);
		if (polyComplete && isSimple) {
			fillPolygon(vertices);
		}
		glEnd();
		glPointSize(2.0);
		glBegin(GL_POINTS);
		if (isSimple){
			glColor3f(0.1, 0.1, 0.9);
		}
		if (polyComplete) {
			drawMidPointAlgo(vertices[vertices.size() - 1], vertices[0], 0.0025);
		}
		for (int i = 1; i < vertices.size(); i++) {
			drawMidPointAlgo(vertices[i], vertices[i - 1], 0.0025);
		}
		glColor3f(0.2, 0.5, 0.8);
		glEnd();
		glPointSize(4.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].draw();
		}
		glEnd();
	}

	void checkSimple() {
		for (int i = 0; i < vertices.size(); i++) {
			for (int j = 0; j < vertices.size(); j++) {
				if (i == j);
				else if (i == j - 1);
				else if (i == j + 1);
				else if (doLinesIntersect(vertices[i].x + 1, vertices[i].y + 1, vertices[(i + 1) % (int)vertices.size()].x + 1, vertices[(i + 1) % (int)vertices.size()].y + 1, vertices[j].x + 1, vertices[j].y + 1, vertices[(j + 1) % (int)vertices.size()].x + 1, vertices[(j + 1) % (int)vertices.size()].y + 1)) {
					isSimple = false;
					break;
				}
			}
		}
		cout << isSimple;
	}

};