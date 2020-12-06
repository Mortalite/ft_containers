#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft {

	template<typename T> class DLLNode {
	public:
		T*			_data;
		DLLNode<T>*	_next;
		DLLNode<T>*	_prev;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag{};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template<typename T, typename Category = bidirectional_iterator_tag>
	class IteratorList {

		private:
			DLLNode<T>*	_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			IteratorList() {}
			IteratorList(const IteratorList& other) { _ptr = other._ptr; }
			IteratorList(DLLNode<T> *node) { _ptr = node; }
			~IteratorList() {}

			DLLNode<T>*	getPtr() { return (_ptr); }

			IteratorList&	operator=(const IteratorList& other) {
				_ptr = other._ptr;
				return (*this);
			}

			bool					operator==(const IteratorList& other) const {
				return (_ptr == other._ptr);
			}

			bool					operator!=(const IteratorList& other) const {
				return (_ptr != other._ptr);
			}

			reference				operator*() {
				return (*_ptr->_data);
			}

			pointer 				operator->() const {
				return (_ptr->_data);
			}

			IteratorList&	operator++() {
				if (_ptr && _ptr->_next)
					_ptr = _ptr->_next;
				return (*this);
			}

			IteratorList	operator++(int) {
				IteratorList<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}

			IteratorList&	operator--() {
				if (_ptr && _ptr->_prev)
					_ptr = _ptr->_prev;
				return (*this);
			}

			IteratorList	operator--(int) {
				IteratorList<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename T, typename Category = bidirectional_iterator_tag>
	class ReverseIteratorList {

		private:
			DLLNode<T>*	_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			ReverseIteratorList() {}
			ReverseIteratorList(const IteratorList<T>& other): IteratorList<T>(other) { }
			ReverseIteratorList(DLLNode<T> *node) { this->_ptr = node; }
			~ReverseIteratorList() {}

			DLLNode<T>*	getPtr() { return (_ptr); }

			ReverseIteratorList&	operator=(const ReverseIteratorList& other) {
				_ptr = other._ptr;
				return (*this);
			}

			bool					operator==(const ReverseIteratorList& other) const {
				return (_ptr == other._ptr);
			}

			bool					operator!=(const ReverseIteratorList& other) const {
				return (_ptr != other._ptr);
			}

			reference				operator*() {
				return (*_ptr->_data);
			}

			pointer 				operator->() const {
				return (_ptr->_data);
			}

			ReverseIteratorList& operator++() {
				if (_ptr && _ptr->_prev)
					_ptr = _ptr->_prev;
				return (*this);
			}

			ReverseIteratorList operator++(int) {
				ReverseIteratorList<T> tmp(*this);
				operator++();
				return (tmp);
			}

			ReverseIteratorList& operator--() {
				if (_ptr && _ptr->_next)
					_ptr = _ptr->_next;
				return (*this);
			}

			ReverseIteratorList operator--(int) {
				ReverseIteratorList<T> tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename T, typename Category = bidirectional_iterator_tag>
	class ConstIteratorList {

		private:
			DLLNode<T>*	_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			ConstIteratorList() {}
			ConstIteratorList(const IteratorList<T>& other): IteratorList<T>(other) { }
			ConstIteratorList(DLLNode<T> *node) { this->_ptr = node; }
			~ConstIteratorList() {}

			ConstIteratorList&	operator=(const ConstIteratorList& other) {
				_ptr = other._ptr;
				return (*this);
			}

			bool					operator==(const ConstIteratorList& other) const {
				return (_ptr == other._ptr);
			}

			bool					operator!=(const ConstIteratorList& other) const {
				return (_ptr != other._ptr);
			}

			const reference				operator*() {
				return (*_ptr->_data);
			}

			const pointer 			operator->() const {
				return (_ptr->_data);
			}

			ConstIteratorList&	operator++() {
				if (_ptr && _ptr->_next)
					_ptr = _ptr->_next;
				return (*this);
			}

			ConstIteratorList	operator++(int) {
				ConstIteratorList<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}

			ConstIteratorList&	operator--() {
				if (_ptr && _ptr->_prev)
					_ptr = _ptr->_prev;
				return (*this);
			}

			ConstIteratorList	operator--(int) {
				ConstIteratorList<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename T, typename Category = bidirectional_iterator_tag>
	class ConstReverseIteratorList {

		private:
			DLLNode<T>*	_ptr;

		public:

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;

			ConstReverseIteratorList() {}
			ConstReverseIteratorList(const ReverseIteratorList<T>& other): ReverseIteratorList<T>(other) { }
			ConstReverseIteratorList(DLLNode<T> *node) { this->_ptr = node; }
			~ConstReverseIteratorList() {}

			ConstReverseIteratorList&	operator=(const ConstReverseIteratorList& other) {
				_ptr = other._ptr;
				return (*this);
			}

			bool					operator==(const ConstReverseIteratorList& other) const {
				return (_ptr == other._ptr);
			}

			bool					operator!=(const ConstReverseIteratorList& other) const {
				return (_ptr != other._ptr);
			}

			const reference			operator*() {
				return (*_ptr->_data);
			}

			const pointer 			operator->() const {
				return (_ptr->_data);
			}

			ConstReverseIteratorList& operator++() {
				if (_ptr && _ptr->_prev)
					_ptr = _ptr->_prev;
				return (*this);
			}

			ConstReverseIteratorList operator++(int) {
				ConstReverseIteratorList<T> tmp(*this);
				operator++();
				return (tmp);
			}

			ConstReverseIteratorList& operator--() {
				if (_ptr && _ptr->_next)
					_ptr = _ptr->_next;
				return (*this);
			}

			ConstReverseIteratorList operator--(int) {
				ConstReverseIteratorList<T> tmp(*this);
				operator--();
				return (tmp);
			}

	};

}

#endif
