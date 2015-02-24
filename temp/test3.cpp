/****************************************************************
*  Copyright@2011
*
*  example of mouse selection, polygon creation.
*
*  useage:
*      use mouse "MIDDLE" button to popup menu;
*      two modes: CREATION -- create polygon
*                 SELECTION -- select point;
*
*  shuchu.han@gmail.com
*  26th-Feb-2011
****************************************************************/

#include "stdafx.h"
#include <vector>
#include <algorithm>

#include <GL/glut.h>

/* global variables */
static int win(0); // GLUT window ID
static int menu_id(0); // menu id;
static int win_width(600), win_height(600); // window's width and height
static float mouse_x(0.0), mouse_y(0.0);
static int mouse_mode(-1); // flag, 0 -- selecting mode, 1 -- creating mode;

/* Pixel vertex */
struct MyPixelVertex{
	int x;
	int y;

	MyPixelVertex() :x(-1), y(-1){};
	MyPixelVertex(int a, int b) :x(a), y(b){};
};

/* vertex with a quad selection range. the edge length is 0.02 */
struct MyVertex{
	int id;
	float x;
	float y;
	float range; //mouse selection range;

	MyVertex() :x(0.0), y(0.0), id(-1), range(0.02){};
	MyVertex(float a, float b) :x(a), y(b), id(-1), range(0.02){};
	MyVertex(double a, double b) :x(a), y(b), id(-1), range(0.02){};

	void draw_selection_range()
	{
		glColor3f(0.2f, 0.5f, 0.8f);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x - range, y + range); //edge length is 0.02
		glVertex2f(x - range, y - range);
		glVertex2f(x + range, y - range);
		glVertex2f(x + range, y + range);
		glEnd();
	};

	void draw()
	{
		glColor3f(1.0f, 0.8f, 0.0f);
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}

	bool is_selected(float mouse_x_pos, float mouse_y_pos)
	{
		if (mouse_x_pos >= (x - range) && mouse_y_pos >= (y - range) &&
			mouse_x_pos <+(x + range) && mouse_y_pos >= (y - range)){
			return true;
		}
		else{
			return false;
		}
	}

	void set_range(float value){
		if (value > 0.0 && value < 1.0)
			range = value;
	}
};

/* Polygon */
struct MyPolygon{
	std::vector<MyVertex> nodes; //nodes of polygon

	MyPolygon(){};

	int size_of_nodes(){ return nodes.size(); } // return size;
	bool is_empty(){ return nodes.empty(); }
	void clear(){ nodes.clear(); } //clear all nodes;

	void draw()
	{
		//1) rendering draw the polygon

		//!!! Attention, you are not allowed to use "GL_POLYGON", 
		// you have to render the inside of polygon by drawing each pixel(points) 

		glBegin(GL_POLYGON);
		for (int i = 0; i < (int)nodes.size(); ++i){
			glVertex2f(nodes[i].x, nodes[i].y);
		}
		glEnd();

		//2) rendering the vertices;
		for (int i = 0; i < (int)nodes.size(); ++i){
			nodes[i].draw();
			if (nodes[i].is_selected(mouse_x, mouse_y))
				nodes[i].draw_selection_range();
		}

		//3) rendering the edges;
		glColor3f(0.8, 0.5, 0.2);
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < (int)nodes.size(); ++i){
			glVertex2f(nodes[i].x, nodes[i].y);
		}
		glEnd();
	};
};

MyPolygon polygon_buffer; // a polygon buffer;
std::vector<MyPolygon>   polygons; //record all polygons on the screen.

/* Pixel to World coordinates*/
MyPixelVertex WorldToPixel(MyVertex& v)
{
	MyPixelVertex pxl;
	pxl.x = (int)((v.x + 1.0)*win_width*0.5);
	pxl.y = (int)((1.0 - v.y)*win_height*0.5);
	return pxl;
};

MyVertex PixelToWorld(MyPixelVertex& pxl)
{
	MyVertex v;
	v.x = (pxl.x*2.0) / win_width - 1.0;
	v.y = 1.0 - (pxl.y*2.0) / win_height;
	return v;
};

/* set menu */
void Menu(int value) //Menu function;
{
	if (value == 3)
		exit(-1);  // quit
	else if (value == 0){
		mouse_mode = 0; // selection
	}
	else if (value == 1){
		mouse_mode = 1; // creation
	}
	else if (value == 2){
		mouse_mode = 2; // NONE
	}
	else if (value == 4){
		polygons.clear(); // clear polygons
		glutPostRedisplay();
	}
}

/* menu creation */
/*void CreateMenu(void)
{
	menu_id = glutCreateMenu(Menu);
	//create an entry

	glutAddMenuEntry("NONE", 2);
	glutAddMenuEntry("SELECTION", 0);
	glutAddMenuEntry("CREATION", 1);
	glutAddMenuEntry("CLEAR", 4);
	glutAddMenuEntry("Quit", 3);

	//let the menu respnd on the right button
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}*/


// Call-back function glutMouseFunc();
// get the mouse position from here
void MouseMotion(int button, int state, int x, int y)
{
	// we calculate the coordiante transform by ourself;
	mouse_x = (x*2.0) / win_width - 1.0;
	mouse_y = 1.0 - (y*2.0) / win_height;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("mouse screen(pixel) pos: (%d %d) window pos: (%f %f)\n", \
			x, y, mouse_x, mouse_y);

		if (mouse_mode == 0){
			//selecting mode;


		}
		else if (mouse_mode == 1){
			//creating mode;
			polygon_buffer.nodes.push_back(MyVertex(mouse_x, mouse_y));
		}

		glutPostRedisplay(); // for redraw the current mouse position;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if (mouse_mode == 1){
			// creating ending;
			polygons.push_back(polygon_buffer); //put polygon buffer to container;
			polygon_buffer.clear(); // clear the buffer for next creating;
		}
	}
};

// Call-back function for windows size changed;
void WindowSizeReShape(int w, int h)
{
	win_width = w;
	win_height = h;

	//update the viewport;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	//update the projection matrix;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
}

void DrawCrossAtOrigin()
{
	// draw a cross at origin
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.1f, 0.0f);
	glVertex2f(0.1f, 0.0f);
	glVertex2f(0.0f, -0.1f);
	glVertex2f(0.0f, 0.1f);
	glEnd();
}

/* display */
void Display(void)
{
	//clean the scene
	glClear(GL_COLOR_BUFFER_BIT);

	//set matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//draw a cross at origin;
	DrawCrossAtOrigin();

	//draw a unit cube;
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(1.0);

	//draw mouse pointer;
	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(mouse_x, mouse_y);
	glEnd();

	//draw polygons
	polygon_buffer.draw();

	for (int i = 0; i < (int)polygons.size(); ++i)
	{
		polygons[i].draw();
	}

	glFlush();
};

/* MAIN */
int main4(int argc, char* argv[])
{
	//step 1. initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(100, 100);

	//step 2. Open a window named "GLUT DEMO"
	win = glutCreateWindow("GLUT Mouse Motion");
	glClearColor(0.0, 0.0, 0.0, 0.0); //set background

	//misc
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	//disable depth test as only draw 2D objects;
	glDisable(GL_DEPTH_TEST);

	//step 3. register the display function
	glutDisplayFunc(Display);
	glutMouseFunc(MouseMotion);
	glutReshapeFunc(WindowSizeReShape);

//	CreateMenu();

	//step 4. enter the event processing loop
	glutMainLoop();
	return 0;
}
