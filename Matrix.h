#ifndef MATRIX_H
#define MATRIX_H
#include "Size.h"

using namespace std;

namespace Printer {

	class Matrix {
		private:
			const Size size;
			char **matrix;

		public:
			Matrix(size_t width, size_t height) : size(width, height) {
				matrix = alloc::allocArray<char>(this->getSize().getHeight(),this->getSize().getWidth());
			}

			Matrix(size_t width, size_t height, char c) : Matrix(width, height) {
				this->setContents(c);
			}

			~Matrix()			{ delete matrix; }

			Size getSize()		{ return this->size; }

			char **getMatrix()	{ return this->matrix; }

			void setContents(char c) {
				for (int i = 0; i < this->getSize().getHeight(); i++)
					for (int j = 0; j < this->getSize().getWidth(); j++)
						this->getMatrix()[i][j] = c;
			}

			string getContents() {
				string s;

				for (int i = 0; i < this->getSize().getHeight(); i++) {
					for (int j = 0; j < this->getSize().getWidth(); j++)
						s += this->getMatrix()[i][j];
					if (this->getSize().getWidth() < CONSOLE_SIZE) s += '\n';
				}

				return s;
			}
	};

}
#endif // MATRIX_H
