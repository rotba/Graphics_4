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
	bool _l_button;
	bool _r_button;
	double _curr_x;
	double _curr_y;
private:
	
};

#pragma once
