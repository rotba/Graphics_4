#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Arm.h"
#include "Box.h"
#include "Camera.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
class Scene
{
public:
	Scene(Mesh* mesh, Shader* shader);
	void render();
	Camera* getCamera();
	mat4 getT();
	virtual ~Scene();
private:
	Camera _camera;
	Arm _arm;
	Box _box;
	mat4 _T;
	Mesh* _cube_mesh;
	Shader* _shader;
};
