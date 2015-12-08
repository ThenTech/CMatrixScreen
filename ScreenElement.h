#ifndef SCREENELEMENT_H
#define SCREENELEMENT_H
#include <iostream>
#include "Point.h"
#include "Matrix.h"

namespace Printer {

	class ScreenElement {
		private:
			Point *pos;
			Matrix *m;
			direction dir;
			size_t speed;

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

		public:
			ScreenElement(Point *pos, Matrix *m) : pos(pos), m(m) {}

			void setDirection(direction d)	{ this->dir = d; }
			void setSpeed(size_t s)			{ this->speed = s; }

			Point* getPos()		{ return this->pos; }

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

}

#endif // SCREENELEMENT_H
