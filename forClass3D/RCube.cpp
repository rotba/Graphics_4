#include "RCube.h"
#include <iostream>

RCube::RCube(int size, Mesh* mesh, Shader* shader):_size(size), _isEven( 1 - size % 2), _mesh(mesh), _shader(shader),_angle(90.0f), _clockwise(false),
_RWall(_size, vec3(-1,0,0),true), _LWall(_size, vec3(1,0,0), false),
_DWall(_size, vec3(0,-1,0),false), _UWall(_size,vec3(0,1,0), true),
_FWall(_size,vec3(0,0,-1), true), _BWall (_size,vec3(0,0,1), false)
{
	vec3 pos = vec3(0, 0, -12);
	vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	vec3 right = glm::vec3(-1.0f, 0.0f, 0.0f);
	mat4 P = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	mat4 M = glm::rotate(0.0f, vec3(1, 0, 0));//glm::mat4(1);
	P = P * glm::lookAt(pos - vec3(0, 0, 1), pos + forward, up);
	mat4 MVP = P * M;
	float rightBottomCorner = -(size / 2)*DELTA + (_isEven*0.5)*DELTA;
	_cubes = new Cube***[_size];
	_allLocations = new Location***[_size];
	for (int x = 0; x < _size; x++)
	{
		_cubes[x] = new Cube**[_size];
		_allLocations[x] = new Location**[_size];
		for (int y = 0; y < _size; y++)
		{
			_cubes[x][y] = new Cube*[_size];
			_allLocations[x][y] = new Location*[_size];
			for (int z = 0; z < _size; z++)
			{
				mat4 trans = translate(
					vec3(
						rightBottomCorner + DELTA * x,
						rightBottomCorner + DELTA * y,
						rightBottomCorner + DELTA * z)
				);
				_cubes[x][y][z] = new Cube(P,M, trans, mat4(1));
				_allLocations[x][y][z] = new Location(_cubes[x][y][z], x,y,z);
				handleRL(x,y,z, _allLocations[x][y][z]);
				handleDU(x, y, z, _allLocations[x][y][z]);
				handleFB(x, y, z, _allLocations[x][y][z]);

			}
		}
	}
}

RCube::~RCube()
{
	
}
void RCube::handleRL(int x, int y, int z, Location* location) {
	if (x == 0) {
		_RWall.setLocation(y, z,location);
	}
	else if (x == (_size -1)) {
		_LWall.setLocation(y, z, location);
	}
}
void RCube::handleDU(int x, int y, int z, Location* location) {
	if (y == 0) {
		_DWall.setLocation(x, z, location);
	}
	else if (y == (_size - 1)) {
		_UWall.setLocation(x, z, location);
	}
}
void RCube::handleFB(int x, int y, int z, Location* location) {
	if (z == 0) {
		_FWall.setLocation(x, y, location);
	}
	else if (z == (_size - 1)) {
		_BWall.setLocation(x, y, location);
	}
}
void RCube::render() {
	_shader->Bind();
	/*for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			for (int z = 0; z < _size; z++)
			{
				_shader->Update(_cubes[x][y][z]->getMVP(), _cubes[x][y][z]->getM());
				_mesh->Draw();
			}
		}
	}*/
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			for (int z = 0; z < _size; z++)
			{
				//if((x ==0) && (y== 0) && (z == 2)) {
					//_test = false;
					_shader->Update(_cubes[x][y][z]->getMVP(), _cubes[x][y][z]->getM());
					_mesh->Draw();
				//}
			}
		}
	}
}
void RCube::printStuff(char * stuff)
{
	std::cout<<stuff<<std::endl;
}
void RCube::printStuff(double stuff)
{
	std::cout << stuff << std::endl;
}
void RCube::halfAngle()
{
	_angle *= 0.5;
}
void RCube::doubleAngle()
{
	if (_angle*2>180) {
		return;
	}
	_angle *= 2;
}
void RCube::rotateRWall()
{
	if (_UWall.isTwisted() ||
		_DWall.isTwisted() || 
		_FWall.isTwisted() || 
		_BWall.isTwisted()) 
	{
		return;
	}
	rotateWall(&_RWall);
}
void RCube::rotateLWall()
{
	if (_UWall.isTwisted() ||
		_DWall.isTwisted() ||
		_FWall.isTwisted() ||
		_BWall.isTwisted())
	{
		return;
	}
	rotateWall(&_LWall);
}
void RCube::rotateDWall()
{
	if (_RWall.isTwisted() ||
		_LWall.isTwisted() ||
		_FWall.isTwisted() ||
		_BWall.isTwisted())
	{
		return;
	}
	rotateWall(&_DWall);
}
void RCube::rotateUWall()
{
	if (_RWall.isTwisted() ||
		_LWall.isTwisted() ||
		_FWall.isTwisted() ||
		_BWall.isTwisted())
	{
		return;
	}
	rotateWall(&_UWall);
}
void RCube::rotateFWall()
{
	if (_RWall.isTwisted() ||
		_LWall.isTwisted() ||
		_UWall.isTwisted() ||
		_DWall.isTwisted())
	{
		return;
	}
	rotateWall(&_FWall);
}
void RCube::rotateBWall()
{
	if (_RWall.isTwisted() ||
		_LWall.isTwisted() ||
		_UWall.isTwisted() ||
		_DWall.isTwisted())
	{
		return;
	}
	rotateWall(&_BWall);
}
void RCube::rotateWall(Wall* wall)
{
	wall->rotateWall(_angle, _clockwise);
}
void RCube::reverseRotaion() {
	_clockwise = !_clockwise;
}
void RCube::translateRCube(vec3 transVec)
{
	mat4 trans = translate(transVec);
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			for (int z = 0; z < _size; z++)
			{
				_cubes[x][y][z]->tranformRCube(trans);
			}
		}
	}
}
void RCube::rotateRCube(float angle, glm::vec3 rotateVec)
{
	mat4 rotate = glm::rotate(angle,rotateVec);
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			for (int z = 0; z < _size; z++)
			{
				_cubes[x][y][z]->rotateRRCube(rotate);
			}
		}
	}
}
void RCube::scaleRCube(float scaleFactor)
{
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			for (int z = 0; z < _size; z++)
			{
				_cubes[x][y][z]->scaleCube(scaleFactor);
			}
		}
	}
}