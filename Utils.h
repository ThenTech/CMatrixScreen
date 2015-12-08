#ifndef UTILS
#define UTILS

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

	enum class direction { NONE, UP, DOWN, LEFT, RIGHT};

	void putChar(char c, size_t i) {
		while (i--) putchar(c);
	}

}

#endif // UTILS

