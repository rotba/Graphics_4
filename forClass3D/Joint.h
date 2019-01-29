#pragma once
#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Transforamble.h"
#include "Camera.h"
using namespace glm;
using namespace std;
static const vec4 ORIGIN = vec4(0, 0, -1, 1);
static const vec4 Z_HAT = vec4(0, 0, 1, 1);
static const vec4 X_HAT = vec4(1, 0, -1, 1);
class Joint: public Transformable
{
public:
	Joint(Joint* prev , mat4 *Tarm, mat4 P, mat4* Tscene,  mat4* Rscene, Camera* camera);
	mat4 getMVP();
	mat4 getPrev();
	mat4 getM();
	mat4 getR();
	mat4 getR2();
	vec3 getRoot();
	vec3 getEnd();
	void setPickingColor(vec4 pickingColor);
	vec4 getPickingColor();
	void rotate(float a, vec3 axis);
	void rotateTmp(mat4 jnk);
	virtual void rotateX(bool clockwise, float angle);
	virtual void rotateZ(bool clockwise, float angle);
	virtual void translate(vec3 trans);
	virtual void zoom(bool in, float delta);
	virtual void printEulerEngles();
	vec3 getW();
	vec3 getU();
	void rotateTheta(vec3 axis, float theta);
	void rotatePsi(vec3 axis, float psi);
	void rotatePhi(vec3 axis,float phi);
private:
	mat4 _Rjunk;
	mat4 _Thight;
	mat4* _Rscene;
	mat4* _Tscene;
	mat4 _S;
	mat4 _base = glm::translate(vec3(0,0,1));
	mat4* _Tarm;
	mat4 _P;
	Camera* _camera;
	vec4 _picking_color;
	Joint* _prev;
};
