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
			IteratorVector(const IteratorVector& other):_ptr(other._ptr) {}
			IteratorVector(pointer ptr):_ptr(ptr) {}
			~IteratorVector() {}

			pointer			getPtr() const { return (_ptr); }
			pointer 		operator->() const {	return (_ptr);		}
			reference		operator*() {	return (*_ptr);		}
			reference		operator[](int n) const {	return (*(_ptr + n));	}
			difference_type operator-(const IteratorVector& other) const {		return (_ptr - other._ptr);		}
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

			IteratorVector& operator+=(int n) {
				_ptr += n;
				return (*this);
			}

			IteratorVector& operator-=(int n) {
				_ptr -= n;
				return (*this);
			}

	};

	template<typename T, typename Category = std::random_access_iterator_tag>
	class ReverseIteratorVector {

		private:
			T	*_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			ReverseIteratorVector() {}
			ReverseIteratorVector(const ReverseIteratorVector& other):_ptr(other._ptr) {}
			ReverseIteratorVector(pointer ptr):_ptr(ptr) {}
			~ReverseIteratorVector() {}

			pointer			getPtr() const { return (_ptr); }
			pointer 		operator->() const {	return (_ptr);		}
			reference		operator*() const {	return (*(_ptr - 1));	}
			reference		operator[](int n) const {	return (*(_ptr + n - 1));	}
			difference_type operator-(const ReverseIteratorVector& other) const {		return (_ptr - other._ptr);		}
			bool 			operator==(const ReverseIteratorVector& other) const {		return (_ptr == other._ptr);		}
			bool 			operator!=(const ReverseIteratorVector& other) const {		return (_ptr != other._ptr);		}
			bool 			operator<(const ReverseIteratorVector& other) const {		return (_ptr < other._ptr);			}
			bool 			operator>(const ReverseIteratorVector& other) const {		return (_ptr > other._ptr);			}
			bool 			operator<=(const ReverseIteratorVector& other) const {		return (_ptr <= other._ptr);		}
			bool 			operator>=(const ReverseIteratorVector& other) const {		return (_ptr >= other._ptr);		}

			ReverseIteratorVector& operator=(const ReverseIteratorVector& other) {
				_ptr = other._ptr;
				return (*this);
			}

			ReverseIteratorVector&	operator++() {
				--_ptr;
				return (*this);
			}

			ReverseIteratorVector	operator++(int) {
				ReverseIteratorVector<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}

			ReverseIteratorVector&	operator--() {
				++_ptr;
				return (*this);
			}

			ReverseIteratorVector	operator--(int) {
				ReverseIteratorVector<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

			ReverseIteratorVector	operator+(int n) const {
				ReverseIteratorVector it(*this);
				return (it -= n);
			}


			ReverseIteratorVector	operator-(int n) const {
				ReverseIteratorVector it(*this);
				return (it += n);
			}

			ReverseIteratorVector& operator+=(int n) {
				_ptr -= n;
				return (*this);
			}

			ReverseIteratorVector& operator-=(int n) {
				_ptr += n;
				return (*this);
			}

	};

	template<typename T, typename Category = std::random_access_iterator_tag>
	class ConstIteratorVector {

		private:
			T	*_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			ConstIteratorVector() {}
			ConstIteratorVector(const ConstIteratorVector& other):_ptr(other._ptr) {}
			ConstIteratorVector(pointer ptr):_ptr(ptr) {}
			~ConstIteratorVector() {}

			pointer				getPtr() const { return (_ptr); }
			const value_type*	operator->() const {	return (_ptr);		}
			const value_type&	operator*() const {	return (*_ptr);	}
			reference 			operator[](int n) const {	return (*(_ptr + n));	}
			difference_type 	operator-(const ConstIteratorVector& other) const {		return (_ptr - other._ptr);		}
			bool 				operator==(const ConstIteratorVector& other) const {		return (_ptr == other._ptr);		}
			bool 				operator!=(const ConstIteratorVector& other) const {		return (_ptr != other._ptr);		}
			bool 				operator<(const ConstIteratorVector& other) const {		return (_ptr < other._ptr);			}
			bool 				operator>(const ConstIteratorVector& other) const {		return (_ptr > other._ptr);			}
			bool 				operator<=(const ConstIteratorVector& other) const {		return (_ptr <= other._ptr);		}
			bool 				operator>=(const ConstIteratorVector& other) const {		return (_ptr >= other._ptr);		}

			ConstIteratorVector& operator=(const ConstIteratorVector& other) {
				_ptr = other._ptr;
				return (*this);
			}

			ConstIteratorVector&	operator++() {
				++_ptr;
				return (*this);
			}

			ConstIteratorVector	operator++(int) {
				IteratorVector<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}

			ConstIteratorVector&	operator--() {
				--_ptr;
				return (*this);
			}

			ConstIteratorVector	operator--(int) {
				ConstIteratorVector<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

			ConstIteratorVector	operator+(int n) const {
				ConstIteratorVector it(*this);
				return (it += n);
			}

			ConstIteratorVector	operator-(int n) const {
				ConstIteratorVector it(*this);
				return (it -= n);
			}

			ConstIteratorVector& operator+=(int n) {
				_ptr += n;
				return (*this);
			}

			ConstIteratorVector& operator-=(int n) {
				_ptr -= n;
				return (*this);
			}

	};


	template<typename T, typename Category = std::random_access_iterator_tag>
	class ConstReverseIteratorVector {

		private:
			T	*_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			ConstReverseIteratorVector() {}
			ConstReverseIteratorVector(const ConstReverseIteratorVector& other):_ptr(other._ptr) {}
			ConstReverseIteratorVector(pointer ptr):_ptr(ptr) {}
			~ConstReverseIteratorVector() {}

			pointer				getPtr() const { return (_ptr); }
			const value_type*	operator->() const {	return (_ptr);		}
			const value_type&	operator*() const {	return (*(_ptr - 1));	}
			reference 			operator[](int n) const {	return (*(_ptr + n - 1));	}
			difference_type 	operator-(const ConstReverseIteratorVector& other) const {		return (_ptr - other._ptr);		}
			bool 				operator==(const ConstReverseIteratorVector& other) const {		return (_ptr == other._ptr);		}
			bool 				operator!=(const ConstReverseIteratorVector& other) const {		return (_ptr != other._ptr);		}
			bool 				operator<(const ConstReverseIteratorVector& other) const {		return (_ptr < other._ptr);			}
			bool 				operator>(const ConstReverseIteratorVector& other) const {		return (_ptr > other._ptr);			}
			bool 				operator<=(const ConstReverseIteratorVector& other) const {		return (_ptr <= other._ptr);		}
			bool 				operator>=(const ConstReverseIteratorVector& other) const {		return (_ptr >= other._ptr);		}

			ConstReverseIteratorVector& operator=(const ConstReverseIteratorVector& other) {
				_ptr = other._ptr;
				return (*this);
			}

			ConstReverseIteratorVector&	operator++() {
				++_ptr;
				return (*this);
			}

			ConstReverseIteratorVector	operator++(int) {
				IteratorVector<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}

			ConstReverseIteratorVector&	operator--() {
				--_ptr;
				return (*this);
			}

			ConstReverseIteratorVector	operator--(int) {
				ConstReverseIteratorVector<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

			ConstReverseIteratorVector	operator+(int n) const {
				ConstReverseIteratorVector it(*this);
				return (it += n);
			}

			ConstReverseIteratorVector	operator-(int n) const {
				ConstReverseIteratorVector it(*this);
				return (it -= n);
			}

			ConstReverseIteratorVector&	operator+=(int n) {
				_ptr += n;
				return (*this);
			}

			ConstReverseIteratorVector&	operator-=(int n) {
				_ptr -= n;
				return (*this);
			}

	};

}

#endif
