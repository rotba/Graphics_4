#include "Scene.h"
#include <iostream>

using namespace glm;
Scene::Scene(Mesh* mesh, Shader* shader):
	_camera(UP, FORWARD,POSITION, CENTER, perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f)),
	_arm(_camera.getLookAt(), mat4(1)),
	_box(_camera.getLookAt(), mat4(1), translate(vec3(5.0f,0.0f,0.0f)), mat4(1)),
	_cube_mesh(mesh),
	_shader(shader){}

Camera * Scene::getCamera()
{
	return &_camera;
}

void Scene::render()
{
	_shader->Bind();
	_arm.render(_cube_mesh, _shader);
	_shader->Update(_box.getMVP(), _box.getM());
	_cube_mesh->Draw();
}

void Scene::solve()
{
	Joint** joints = new Joint*[4];
	joints[0] = &_arm._joint_0;
	joints[1] = &_arm._joint_1;
	joints[2] = &_arm._joint_2;
	joints[3] = &_arm._joint_3;
	vec3 D = _box.getCenter();
	while (distance(_arm.getEnd(), D)>= EPSILON)
	{
		for (int i = 0 ; i < 4; i++)
		{
			vec3 R = joints[i]->getRoot();
			vec3 E = joints[i]->getEnd();
			vec3 RD = normalize(D-R);
			vec3 RE = normalize(E - R);
			float a = dot(RD, RE);
			vec3 axis = cross(RD, -RE);
			joints[i]->rotate(a, axis);
		}
	}
}

mat4 Scene::getT()
{
	return _T;
}

Scene::~Scene()
{
	
}