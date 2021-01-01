#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

	template <typename T> T min(T a, T b) {
		return (a > b ? b : a);
	}

	template <typename T> void swap(T &a, T &b) {
		T c;
		c = a;
		a = b;
		b = c;
	}

	template<typename T>
	typename T::difference_type distance(T first, T last) {
		return (last.getPtr() - first.getPtr());
	}

}

#endif
