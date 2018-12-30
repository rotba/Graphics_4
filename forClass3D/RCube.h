#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Wall.h"
#include "mesh.h"
#include "shader.h"
using namespace glm;
static const float DELTA = 2.0;
static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;

class RCube
{
public:
	RCube(int size, Mesh* mesh, Shader* shader);

	void translateRCube(glm::vec3 transVec);
	void rotateRCube(float angle ,glm::vec3 rotateVec);
	void scaleRCube(float scaleFactor);
	void render();
	void printStuff(char* stuff);
	void printStuff(double stuff);
	void halfAngle();
	void reverseRotaion();
	void doubleAngle();
	void rotateRWall();
	void rotateLWall();
	void rotateDWall();
	void rotateUWall();
	void rotateFWall();
	void rotateBWall();

	virtual ~RCube();
protected:
private:
	void handleRL(int x, int y, int z, Location* location);
	void handleDU(int x, int y, int z, Location* location);
	void handleFB(int x, int y, int z, Location* location);
	void rotateWall(Wall* wall);
	const int _size;
	Cube**** _cubes;
	Location**** _allLocations;
	Mesh* _mesh;
	Shader* _shader;
	const int _isEven;
	float _angle;
	bool _clockwise;
	bool _test;
	Wall _RWall;
	Wall _LWall;
	Wall _UWall;
	Wall _DWall;
	Wall _FWall;
	Wall _BWall;
};
