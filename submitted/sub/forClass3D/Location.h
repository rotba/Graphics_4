#include "glm\glm.hpp"
#include "Cube.h"

class Location
{
public:
	Location(Cube* cube, int x, int y, int z);
	Cube* getCube();
	void setCube(Cube* cube);
	int getX();
	int getY();
	int getZ();

	virtual ~Location();
	Cube* _cube;
protected:
private:
	const int _x;
	const int _y;
	const int _z;

};

