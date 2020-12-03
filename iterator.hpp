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
	class BidirectionalIterator {

		protected:
			DLLNode<T>*	_ptr;

		public:
			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;


			BidirectionalIterator() {}
			BidirectionalIterator(const BidirectionalIterator& other) { _ptr = other._ptr; }
			BidirectionalIterator(DLLNode<T> *node) { _ptr = node; }
			virtual ~BidirectionalIterator() {}

			DLLNode<T>*	getPtr() { return (_ptr); }

			BidirectionalIterator&	operator=(const BidirectionalIterator& other) {
				_ptr = other._ptr;
				return (*this);
			}
			bool					operator==(const BidirectionalIterator& other) const {
				return (_ptr == other._ptr);
			}
			bool					operator!=(const BidirectionalIterator& other) const {
				return (_ptr != other._ptr);
			}
			reference				operator*() {
				return (*_ptr->_data);
			}
			pointer 				operator->() const {
				return (_ptr->_data);
			}

			BidirectionalIterator&	operator++() {
				if (_ptr && _ptr->_next)
					_ptr = _ptr->_next;
				return (*this);
			}
			BidirectionalIterator	operator++(int) {
				BidirectionalIterator<T, Category> tmp(*this);
				operator++();
				return (tmp);
			}
			BidirectionalIterator&	operator--() {
				if (_ptr && _ptr->_prev)
					_ptr = _ptr->_prev;
				return (*this);
			}
			BidirectionalIterator	operator--(int) {
				BidirectionalIterator<T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename T>
	class ReverseBidirectionalIterator: public BidirectionalIterator<T> {

		public:
			ReverseBidirectionalIterator() {}
			ReverseBidirectionalIterator(const BidirectionalIterator<T>& other):BidirectionalIterator<T>(other) { }
			ReverseBidirectionalIterator(DLLNode<T> *node) { this->_ptr = node; }
			virtual ~ReverseBidirectionalIterator() {}

			ReverseBidirectionalIterator& operator++() {
				BidirectionalIterator<T>::operator--();
				return (*this);
			}

			ReverseBidirectionalIterator operator++(int) {
				ReverseBidirectionalIterator<T> tmp(*this);
				operator++();
				return (tmp);
			}

			ReverseBidirectionalIterator& operator--() {
				BidirectionalIterator<T>::operator++();
				return (*this);
			}

			ReverseBidirectionalIterator operator--(int) {
				ReverseBidirectionalIterator<T> tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename T>
	class ConstBidirectionalIterator: public BidirectionalIterator<T> {

		public:
			ConstBidirectionalIterator() {}
			ConstBidirectionalIterator(const BidirectionalIterator<T>& other):BidirectionalIterator<T>(other) { }
			ConstBidirectionalIterator(DLLNode<T> *node) { this->_ptr = node; }
			virtual ~ConstBidirectionalIterator() {}

			ConstBidirectionalIterator&	operator=(const ConstBidirectionalIterator &other) {
				this->_ptr = other._ptr;
				return (*this);
			}
			const T&					operator*() const {
				return (*this->_ptr->data);
			}

	};

	template<typename T>
	class ConstReverseBidirectionalIterator: public ReverseBidirectionalIterator<T> {

		public:
			ConstReverseBidirectionalIterator() {}
			ConstReverseBidirectionalIterator(const ReverseBidirectionalIterator<T>& other): ReverseBidirectionalIterator<T>(other) { }
			ConstReverseBidirectionalIterator(DLLNode<T> *node) { this->_ptr = node; }
			virtual ~ConstReverseBidirectionalIterator() {}

			ConstReverseBidirectionalIterator&	operator=(const ConstReverseBidirectionalIterator &other) {
				this->_ptr = other._ptr;
				return (*this);
			}

			const T&							operator*() const {
				return (*this->_ptr->data);
			}

	};

}

#endif
