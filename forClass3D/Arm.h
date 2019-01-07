#pragma once
#include "mesh.h"
#include "shader.h"
#include "Joint.h"

class Arm
{
public:
	Arm(mat4 P, mat4 T, mat4 *Tscene, Camera* camera);
	mat4 getT();
	void render(Mesh* cube_mesh, Mesh* rf_mesh,Shader* shader);
	void pickingRender(Mesh* cube_mesh, Mesh* rf_mesh, Shader* shader);
	vec3 getEnd();
	Joint _joint_0;
	Joint _joint_1;
	Joint _joint_2;
	Joint _joint_3;
private:
	Joint* _joints[4];
	mat4 _T;
	mat4 _P;
};
