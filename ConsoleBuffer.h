#ifndef CONSOLEBUFFER_H
#define CONSOLEBUFFER_H
#include <Windows.h>
#include <iostream>
#include <vector>

#include "Utils.h"
#include "Size.h"

using namespace std;

namespace Printer {

	class ConsoleBuffer {
		private:
			vector< vector<char> > cur;
			vector< vector<char> > next;

		public:
			ConsoleBuffer(Size s) :	cur (s.getHeight(), vector<char>(s.getWidth(), ' ')),
									next(s.getHeight(), vector<char>(s.getWidth(), ' '))
			{
				for (int i = 0; i < s.getHeight(); i++)
					this->putAt('\n', Point(s.getWidth() - 1, i));
			}

			void sync() {
				// Loop over all positions
				for (int row = 0; row < cur.size(); ++row)
					for (int col = 0; col < cur[row].size(); ++col)
						// If the character at this position has changed
						if (cur[row][col] != next[row][col]) {
							// Move cursor to position
							//COORD c = {row, col};
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {col, row});
							cout.put(next[row][col]); // Overwrite character
						}

				cur = next; // 'next' is the new 'cur'
			}

			void clear() {
				vector< vector<char> > empty(cur.size(), vector<char>(cur[0].size(), ' '));
				next.swap(empty);
			}

			void putAt(char c, Point p) {
				next[p.getY()][p.getX()] = c;
			}
	};

}

#endif // CONSOLEBUFFER_H
