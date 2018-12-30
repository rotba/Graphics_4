#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Location.h"

using namespace glm;
class Wall
{
public:
	Wall(int size, glm::vec3 axis, bool defaultCW);
	void setLocation(int i, int j, Location* location);
	void rotateWall(float angle ,bool clockwise);
	bool isTwisted();

	virtual ~Wall();
protected:
private:
	bool compleetedQuarterRotation();
	void swap(Cube **r, Cube **l);
	Location*** _locations;
	const bool _defaultCW;
	int _size;
	glm::vec3 _axis;
	float _currChangeAngle;

};

