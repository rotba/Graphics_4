#include "Wall.h"
#include <math.h>

Wall::Wall(int size, glm::vec3 axis, bool defaultCW) :_size(size), _axis(axis), _defaultCW(defaultCW){
	_locations = new Location**[_size];
	for (int i = 0; i < _size; i++)
	{
		_locations[i] = new Location*[_size];
	}
}
Wall::~Wall() {}
void Wall::setLocation(int i, int j, Location* location) {
	_locations[i][j] = location;
}
void Wall::rotateWall(float angle, bool clockwise) {
	if (angle  == 180) {
		rotateWall(angle / 2, clockwise);
		rotateWall(angle / 2, clockwise);
		return;
	}
	float cwFactor = 1;
	if (clockwise) cwFactor = -1;
	vec3 rotAx = cwFactor * _axis;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_locations[i][j]->getCube()->tranformWallCube(
				rotate(angle, rotAx)
			);
		}
	}
	_currChangeAngle += angle * cwFactor;
	Cube* tmp = _locations[0][0]->getCube();
	if (compleetedQuarterRotation()) {
		if ((_defaultCW && clockwise) || (!_defaultCW && !clockwise)) {
			swap(&tmp, &_locations[2][0]->_cube);
			swap(&tmp, &_locations[2][2]->_cube);
			swap(&tmp, &_locations[0][2]->_cube);
			swap(&tmp, &_locations[0][0]->_cube);
			tmp = _locations[1][0]->_cube;
			swap(&tmp, &_locations[2][1]->_cube);
			swap(&tmp, &_locations[1][2]->_cube);
			swap(&tmp, &_locations[0][1]->_cube);
			swap(&tmp, &_locations[1][0]->_cube);
		}
		else {
			swap(&tmp, &_locations[0][2]->_cube);
			swap(&tmp, &_locations[2][2]->_cube);
			swap(&tmp, &_locations[2][0]->_cube);
			swap(&tmp, &_locations[0][0]->_cube);
			tmp = _locations[1][0]->_cube;
			swap(&tmp, &_locations[0][1]->_cube);
			swap(&tmp, &_locations[1][2]->_cube);
			swap(&tmp, &_locations[2][1]->_cube);
			swap(&tmp, &_locations[1][0]->_cube);
		}
	}
	
	if (compleetedQuarterRotation()) {
		_currChangeAngle = 0;
	}
}
bool Wall::isTwisted() {
	return _currChangeAngle != 0;
}
bool Wall::compleetedQuarterRotation() {
	return _currChangeAngle != 0 && (fmod(_currChangeAngle, 90.0f) == 0.0);
}

void Wall::swap(Cube **r, Cube **l) {
	Cube* temp = *r;
	*r = *l;
	*l = temp;
	return;
}

