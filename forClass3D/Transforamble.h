#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
class Transformable {
public:
	// pure virtual function
	virtual void translate(vec3 trans) = 0;
	virtual void rotateX(bool anti_clockwise, float angle) = 0;
	virtual void rotateZ(bool anti_clockwise, float angle) = 0;
	virtual void zoom(bool in, float delta) = 0;
	virtual mat4 getM() = 0;
	void printEulerEngles();

protected:
	mat4 _Rphi;
	mat4 _Rtheta;
	mat4 _Rpsi;
private:
	void print_matrix(mat4 M);
	
};