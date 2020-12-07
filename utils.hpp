#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

	template <typename T> void swap(T &a, T &b) {
		T c = a;
		a = b;
		b = c;
	}

	template<typename T>
	typename T::difference_type distance(T first, T last) {
		return (last.getPtr() - first.getPtr());
	}

}

#endif
