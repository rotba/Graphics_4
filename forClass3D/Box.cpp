#include "Box.h"

Box::Box(mat4 P, mat4 R, mat4 T, mat4 S): _P(P), _R(R), _T(T), _S(S){}

mat4 Box::getMVP()
{
	return _P*_S*_T*_R;
}

mat4 Box::getM()
{
	return _S*_T*_R;
}

vec3 Box::getCenter()
{
	return (vec3)(getMVP() * vec4(0, 0, 0, 1));
}
