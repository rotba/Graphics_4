#pragma once
#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
class Box
{
public:
	Box(mat4 P, mat4 R, mat4 T, mat4 S);

	mat4 getMVP();
	mat4 getM();
	void translateBox(vec3 transVec);
	void tranformBox(mat4 mat);
	void scaleBox(float scaleFactor);
private:
	mat4 _P;
	mat4 _R;
	mat4 _T;
	mat4 _S;
};