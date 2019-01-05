#include "Scene.h"
#include <iostream>

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
	vec3 R = joints[curr_joint]->getRoot();
	vec3 E = _arm.getEnd();
	std::cout << E.x << std::endl;
	std::cout << E.y << std::endl;
	std::cout << E.z << std::endl << std::endl;
	vec3 RD = normalize(D-R);
	vec3 RE = normalize(E-R);
	float a = acos(dot(RD, RE));
	vec3 axis = cross(RD, -RE);
	if (EULER) {
		float theta = a;
		joints[curr_joint]->rotateX(true, theta);
		vec3 tmp = normalize(_arm.getEnd() - R);
		vec3 tmp_proj = vec3(tmp.x,tmp.y,0);
		//vec3 projected_RE = normalize(vec3(RE.x, RE.y, 0));
		vec3 projected_RD = normalize(vec3(RD.x, RD.y, 0));
		float phi = acos(dot(projected_RD, tmp_proj));
		joints[curr_joint]->rotateZ(true, phi);

	}
	else {
		joints[curr_joint]->rotate(a, axis);
	}
	if (curr_joint == 0) {
		curr_joint = 3;
	}
	else {
		curr_joint -=1;
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
}

bool Scene::isDone()
{
	vec3 D = _box.getCenter();
	return distance(_arm.getEnd(), D)>=EPSILON;
}

void Scene::setEuler()
{
	EULER = !EULER;
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
