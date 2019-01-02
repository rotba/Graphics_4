#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Arm.h"
#include "Box.h"
#include "Camera.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
static const vec3 UP = vec3(0,0,-1);
static const vec3 FORWARD = vec3(0, 1, 0);
static const vec3 POSITION = vec3(0, -30, 0);
static const vec3 CENTER = vec3(0, 0, -5);
static const float EPSILON = 0.3;
class Scene
{
public:
	Scene(Mesh* mesh, Shader* shader);
	void render();
	void solve();
	Camera* getCamera();
	mat4 getT();
	Camera _camera;
	Arm _arm;
	Box _box;
	virtual ~Scene();
private:
	mat4 _T;
	Mesh* _cube_mesh;
	Shader* _shader;
};
