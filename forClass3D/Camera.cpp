#include "Camera.h"
static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
using namespace glm;
Camera::Camera(vec3 up ,vec3 forward ,vec3 pos, mat4 perspective):_up(up),_forward(forward),_pos(pos), _perspective(perspective){}

mat4 Camera::getLookAt()
{
	_pos = vec3(0,0,-12);
	_forward = vec3(0.0f, 0.0f, 1.0f);
	_up= vec3(0.0f, 1.0f, 0.0f);
	mat4 tnp = _perspective * lookAt(_pos - vec3(0, 0, 1), _pos + _forward, _up);
	return tnp;
}
