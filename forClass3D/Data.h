#include "display.h"
#include "glm\glm.hpp"
#include "Scene.h"

class Data
{
public:
	Data(Scene* scene, Display* display, Shader *picking_shader);

	Scene* _scene;
	Display* _display;
	Shader* _picking_shader;
	Transformable* _picked;
	bool _l_button;
	bool _r_button;
	double _curr_x;
	double _curr_y;
	double unit_factor = 0.025;
	double unit_depth = 0.993721;
private:
	
};

#pragma once
