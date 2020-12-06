#ifndef ITERATORVECTOR_HPP
#define ITERATORVECTOR_HPP

#include "iteratorList.hpp"

namespace ft {

	template<typename T, typename Category = bidirectional_iterator_tag>
	class IteratorVector {

		private:
			T	*_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			IteratorVector() {}
			IteratorVector(const IteratorVector& other) { _ptr = other._ptr; }
			IteratorVector(pointer ptr) { _ptr = ptr; }
			~IteratorVector() {}

			T* getPtr() { return (_ptr); }

			IteratorVector& operator=(const IteratorVector& other) {
				_ptr = other._ptr;
				return (*this);
			}

			bool 			operator==(const IteratorVector& other) {
				return (_ptr == other._ptr);
			}

			bool 			operator!=(const IteratorVector& other) {
				return (_ptr != other._ptr);
			}

			reference		operator*() {
				return (*_ptr);
			}

			pointer 		operator->() const {
				return (_ptr);
			}

			IteratorVector&	operator++() {
				_ptr++;
				return (*this);
			}

			IteratorVector	operator++(int) {
				IteratorVector<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}

			IteratorVector&	operator--() {
				_ptr--;
				return (*this);
			}

			IteratorVector	operator--(int) {
				IteratorVector<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}


	};

}

#endif
