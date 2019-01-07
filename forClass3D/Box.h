#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Joint.h"
using namespace glm;
class Box: public Transformable
{
public:
	Box(mat4 P, mat4 T, mat4* Tscene, mat4* Rscene, Camera* camera);
	mat4 getMVP();
	mat4 getM();
	vec3 getCenter();
	void setPickingColor(vec4 picking_color);
	vec4 getPickingColor();
	void rotateScene(mat4 ro);
	virtual void translate(vec3 trans);
	virtual void rotateX(bool anti_clockwise, float angle);
	virtual void rotateZ(bool anti_clockwise, float angle);
	virtual void zoom(bool in, float delta);
private:
	mat4 _P;
	mat4 _T;
	mat4 _Rphi;
	mat4 _Rtheta;
	mat4 _Rpsi;
	mat4 _Rjunk;
	mat4 _Thight;
	mat4 *_Tscene;
	mat4 *_Rscene;
	mat4 _S;
	Camera* _camera;
	vec4 _picking_color;
};