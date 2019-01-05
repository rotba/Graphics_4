#include "Joint.h"

Joint::Joint(Joint* prev, mat4 Tarm, mat4 P): _prev(prev), _Thight(translate(vec3(0,0,-4 ))), _Tarm(Tarm),_S(scale(vec3(1.0f, 1.0f, 2.0f))), _P(P){}
mat4 Joint::getMVP()
{
	mat4 base = translate(vec3(0,0,-1));
	return _P*_Tarm*getPrev()*_R*_S*base;
}

mat4 Joint::getPrev()
{
	if (_prev ==nullptr) {
		return mat4(1);
	}
	else {
		return _prev->getPrev()*_prev->_R*_Thight;
	}
}

mat4 Joint::getM()
{
	return _Tarm*getPrev()*_Thight*_R*_S;
}

vec3 Joint::getRoot()
{
	return (vec3)(getMVP() * vec4(0, 0, -2, 1));
}

vec3 Joint::getEnd()
{
	return (vec3)(getMVP() * vec4(0, 0, 2, 1));
}

void Joint::setPickingColor(vec4 pickingColor)
{
	_picking_color = pickingColor;
}

vec4 Joint::getPickingColor()
{
	return _picking_color;
}

void Joint::rotate(float a, vec3 axis)
{
	_R = _R * (glm::rotate(a, axis));
}


void Joint::rotateX(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_R = _R * (glm::rotate(angle, vec3(1* anti_clockwise_factor,0,0)));
}

void Joint::rotateZ(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_R = (glm::rotate(angle, vec3(0, 0, -1* anti_clockwise_factor)))*_R;
}
