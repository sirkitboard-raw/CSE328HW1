#include "stdafx.h"
#include "basicFunctions.h"

float min(float a, float b) {
	return((a > b) ? b : a);
}
float max(float a, float b) {
	return((a < b) ? b : a);
}