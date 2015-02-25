#pragma once
#include "stdafx.h"
#include "polygon.h"


#define PI 3.14159265

using std::cout;
using std::cin;

static int win(0);
static int menu_id(0);
static int win_width(600), win_height(600);
static float mouse_x(0.0), mouse_y(0.0);
static int mouseMode(1);
static int leftButtonState(0);

extern Polygon temp;
extern std::vector<Polygon> polyList;