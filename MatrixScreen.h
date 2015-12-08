#ifndef MATRIXSCREEN_H
#define MATRIXSCREEN_H
#include <vector>
#include "ConsoleBuffer.h"
#include "Size.h"
#include "ScreenElement.h"

namespace Printer {

	class MatrixScreen {
		private:
			Size size;
			vector<ScreenElement*> screen;
			ConsoleBuffer screenBuffer;

			bool updatedEl;
			bool updatedScr;

		public:
			MatrixScreen(Size s) :	size(s),
									screenBuffer(s),
									updatedEl(false),
									updatedScr(false) {}

			Size getSize() { return this->size; }

			void addMatrix(Matrix *m, Point *p, direction d, int speed) {
				ScreenElement *el = new ScreenElement(p, m);
				el->setDirection(d);
				el->setSpeed(speed);

				this->screen.push_back(el);
			}

			void updateElements() {
				for (ScreenElement *m : this->screen) {
					m->updateMove();
				}

				this->updatedEl = true;
			}

			void updateScreen() {
				//Matrix *mscreen = new Matrix(this->getSize().getWidth(), this->getSize().getHeight());
				//mscreen->setContents(' ');

//				for (ScreenElement* m : this->screen) {
//					for (int j = 0; j < m->getMatrix()->getSize().getHeight(); j++)
//						for (int i = 0; i < m->getMatrix()->getSize().getWidth(); i++)
//							if ((m->getPos()->getY() + j) < this->getSize().getHeight() && (m->getPos()->getX() + i) < this->getSize().getWidth())
//								mscreen->getMatrix()[m->getPos()->getY() + j][m->getPos()->getX() + i] = m->getMatrix()->getMatrix()[j][i];
//				}

				//for (int i = 0; i < this->getSize().getHeight(); i++)
				//	mscreen->getMatrix()[i][this->getSize().getWidth() - 1] = '\n';

				if (!this->updatedEl)	this->updateElements();
				if (this->updatedScr)	return;

				this->screenBuffer.clear();

				Point nPos(0, 0);

				for (ScreenElement *m : this->screen)
					for (int j = 0; j < m->getMatrix()->getSize().getHeight(); j++)
						for (int i = 0; i < m->getMatrix()->getSize().getWidth(); i++) {
							nPos.setX(m->getPos()->getX() + i);
							nPos.setY(m->getPos()->getY() + j);

							if (posInBounds(nPos))
								this->screenBuffer.putAt(m->getMatrix()->getMatrix()[j][i], nPos);
						}

				this->updatedScr = true;
			}

			void printScreen() {
				if (!this->updatedScr) this->updateScreen();

				this->screenBuffer.sync();

				this->updatedEl = this->updatedScr = false;
			}

			bool posInBounds(Point p) {
				return	   p.getX() < this->getSize().getWidth()
						&& p.getY() < this->getSize().getHeight()
						&& p.getX() >= 0
						&& p.getY() >= 0;
			}
	};
}


#endif // MATRIXSCREEN_H
