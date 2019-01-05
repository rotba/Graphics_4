#include "Box.h"

Box::Box(mat4 P, mat4 R, mat4 T, mat4 S): _P(P), _R(R), _T(T), _S(S){}

mat4 Box::getMVP()
{
	return _P*_S*_T*_R;
}

mat4 Box::getM()
{
	return _S*_T*_R;
}

vec3 Box::getCenter()
{
	return (vec3)(getM() * vec4(0, 0, 0, 1));
}

void Box::setPickingColor(vec4 picking_color)
{
	_picking_color = picking_color;
}

vec4 Box::getPickingColor()
{
	return _picking_color;
}
