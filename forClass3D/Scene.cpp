#include "Scene.h"
#include <iostream>

using namespace glm;
Scene::Scene(Mesh* mesh, Shader* shader):
	_camera(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),vec3(0, 0, -12), perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f)),
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
	//_shader->Update(_box.getMVP(), _box.getM());
	//_cube_mesh->Draw();
}

mat4 Scene::getT()
{
	return _T;
}

Scene::~Scene()
{
	
}