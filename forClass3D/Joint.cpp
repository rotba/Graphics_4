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
	return _Tarm*getPrevR()*_Thight*_R*_S;
}

mat4 Joint::getPrevR()
{
	if (_prev == nullptr) {
		return mat4(1);
	}
	else {
		return (_prev->getR());
	}
}

mat4 Joint::getR()
{
	if (_prev ==nullptr) {
		return _R;
	}
	else {
		return (_prev->getR())*_R;
	}
}

void Joint::rotateX(bool clockwise, float angle)
{
	_R = _R * rotate(angle, vec3(1,0,0));
}

void Joint::rotateZ(bool clockwise, float angle)
{
	_R = rotate(angle, vec3(0, 0, -1))*_R;
}
