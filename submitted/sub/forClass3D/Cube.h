#include "glm\glm.hpp"

class Cube
{
public:
	Cube(glm::mat4 P, glm::mat4 R, glm::mat4 T, glm::mat4 S);

	glm::mat4 getMVP();
	glm::mat4 getM();
	void setP(glm::mat4 P);
	void setR(glm::mat4 R);
	void setT(glm::mat4 T);
	void setS(glm::mat4 S);
	void translateCube(glm::vec3 transVec);
	void tranformRCube(glm::mat4 mat);
	void tranformWallCube(glm::mat4 mat);
	void rotateRRCube(glm::mat4 mat);
	void rotateCube(float angle,glm::vec3 rotateVec);
	void scaleCube(float scaleFactor);

	virtual ~Cube();
private:
	glm::mat4 _P;
	glm::mat4 _R;
	glm::mat4 _T;
	glm::mat4 _S;
	glm::mat4 _Trel;
	glm::mat4 _Trot;
	glm::mat4 _Twall;
};

