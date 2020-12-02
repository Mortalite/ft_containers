#ifndef ITERATOR_H
#define ITERATOR_H

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
			DLLNode<T>	*_ptr;

		public:
			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category		iterator_category;


			BidirectionalIterator() {}
			BidirectionalIterator(const BidirectionalIterator& copySource) { _ptr = copySource._ptr; }
			BidirectionalIterator(DLLNode<T> *node) { _ptr = node; }
			virtual ~BidirectionalIterator() {}

			BidirectionalIterator&	operator=(const BidirectionalIterator& copySource) {
				if (this != copySource)
					_ptr = copySource._ptr;
				return (*this);
			}
			bool					operator==(const BidirectionalIterator& b) const {
				return (_ptr == b._ptr);
			}
			bool					operator!=(const BidirectionalIterator& b) const {
				return (_ptr != b._ptr);
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
			ReverseBidirectionalIterator(const ReverseBidirectionalIterator& copySource) { this->_ptr = copySource._ptr; }
			ReverseBidirectionalIterator(DLLNode<T> *node) { this->_ptr = node; }
			~ReverseBidirectionalIterator() {}

			ReverseBidirectionalIterator& operator++() {
				BidirectionalIterator<T>::operator--();
				return (*this);
			}

			ReverseBidirectionalIterator operator++(int) {
				ReverseBidirectionalIterator<T> tmp(*this);
				operator--();
				return (tmp);
			}

			ReverseBidirectionalIterator& operator--() {
				BidirectionalIterator<T>::operator++();
				return (*this);
			}

			ReverseBidirectionalIterator operator--(int) {
				ReverseBidirectionalIterator<T> tmp(*this);
				operator++();
				return (tmp);
			}

	};

}

#endif
