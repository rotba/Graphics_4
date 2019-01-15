#include "Scene.h"
#include <iostream>

using namespace std;
Scene::Scene(Mesh* cube_mesh, Mesh* rf_mesh, Shader* shader, Shader* picking_shader, Texture* cube_tex, Texture* box_tex):
	_camera(UP, FORWARD,POSITION, CENTER, perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f)),
	_arm(_camera.getLookAt(), mat4(1), &_T, &_R, &_camera),
	_box(_camera.getLookAt(), glm::translate(vec3(5.0f,0.0f,0.0f)), &_T, &_R,&_camera),
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
	if (cannotReach()) {
		cout << "Cannot reach" << endl;
		return;
	}
	Joint** joints = new Joint*[4];
	joints[0] = &_arm._joint_0;
	joints[1] = &_arm._joint_1;
	joints[2] = &_arm._joint_2;
	joints[3] = &_arm._joint_3;
	vec3 D = _box.getCenter();
	vec3 R = joints[curr_joint]->getRoot();
	vec3 E_tag = joints[curr_joint]->getEnd();
	vec3 E = _arm.getEnd();
	vec3 RD = normalize(D-R);
	vec3 RE = normalize(E-R);
	float a = degrees(acos(dot(RD, RE)));
	vec3 axis = normalize(cross(RD, -RE));
	mat4 rot_mat = glm::rotate(a/2,axis);
	vec3 e_angles_rad = rotationMatrixToEulerAngles(rot_mat);
	vec3 e_angles_ang = vec3(degrees(e_angles_rad.x), degrees(e_angles_rad.y), degrees(e_angles_rad.z));
	int x = 1;
	if (EULER) {
		/*float theta = 0;
		float phi = 0;
		if (RD.x==0 && RD.y ==0){ 
			theta =a;
			joints[curr_joint]->rotateX(true, theta);
		}
		else if (RE.x == 0 && RE.y == 0) {
			theta = a;
			joints[curr_joint]->rotateX(D.x > 0 , theta/2 );
			vec3 RE_tag = normalize(_arm.getEnd() - R);
			phi = calculatePhi(RE_tag, RD);
			joints[curr_joint]->rotateZ(true, phi);
			int x = 1;
		}else {
			theta = calculateTheta(RE,RD);
			bool antiClockwise = antiClockwiseTheta(RE, RD, joints[curr_joint]);
			joints[curr_joint]->rotateX(antiClockwise, theta/2);
			vec3 RE_tag = normalize(joints[curr_joint]->getEnd() - R);
			phi = calculatePhi(RE_tag, RD);
			joints[curr_joint]->rotateZ(true, phi);
		}*/
		mat4 theta = glm::rotate(e_angles_ang.x, vec3(-1,0,0));
		mat4 psi = glm::rotate(e_angles_ang.y, vec3(0, -1, 0));
		mat4 phi = glm::rotate(e_angles_ang.z, vec3(0, 0, -1));
		joints[curr_joint]->rotateTheta(theta);
		joints[curr_joint]->rotatePsi(psi);
		joints[curr_joint]->rotatePhi(phi);
		joints[curr_joint]->rotateTmp(phi*psi*theta);
	}
	else {
		joints[curr_joint]->rotate(a/2, axis);
	}
	vec3 check = _arm.getEnd();
	if (curr_joint == 0) {
		curr_joint = 3;
	}
	else {
		curr_joint -=1;
	}
}
float Scene::calculatePhi(vec3 RE, vec3 RD)
{
	vec2 RE_xy = normalize(vec2(RE.x, RE.y));
	vec2 RD_xy = normalize(vec2(RD.x, RD.y));
	float  cos_phi = dot(RE_xy, RD_xy);
	if (abs(cos_phi) > 1) {
		return 0;
	}
	float phi_in_radians = acos(cos_phi);
	cout << "PHI: " << degrees(phi_in_radians) << endl;
	float DEBUG = degrees(phi_in_radians);
	return degrees(phi_in_radians);
}

float Scene::calculateTheta(vec3 RE, vec3 RD)
{
	vec2 RE_xz = normalize(vec2(RE.x, RE.z));
	vec2 RD_xz = normalize(vec2(RD.x, RD.z));
	float cos_theta = dot(RE_xz, RD_xz);
	if (abs(cos_theta) > 1) {
		return 0;
	}
	float theta_in_radians = acos(cos_theta);
	cout<<"THETA: " <<degrees(theta_in_radians)  <<endl;
	return degrees(theta_in_radians);
}

bool Scene::antiClockwiseTheta(vec3 RE, vec3 RD, Joint* curr_joint)
{
	vec3 proj_RE = vec3(RE.x, 0, RE.z);
	vec3 proj_RD = vec3(RD.x, 0, RD.z);
	//vec3 up = (vec3)(curr_joint->getR()*vec4(0, -1, 0, 1));
	vec3 up = (vec3)vec4(0, -1, 0, 1);
	vec3 right = cross(proj_RE, up);
	float dot_product = dot(right, proj_RD);
	return dot_product < 0;
	return true;
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
		std::cout << "J0" << std::endl;
		return &_arm._joint_0;
		break;
	case 1:
		std::cout << "J1" << std::endl;
		return &_arm._joint_1;
		break;
	case 2:
		std::cout << "J2" << std::endl;
		return &_arm._joint_2;
		break;
	case 3:
		std::cout << "J3" << std::endl;
		return &_arm._joint_3;
		break;
	case 4:		
		std::cout << "BOX" << std::endl;
		return &_box;
		break;
	default:		
		std::cout << "SCENE" << std::endl;
		return this;
		break;
	}
}

bool Scene::cannotReach()
{
	return distance(_arm.getRoot(), _box.getCenter()) >16;
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
mat4 Scene::getM()
{
	return mat4();
}
void Scene::updateChildren()
{
	_R= _Rpsi* _Rtheta*_Rphi*_Rjunk*_S;
}

bool Scene::isDone()
{
	vec3 D = _box.getCenter();
	return distance(_arm.getEnd(), D)<=EPSILON;
}

void Scene::setEuler()
{
	if (EULER) {
		cout << "Vector rotation IK solver" << endl;
	}
	else {
		cout << "Euler angles IK solver" << endl;
	}
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

