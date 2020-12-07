#ifndef ITERATORVECTOR_HPP
#define ITERATORVECTOR_HPP

#include "utils.hpp"

namespace ft {

	template<typename T, typename Category = std::random_access_iterator_tag>
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

			T* 				getPtr() { return (_ptr); }
			bool 			operator==(const IteratorVector& other) {	return (_ptr == other._ptr);	}
			bool 			operator!=(const IteratorVector& other) {	return (_ptr != other._ptr);	}
			reference		operator*() {	return (*_ptr);		}
			pointer 		operator->() const {	return (_ptr);		}
			difference_type operator-(const IteratorVector& other) const {		return (_ptr - other._ptr);		}
			T&				operator[](int n) const {	return (*(this + n));	}
			bool 			operator==(const IteratorVector& other) const {		return (_ptr == other._ptr);		}
			bool 			operator!=(const IteratorVector& other) const {		return (_ptr != other._ptr);		}
			bool 			operator<(const IteratorVector& other) const {		return (_ptr < other._ptr);			}
			bool 			operator>(const IteratorVector& other) const {		return (_ptr > other._ptr);			}
			bool 			operator<=(const IteratorVector& other) const {		return (_ptr <= other._ptr);		}
			bool 			operator>=(const IteratorVector& other) const {		return (_ptr >= other._ptr);		}

			IteratorVector& operator=(const IteratorVector& other) {
				_ptr = other._ptr;
				return (*this);
			}

			IteratorVector&	operator++() {
				++_ptr;
				return (*this);
			}

			IteratorVector	operator++(int) {
				IteratorVector<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}

			IteratorVector&	operator--() {
				--_ptr;
				return (*this);
			}

			IteratorVector	operator--(int) {
				IteratorVector<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

			IteratorVector	operator+(int n) const {
				IteratorVector it(*this);
				return (it += n);
			}


			IteratorVector	operator-(int n) const {
				IteratorVector it(*this);
				return (it -= n);
			}

			IteratorVector& operator+=(int n) const {
				_ptr += n;
				return (*this);
			}

			IteratorVector& operator-=(int n) const {
				_ptr -= n;
				return (*this);
			}

	};

}

#endif
