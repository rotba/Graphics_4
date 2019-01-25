#include "Joint.h"
#include <iostream>

Joint::Joint(Joint* prev, mat4* Tarm, mat4 P, mat4* Tscene, mat4* Rscene, Camera* camera):
	_prev(prev),
	_Thight(glm::translate(vec3(0,0 , 4 ))), _Tarm(Tarm),_S(scale(vec3(1.0f, 1.0f, 2.0f))), _P(P),
	_Tscene(Tscene),
	_Rscene(Rscene),
	_camera(camera){}
mat4 Joint::getMVP()
{
	return _P*(*_Tscene)*(*_Rscene)*(*_Tarm)*getPrev()*_Rpsi*_Rtheta*_Rphi*_Rjunk*_S*_base;
}

mat4 Joint::getPrev()
{
	if (_prev ==nullptr) {
		return mat4(1);
	}
	else {
		return _prev->getPrev()*(_prev->_Rpsi*_prev->_Rtheta*_prev->_Rphi*_prev->_Rjunk)*_Thight;
	}
}

mat4 Joint::getM()
{
	return (*_Tscene)*(*_Tarm)*getPrev()*_Rpsi*_Rtheta*_Rphi*_Rjunk*_S*_base;
}

mat4 Joint::getR()
{
	return _Rpsi * _Rtheta*_Rphi*_Rjunk;
}

vec3 Joint::getRoot()
{
	return (vec3)(getM() * vec4(0, 0, -1, 1.0));
}

vec3 Joint::getEnd()
{
	return (vec3)(getM() * vec4(0, 0, 1, 1));
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
	_Rjunk = _Rjunk * glm::rotate(a, axis);
}


void Joint::rotateTmp(mat4 jnk)
{
	_Rjunk = _Rjunk * jnk;
}



void Joint::rotateX(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_Rtheta = glm::rotate(_Rtheta,angle, vec3(1* anti_clockwise_factor,0,0));
}

void Joint::rotateZ(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_Rphi = glm::rotate(_Rphi, angle, vec3(0, 0, 1 * anti_clockwise_factor));
	_Rpsi = glm::rotate(_Rpsi, angle, vec3(0, 0, -1 * anti_clockwise_factor));
}

void Joint::translate(vec3 trans)
{
	*_Tarm = (*_Tarm)* glm::translate(trans);
}

void Joint::zoom(bool in, float delta)
{
	vec3 trans = (_camera->getForward()) * delta;
	*_Tarm = (*_Tarm)* glm::translate(trans);
}

void Joint::printEulerEngles()
{
	cout << "Phi matrix:" << endl;
	print_matrix(_solverPhi);
	cout << "Theta matrix:" << endl;
	print_matrix(_solverTheta);
	cout << "Psi matrix:" << endl;
	print_matrix(_solverPsi);
}

void Joint::rotateTheta(vec3 axis, float theta)
{
	_Rtheta = glm::rotate(_Rtheta, theta, axis);
}
void Joint::rotatePsi(float psi)
{
	_Rpsi = glm::rotate(_Rpsi, psi, vec3(0, 0, -1));
}
void Joint::rotatePhi(vec3 axis, float phi)
{
	_Rphi = glm::rotate(_Rphi, phi, axis);
}
