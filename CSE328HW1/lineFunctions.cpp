#include "stdafx.h"
#include "lineFunctions.h"

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
	return (flag == 2);
}