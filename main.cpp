#include <iostream>
#include "Utils.h"
#include "MatrixScreen.h"

using namespace std;
using namespace Printer;

int main() {
	MatrixScreen s(Size(80, 20));

//	Matrix m(3, 8, 'c');
//	Matrix n(5, 5, 'p');

//	s.addMatrix(&m, new Point(-1, 0), direction::RIGHT, 1);
//	s.addMatrix(&n, new Point(10, 9), direction::UP, 1);

	Matrix	*adding = new Matrix(1, 1, '>'),
			*bdding = new Matrix(1, 1, '<');

	for(int i = 0; i < s.getSize().getHeight(); i++) {
		s.addMatrix(adding, new Point(-5 - i, i), direction::RIGHT, 1);
		s.addMatrix(bdding, new Point(85 + i, i), direction::LEFT, 1);
	}

	while(1) {
		//system("CLS");

		s.printScreen();

		Sleep(100);

		//putchar('\n');
		//system("PAUSE");
	}


	return 0;
}

