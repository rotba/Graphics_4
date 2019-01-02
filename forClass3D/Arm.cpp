#include "Arm.h"
Arm::Arm(mat4 P, mat4 T) :
	_T(T),
	_P(P),
	_joint_0(nullptr, translate(vec3(0, 0, 0)), P),
	_joint_1(&_joint_0, translate(vec3(0, 0, 0)), P),
	_joint_2(&_joint_1, translate(vec3(0, 0, 0)), P),
	_joint_3(&_joint_2, translate(vec3(0, 0, 0)), P){}

mat4 Arm::getT()
{
	return _T;
}

void Arm::render(Mesh * mesh, Shader * shader)
{
	shader->Update(_joint_0.getMVP(), _joint_0.getM());
	mesh->Draw();
	shader->Update(_joint_1.getMVP(), _joint_1.getM());
	mesh->Draw();
	shader->Update(_joint_2.getMVP(), _joint_2.getM());
	mesh->Draw();
	shader->Update(_joint_3.getMVP(), _joint_3.getM());
	mesh->Draw();
}
