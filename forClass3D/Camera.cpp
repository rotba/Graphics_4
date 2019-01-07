#include "Camera.h"
static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
using namespace glm;
Camera::Camera(vec3 up ,vec3 forward ,vec3 pos, vec3 center,mat4 perspective):_up(up),_forward(forward),_pos(pos), _center(center),_perspective(perspective){}

mat4 Camera::getLookAt()
{
	return _perspective * lookAt(_pos - vec3(0, 0, 1), _center, _up);
}

vec3 Camera::getForward()
{
	return _forward;
}
