#include "Transforamble.h"
#include <iostream>
using namespace std;
void Transformable::printEulerEngles()
{
	cout << "Phi matrix:" << endl;
	print_matrix(_Rphi);
	cout << "Theta matrix:" << endl;
	print_matrix(_Rtheta);
	cout << "Psi matrix:" << endl;
	print_matrix(_Rpsi);
}
void Transformable::print_matrix(mat4 M) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}
