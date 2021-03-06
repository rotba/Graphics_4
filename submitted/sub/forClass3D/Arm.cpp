#include "Arm.h"
Arm::Arm(mat4 P, mat4 T, mat4* Tscene, mat4* Rscene, Camera* camera):
	_T(T),
	_P(P),
	_joint_0(nullptr, &_T, P, Tscene, Rscene, camera),
	_joint_1(&_joint_0, &_T, P, Tscene, Rscene, camera),
	_joint_2(&_joint_1, &_T, P, Tscene, Rscene, camera),
	_joint_3(&_joint_2, &_T, P, Tscene, Rscene, camera),
	_joints{&_joint_0,&_joint_1,&_joint_2,&_joint_3}{}

mat4 Arm::getT()
{
	return _T;
}

void Arm::render(Mesh * cube_mesh, Mesh * rf_mesh, Shader * shader)
{
	for each (Joint* j in _joints)
	{
		shader->Update(j->getMVP(), j->getM());
		cube_mesh->Draw();
		if (j != &_joint_3) {
			shader->Update(j->getMVP()*translate(vec3(0, 0, -1))*scale(vec3(0.5, 0.5, 0.5)), j->getM()*translate(vec3(0, 0, -1))*scale(vec3(0.5, 0.5, 0.5)));
			rf_mesh->DrawLines();
		}
	}
}

void Arm::pickingRender(Mesh * cube_mesh, Mesh * rf_mesh, Shader * shader)
{
	for each (Joint* j in _joints)
	{
		shader->Update(j->getMVP(), j->getM());
		shader->SetPickingColor(j->getPickingColor());
		cube_mesh->Draw();
	}
}

vec3 Arm::getEnd()
{
	return (_joint_3.getEnd());
}

vec3 Arm::getRoot()
{
	return _joint_0.getRoot();
}
