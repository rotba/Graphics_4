#include "Data.h"

Data::Data(Scene* scene, Display* display, Shader* picking_shader)
{
	_picking_shader = picking_shader;
	_scene = scene;
	_display = display;
	_l_button = false;
	_r_button = false;
}
