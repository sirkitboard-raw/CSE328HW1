#include "stdafx.h"
#include "polygonFunctions.h"

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
			drawMidPointAlgo(Vertex((intercepts[j] + 0.005f), i + 0.005f), Vertex(intercepts[j + 1] - 0.005f, i - 0.005f), 0.005);
		}
		intercepts.clear();
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
