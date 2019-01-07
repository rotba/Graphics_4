#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Arm.h"
#include "Box.h"
#include "Camera.h"
#include "texture.h"
#include <math.h>

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;
static const int SOLVER_SOFTER = 5000;
static const vec3 UP = vec3(0,0,-1);
static const vec3 FORWARD = vec3(0, 1, 0);
static const vec3 POSITION = vec3(0, -15, 0);
static const vec3 CENTER = vec3(0, 0, -5);
static const float EPSILON = 0.3;
static float EULER = false;
static vec4 J0_PC;
static vec4 J1_PC;
static vec4 J2_PC;
static vec4 J3_PC;
static vec4 BOX_PC;

void static generatePickingColors() {
	vec4* objects[5]{&J0_PC, &J1_PC , &J2_PC , &J3_PC , &BOX_PC};
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		int r = (i & 0x000000FF) >> 0;
		int g = (i & 0x0000FF00) >> 8;
		int b = (i & 0x00FF0000) >> 16;
		*objects[i] = (vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f));
	}
}
class Scene: public Transformable
{
public:
	Scene(Mesh* cube_mesh, Mesh* rf_mesh, Shader* shader, Shader* picking_shader,Texture* cube_tex, Texture* box_tex);
	void render();
	void solve();
	Camera* getCamera();
	mat4 getT();
	Transformable* getPickedObject(int picked_id);
	bool cannotReach();
	virtual void translate(vec3 trans);
	virtual void rotateX(bool anti_clockwise, float angle);
	virtual void rotateZ(bool anti_clockwise, float angle);
	virtual void zoom(bool in, float delta);
	virtual mat4 getM();
	bool isDone();
	void setEuler();
	Camera _camera;
	Arm _arm;
	Box _box;
	Mesh* _cube_mesh;
	void updatePickingShader();
	virtual ~Scene();
private:
	void updateChildren();
	float calculatePhi(vec3 RE, vec3 RD);
	float calculateTheta(vec3 RE, vec3 RD);
	bool antiClockwiseTheta(vec3 RE, vec3 RD);
	mat4 _T;
	mat4 _R;
	mat4 _Rjunk;
	mat4 _Thight;
	mat4 _S;
	Mesh* _rf_mesh;
	Texture* _cube_tex;
	Texture* _box_tex;
	Shader* _shader;
	Shader* _picking_shader;
	int curr_joint = 3;
};
