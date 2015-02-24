#include "stdafx.h"
#include "vertex.h"
#include "basicFunctions.h"

void drawMidPointAlgo(Vertex a, Vertex b, float lineWidth);
bool doLinesIntersect(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
float getXIntercept(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);