#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 ) {
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

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
