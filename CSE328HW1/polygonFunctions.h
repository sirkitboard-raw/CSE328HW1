#include "vertex.h"
#include "lineFunctions.h"
#include "main.h"

void fillPolygon(std::vector<Vertex> vertices);
void scale(int sf);
void rotate(int ra);
void reflect();
void shear(int sf, char type);
void morphPolygon(std::vector<Vertex*> vlist1, std::vector<Vertex*> vlist2);