#include "Camera.h"
static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
using namespace glm;
Camera::Camera(vec3 up ,vec3 forward ,vec3 pos, vec3 center,mat4 perspective):_up(up),_forward(forward),_pos(pos), _center(center),_perspective(perspective){}

mat4 Camera::getLookAt()
{
	return _perspective * lookAt(_pos , _center, _up);
}

mat4 Camera::getLookAt2()
{
	return lookAt(_pos, _center, _up);
}

mat4 Camera::getPerspective()
{
	return _perspective;
}

vec3 Camera::getForward()
{
	return _forward;
}
