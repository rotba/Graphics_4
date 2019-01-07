#pragma once
#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
class Camera
{
public:
	Camera(vec3 up, vec3 forward,vec3 pos, vec3 center,mat4 perspective);
	mat4 getLookAt();
	vec3 getForward();
private:
	vec3 _up;
	vec3 _forward;
	vec3 _pos;
	vec3 _center;
	mat4 _perspective;
};