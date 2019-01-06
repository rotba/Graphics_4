#include "Box.h"

Box::Box(mat4 P,  mat4 T, mat4* Tscene): _P(P), _T(T), _Tscene(Tscene){}

mat4 Box::getMVP()
{
	return glm::inverse((*_Tscene))*_P *_T*_Rpsi*_Rtheta*_Rphi*_Rjunk*_S;
}

mat4 Box::getM()
{
	return _S*(*_Tscene)*_T*_Rpsi*_Rtheta*_Rphi*_Rjunk*_S;
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

void Box::translate(vec3 trans)
{
	_T = _T * glm::translate(trans);
}

void Box::rotateX(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_Rtheta = glm::rotate(_Rtheta, angle, vec3(1 * anti_clockwise_factor, 0, 0));
}

void Box::rotateZ(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_Rphi = glm::rotate(_Rphi, angle, vec3(0, 0, 1 * anti_clockwise_factor));
	_Rpsi = glm::rotate(_Rpsi, angle, vec3(0, 0, -1 * anti_clockwise_factor));
}

void Box::zoom(bool in, float delta)
{
}
