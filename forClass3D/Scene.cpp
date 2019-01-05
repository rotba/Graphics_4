#include "Scene.h"
#include <iostream>

using namespace glm;
Scene::Scene(Mesh* cube_mesh, Mesh* rf_mesh, Shader* shader, Shader* picking_shader, Texture* cube_tex, Texture* box_tex):
	_camera(UP, FORWARD,POSITION, CENTER, perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f)),
	_arm(_camera.getLookAt(), mat4(1)),
	_box(_camera.getLookAt(), mat4(1), translate(vec3(5.0f,0.0f,0.0f)), mat4(1)),
	_cube_tex(cube_tex),
	_box_tex(box_tex),
	_cube_mesh(cube_mesh),
	_rf_mesh(rf_mesh),
	_shader(shader),
	_picking_shader(picking_shader) 
{
	generatePickingColors();
	_arm._joint_0.setPickingColor(J0_PC);
	_arm._joint_1.setPickingColor(J1_PC);
	_arm._joint_2.setPickingColor(J2_PC);
	_arm._joint_3.setPickingColor(J3_PC);
	_box.setPickingColor(BOX_PC);
	updatePickingShader();
}

Camera * Scene::getCamera()
{
	return &_camera;
}

void Scene::render()
{
	_shader->Bind();
	_cube_tex->Bind(0);
	_arm.render(_cube_mesh, _rf_mesh, _shader);
	_box_tex->Bind(0);
	_shader->Update(_box.getMVP(), _box.getM());
	_cube_mesh->Draw();
	_shader->Update(_camera.getLookAt(), mat4(1));
	_rf_mesh->DrawLines();
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
			//joints[i]->rotate(a, axis);
		}
	}
}

mat4 Scene::getT()
{
	return _T;
}

void Scene::printPickedObject(int picked_id)
{
	switch (picked_id)
	{
	case 0:
		std::cout << "J0" << std::endl;
		break;
	case 1:
		std::cout << "J1" << std::endl;
		break;
	case 2:
		std::cout << "J2" << std::endl;
		break;
	case 3:
		std::cout << "J3" << std::endl;
		break;
	case 4:
		std::cout << "BOX" << std::endl;
		break;
	default:
		std::cout << "BACKGROUND" << std::endl;
		break;
	}
	/*if (pc == J0_PC) std::cout << "J0" << std::endl;
	else if (pc == J1_PC) std::cout << "J1" << std::endl;
	else if (pc == J2_PC) std::cout << "J2" << std::endl;
	else if (pc == J3_PC) std::cout << "J3" << std::endl;
	else if (pc == BOX_PC) std::cout << "BOX" << std::endl;*/
}

Scene::~Scene()
{
	
}

void Scene::updatePickingShader()
{
	_picking_shader->Bind();
	_picking_shader->clear();
	_arm.pickingRender(_cube_mesh, _rf_mesh, _picking_shader);
	_picking_shader->Update(_box.getMVP(), _box.getM());
	_picking_shader->SetPickingColor(_box.getPickingColor());
	_cube_mesh->Draw();
	_picking_shader->flush();
}
