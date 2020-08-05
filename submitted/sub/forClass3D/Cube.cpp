#include "Cube.h"
#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

Cube::Cube(glm::mat4 P, glm::mat4 R, glm::mat4 T, glm::mat4 S) :_P(P), _R(R), _T(T), _S(S){
	_Trel = mat4(1);
	_Twall = mat4(1);
	_Trot = mat4(1);
}
Cube::~Cube(){}
glm::mat4 Cube::getMVP() { return _P*_S*_Trel*_Trot*_Twall*_T*_R; }
glm::mat4 Cube::getM() { return _Trel * _Twall * _T*_R; }
void Cube::setP(mat4 P) { _P = P; }
void Cube::setR(mat4 R) { _R = R; }
void Cube::setT(mat4 T) { _T = T; }
void Cube::setS(mat4 S) { _S = S; }
void Cube::translateCube(vec3 transVec)
{
	mat4 trans = glm::translate(transVec);
	_T = _T * trans;
}
void Cube::tranformRCube(glm::mat4 mat) {
	_Trel = mat*_Trel;
}
void Cube::tranformWallCube(glm::mat4 mat) {
	_Twall = mat*_Twall ;
}
void Cube::rotateRRCube(glm::mat4 mat) {
	_Trot = mat * _Trot;
}
void Cube::rotateCube(float angle,vec3 rotateVec)
{
	mat4 rotate = glm::rotate(angle, rotateVec);
	_R = _R * rotate;
}
void Cube::scaleCube(float scaleFactor)
{
	mat4 scale = glm::scale(vec3(scaleFactor,scaleFactor,scaleFactor));
	_S = _S * scale;
}