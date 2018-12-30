#include "display.h"
#include "glm\glm.hpp"
#include "RCube.h"

class Data
{
public:
	Data(RCube* rcube, Display* display);

	RCube* _rcube;
	Display* _display;
	bool _l_button;
	bool _r_button;
	double _curr_x;
	double _curr_y;
private:
	
};

#pragma once
