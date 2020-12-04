#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

	template <typename T> void swap(T &a, T &b) {
		T c = a;
		a = b;
		b = c;
	}

}

#endif
