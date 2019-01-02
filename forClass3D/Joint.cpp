#include "Joint.h"


Joint::Joint(Joint* prev, mat4 Thight, mat4 Tarm, mat4 P): _prev(prev), _Thight(Thight), _Tarm(Tarm),_S(mat4(1)), _P(P){}

mat4 Joint::getMVP()
{
	return _P*_S*_Tarm*getPrevR()*_Thight*_R;
}

mat4 Joint::getM()
{
	return _S * _Tarm*getPrevR()*_Thight*_R;
}

mat4 Joint::getPrevR()
{
	if (_prev == nullptr) {
		return _R;
	}
	else {
		return (_prev->getR())*_R;
	}
}

mat4 Joint::getR()
{
	if (_prev ==nullptr) {
		return _R;
	}
	else {
		return (_prev->getR())*_R;
	}
}
