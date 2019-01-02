#pragma once
#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;
class Joint
{
public:
	Joint(Joint* prev , mat4 Tarm, mat4 P);
	mat4 getMVP();
	mat4 getPrev();
	mat4 getM();
	vec3 getRoot();
	vec3 getEnd();
	void rotate(float a, vec3 axis);
	void rotateX(bool clockwise, float angle);
	void rotateZ(bool clockwise, float angle);
private:
	mat4 _R;
	mat4 _Thight;
	mat4 _S;
	mat4 _Tarm;
	mat4 _P;
	Joint* _prev;
};
