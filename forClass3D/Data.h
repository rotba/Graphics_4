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
	bool _solve = false;
	vec3 curr_cursor = vec3(0, 0, 0);
	float curr_depth = 0;
	double unit_factor = 0.025;
	double unit_depth = 0.993721;
private:
	
};

#pragma once
