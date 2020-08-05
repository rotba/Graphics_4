#include "Location.h"

Location::Location(Cube* cube, int x, int y, int z) :_cube(cube), _x(x), _y(y), _z(z) {}
Location::~Location() {}
Cube* Location::getCube() { return _cube; }
void Location::setCube(Cube* cube) { _cube = cube; }
int Location::getX() { return _x; }
int Location::getY() { return _y; }
int Location::getZ() { return _z; }
