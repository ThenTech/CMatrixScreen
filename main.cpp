#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace alloc {
	/**
	 *	Overloaded methods to allocate an array of T of size x, y, z.
	 */
	template <class T>
	static T* allocVar() {
		return new T();
	}

	template <class T>
	static T* allocArray(size_t x) {
		return new T[x]();
	}

	template <class T>
	static T** allocArray(size_t x, size_t y) {
		T **arr = new T*[x];
		for(size_t i = 0; i < x; i++) arr[i] = alloc::allocArray<T>(y);
		return arr;
	}

	template <class T>
	static T*** allocArray(size_t x, size_t y, size_t z) {
		T ***arr = new T**[x];
		for(size_t i = 0; i < x; i++) arr[i] = alloc::allocArray<T>(y, z);
		return arr;
	}
}

namespace Printer {

	static const char CONSOLE_SIZE = 80;

	enum class direction { UP, DOWN, LEFT, RIGHT};

	void putChar(char c, size_t i) {
		while (i--) putchar(c);
	}

	class Point {
		private:
			int x;
			int y;
		public:
			Point(int x, int y) : x(x), y(y) {}

			int getX()			{ return this->x; }
			int getY()			{ return this->y; }

			void setX(int x)	{ this->x = x; }
			void setY(int y)	{ this->y = y; }

			void offset(int x, int y) {
				this->offsetX(x);
				this->offsetX(y);
			}

			void offsetX(int x)	{ this->x += x; }

			void offsetY(int y)	{ this->y += y; }

	};

	class Size {
		private:
			Point *p;
		public:
			Size(size_t width, size_t height) {
				p = new Point(width, height);
			}

			size_t getWidth()	{ return this->p->getX(); }
			size_t getHeight()	{ return this->p->getY(); }
	};

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

	class ScreenElement {
		private:
			Point *pos;
			Matrix *m;
			direction dir;
			size_t speed;

		public:
			ScreenElement(Point *pos, Matrix *m) : pos(pos), m(m)  {}

			void setDirection(direction d)	{ this->dir = d; }
			void setSpeed(size_t s)			{ this->speed = s; }

			Point* getPos()		{ return this->pos; }

			void move(int hor, int ver) {
				this->getPos()->offset(hor, ver);
			}

			void moveUp(int y) {
				this->getPos()->offsetY(-y);
			}

			void moveDown(int y) {
				this->getPos()->offsetY(y);
			}

			void moveRight(int x) {
				this->getPos()->offsetX(x);
			}

			void moveLeft(int x) {
				this->getPos()->offsetX(-x);
			}

			void updateMove() {
				switch (this->dir) {
					case direction::UP:
						this->moveUp(this->speed);
						break;
					case direction::DOWN:
						this->moveDown(this->speed);
						break;
					case direction::LEFT:
						this->moveLeft(this->speed);
						break;
					case direction::RIGHT:
						this->moveRight(this->speed);
						break;
					default:
						break;
				}
			}

			Matrix* getMatrix()	{ return this->m; }
	};

	class MatrixScreen {
		private:
			Size size;
			vector<ScreenElement*> screen;

		public:
			MatrixScreen(size_t width, size_t height) : size(width, height) {}

			Size getSize() { return this->size; }

			void addMatrix(Matrix *m, Point *p, direction d, int speed) {
				ScreenElement *el = new ScreenElement(p, m);
				el->setDirection(d);
				el->setSpeed(speed);

				this->screen.push_back(el);
			}

			void update() {
				for (ScreenElement* m : this->screen) {
					m->updateMove();
				}
			}

			Matrix* getScreen() {
				Matrix *mscreen = new Matrix(this->getSize().getWidth(), this->getSize().getHeight());
				mscreen->setContents(' ');

				for (ScreenElement* m : this->screen) {
					for (int j = 0; j < m->getMatrix()->getSize().getHeight(); j++)
						for (int i = 0; i < m->getMatrix()->getSize().getWidth(); i++)
							if ((m->getPos()->getY() + j) < this->getSize().getHeight() && (m->getPos()->getX() + i) < this->getSize().getWidth())
								mscreen->getMatrix()[m->getPos()->getY() + j][m->getPos()->getX() + i] = m->getMatrix()->getMatrix()[j][i];
				}

				for (int i = 0; i < this->getSize().getHeight(); i++)
					mscreen->getMatrix()[i][this->getSize().getWidth() - 1] = '\n';

				return mscreen;
			}
	};
}

using namespace Printer;

int main() {

	Matrix m(3, 8, 'c');
	Matrix n(5, 5, 'p');


	MatrixScreen s(80,20);

	s.addMatrix(&m, new Point(0, 0), direction::RIGHT, 1);
	s.addMatrix(&n, new Point(10, 10), direction::UP, 1);


	while(1) {
		system("CLS");
		cout << s.getScreen()->getContents();
		s.update();
		//system("PAUSE");
	}


	return 0;
}

