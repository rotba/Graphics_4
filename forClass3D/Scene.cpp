#include "Scene.h"
#include <iostream>

Scene::Scene(Mesh* cube_mesh, Mesh* rf_mesh, Shader* shader, Shader* picking_shader, Texture* cube_tex, Texture* box_tex):
	_camera(UP, FORWARD,POSITION, CENTER, perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f)),
	_arm(_camera.getLookAt(), mat4(1), &_Tchildren),
	_box(_camera.getLookAt(), glm::translate(vec3(5.0f,0.0f,0.0f)), &_Tchildren),
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
	vec3 RD = normalize(D-R);
	vec3 RE = normalize(E-R);
	float a = degrees(acos(dot(RD, RE)));
	vec3 axis = normalize(cross(RD, -RE));
	if (EULER) {
		float theta = 0;
		float phi = 0;
		//if (RD.x==0 && RD.y ==0){ 
		//	theta =a;
		//	joints[curr_joint]->rotateX(true, theta);
		//}
		//else if (RE.x == 0 && RE.y == 0) {
		//	theta = a;
		//	joints[curr_joint]->rotateX(true, theta/3);
		//	vec3 RE_tag = normalize(_arm.getEnd() - R);
		//	vec2 norm_RE_tag_xy = normalize(vec2(RE_tag.x, RE_tag.y));
		//	vec2 norm_RD_xy = normalize(vec2(RD.x, RD.y));
		//	phi = degrees(acos(dot(norm_RE_tag_xy, norm_RD_xy)));
		//	joints[curr_joint]->rotateZ(true, phi);
		//}else {
		//	float alpha = degrees(acos(dot(RE, vec3(RE.x,RE.y,0))));
		//	float beta = degrees(acos(dot(RD, vec3(RD.x, RD.y, 0))));
		//	theta = alpha - beta;
		//	/*vec2 norm_RE_xy = normalize(vec2(RE.x, RE.y));
		//	vec2 norm_RD_xy = normalize(vec2(RD.x, RD.y));
		//	float phi_tag = degrees(acos(dot(norm_RE_xy, norm_RD_xy)));
		//	joints[curr_joint]->rotateZ(true, phi_tag);
		//	vec3 RE_tag = normalize(_arm.getEnd() - R);
		//	theta = degrees(acos(dot(RE_tag, RD)));*/
		//	joints[curr_joint]->rotateX(true, theta/3);
		//	vec3 RE_tag = normalize(_arm.getEnd() - R);
		//	phi = degrees(acos(dot(RE_tag, RD)));
		//	joints[curr_joint]->rotateZ(true, phi);
		//}
		/*vec3 euler_angles = rotationMatrixToEulerAngles(rotate(a , axis));
		joints[curr_joint]->rotateTmp(eulerAngleYXZ);*/
	}
	else {
		joints[curr_joint]->rotate(a/3, axis);
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

Transformable* Scene::getPickedObject(int picked_id)
{
	switch (picked_id)
	{
	case 0:
		return &_arm._joint_0;
		break;
	case 1:
		return &_arm._joint_1;
		break;
	case 2:
		return &_arm._joint_2;
		std::cout << "J2" << std::endl;
		break;
	case 3:
		return &_arm._joint_3;
		std::cout << "J3" << std::endl;
		break;
	case 4:
		return &_box;
		std::cout << "BOX" << std::endl;
		break;
	default:
		return this;
		std::cout << "BACKGROUND" << std::endl;
		break;
	}
}

void Scene::translate(vec3 trans)
{
	_T = _T * glm::translate(trans);
	updateChildren();
}

void Scene::rotateX(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_Rtheta = glm::rotate(_Rtheta, angle, vec3(1 * anti_clockwise_factor, 0, 0));
	updateChildren();
}

void Scene::rotateZ(bool anti_clockwise, float angle)
{
	int anti_clockwise_factor = anti_clockwise ? 1 : -1;
	_Rphi = glm::rotate(_Rphi, angle, vec3(0, 0, 1 * anti_clockwise_factor));
	_Rpsi = glm::rotate(_Rpsi, angle, vec3(0, 0, -1 * anti_clockwise_factor));
	updateChildren();
}

void Scene::zoom(bool in, float delta)
{
	vec3 trans = FORWARD * delta;
	_T = _T * glm::translate(trans);
	updateChildren();
}
void Scene::updateChildren()
{
	_Tchildren = _T * _Rpsi* _Rtheta*_Rphi*_Rjunk*_S;
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

vec3 Scene::rotationMatrixToEulerAngles(mat4 M)
{

	float sy = sqrt(M[0][0] * M[0][0] + M[1][0] * M[1][0]);

	bool singular = sy < 1e-6; // If

	float x, y, z;
	if (!singular)
	{
		x = atan2(M[2][1], M[2][2]);
		y = atan2(-M[2][0], sy);
		z = atan2(M[1][0], M[0][0]);
	}
	else
	{
		x = atan2(-M[1][2], M[1][1]);
		y = atan2(-M[2][0], sy);
		z = 0;
	}
	return vec3(x, y, z);



}

void Scene::rotateXPicked(int picked_id, bool anti_clockwise, float angle)
{
	switch (picked_id)
	{
	case 0:
		std::cout << "J0" << std::endl;
		_arm._joint_0.rotateX(anti_clockwise, angle);
		break;
	case 1:
		std::cout << "J1" << std::endl;
		_arm._joint_1.rotateX(anti_clockwise, angle);
		break;
	case 2:
		_arm._joint_2.rotateX(anti_clockwise, angle);
		std::cout << "J2" << std::endl;
		break;
	case 3:
		_arm._joint_3.rotateX(anti_clockwise, angle);
		std::cout << "J3" << std::endl;
		break;
	case 4:
		_box.rotateX(anti_clockwise, angle);
		std::cout << "BOX" << std::endl;
		break;
	default:
		this->rotateX(anti_clockwise ,angle);
		std::cout << "BACKGROUND" << std::endl;
		break;
	}
}
