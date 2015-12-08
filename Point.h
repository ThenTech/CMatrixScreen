#ifndef POINT_H
#define POINT_H

namespace Printer {

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

}

#endif // POINT_H
