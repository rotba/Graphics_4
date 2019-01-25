#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
static const vec4 STANDARD_X = vec4(1, 0, 0, 0);
static const vec4 STANDARD_Y = vec4(0, 1, 0, 0);
static const vec4 STANDARD_Z = vec4(0, 0, 1, 0);
class Transformable {
public:
	// pure virtual function
	virtual void translate(vec3 trans) = 0;
	virtual void rotateX(bool anti_clockwise, float angle) = 0;
	virtual void rotateZ(bool anti_clockwise, float angle) = 0;
	virtual void zoom(bool in, float delta) = 0;
	virtual mat4 getM() = 0;
	virtual void printEulerEngles();

protected:
	mat4 _Rphi;
	mat4 _Rtheta;
	mat4 _Rpsi;
	mat4 _solverTheta;
	mat4 _solverPsi;
	mat4 _solverPhi;
	void print_matrix(mat4 M);
private:
	
};