#ifndef SIZE_H
#define SIZE_H
#include <iostream>

#include "Point.h"

namespace Printer {

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

}

#endif // SIZE_H
