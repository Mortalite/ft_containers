#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <limits>
# include "iterator.h"

namespace ft {

	template<typename T, typename Alloc = std::allocator<T> >
	class list {

		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef T&											reference;
			typedef const T&									const_reference;
			typedef T*											pointer;
			typedef const T* 									const_pointer;
			typedef std::ptrdiff_t								difference_type;
			typedef size_t										size_type;
			typedef ft::BidirectionalIterator<T>				iterator;
			typedef ft::ReverseBidirectionalIterator<T>			reverse_iterator;
			typedef ft::ConstBidirectionalIterator<T>			const_iterator;
			typedef ft::ConstReverseBidirectionalIterator<T>	const_reverse_iterator;

		private:
			DLLNode<T>*		_first;
			DLLNode<T>*		_last;
			DLLNode<T>*		_end;
			size_t			_size;
			allocator_type	_alloc;

		public:

			explicit list(const allocator_type& alloc = allocator_type()) {
				_first = NULL;
				_last = NULL;
				_end = new DLLNode<T>;
				_end->_next = _end;
				_end->_prev = _end;
				_end->_data = NULL;
				_size = 0;
				_alloc = alloc;
			}
			list(const list& x) {
				_first = NULL;
				_last = NULL;
				_end = new DLLNode<T>;
				_end->_next = _end;
				_end->_prev = _end;
				_end->_data = NULL;
				_size = 0;
				_alloc = x._alloc;

				if (x._size) {
					DLLNode<T> *ptr = x._first;
					while (ptr != x._end) {
						push_back(*ptr->_data);
						ptr = ptr->_next;
					}
				}
			}
			~list() {
				DLLNode<T> *ptr;
				while (_first && _first != _end) {
					ptr = _first->_next;
					_alloc.deallocate(_first->_data, 1);
					delete _first;
					_first = ptr;
				}
				delete _end;
			}


			void					push_front(const value_type& val) {
				DLLNode<T> *ptr = new DLLNode<T>;

				ptr->_prev = ptr->_next = NULL;
				ptr->_data = _alloc.allocate(1);
				_alloc.construct(ptr->_data, val);
				if (!_size) {
					ptr->_next = _end;
					_end->_prev = ptr;
					_end->_next = _first;
					_last = _first = ptr;
				}
				else {
					_first->_prev = ptr;
					ptr->_next = _first;
					_end->_next = _first = ptr;
				}
				_size++;
			}

			void 					pop_front() {
				if (!empty())
					erase(begin());
			}

			void					push_back(const value_type& val) {
				DLLNode<T> *ptr = new DLLNode<T>;

				ptr->_prev = NULL;
				ptr->_next = NULL;
				ptr->_data = _alloc.allocate(1);
				_alloc.construct(ptr->_data, val);
				if (!_size) {
					ptr->_next = _end;
					_last = ptr;
					_first = ptr;
					_first->_prev = _end;
					_end->_prev = ptr;
					_end->_next = ptr;
				}
				else {
					_last->_next = ptr;
					ptr->_prev = _last;
					ptr->_next = _end;
					_end->_prev = ptr;
					_last = ptr;
				}
				_size++;
			}

			void					pop_back() {
				if (!empty())
					erase(iterator(_last));
			}

			iterator				erase(iterator position) {
				DLLNode<T> *ptr = position.getPtr();
				DLLNode<T> *tmp = ptr->_next;
				ptr->_prev->_next = ptr->_next;
				if (ptr == _first) {
					_end->_next = _first->_next;
					_first = _first->_next;
				}
				else if (ptr == _last)
					_last = _last->_prev;
				_alloc.deallocate(ptr->_data, 1);
				delete ptr;
				_size--;
				return (iterator(tmp));
			}

			iterator 				erase(iterator first, iterator last) {
				while (first != last)
					erase(first++);
				return (iterator(_first));
			}

			bool					empty() const {
				return (!_size);
			}
			size_type				size() const {
				return (_size);
			}
			size_type				max_size() const {
				return (std::numeric_limits<size_type>::max());
			}

			reference				front() {
				return (*_first->_data);
			}
			const_reference			front() const {
				return (*_first->_data);
			}
			reference				back() {
				return (*_last->_data);
			}
			const_reference			back() const {
				return (*_last->_data);
			}

			iterator				begin() {
				return (iterator(_end->_next));
			}

			const_iterator			begin() const {
				return (const_iterator(_end->_next));
			}

			iterator				end() {
				return (iterator(_end));
			}

			const_iterator			end() const {
				return (const_iterator(_end));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(_end->_prev));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(_end->_prev));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(_end));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(_end));
			}

			list& operator=(const list& x) {
				DLLNode<T> *ptr;
				while (_first && _first != _end) {
					ptr = _first->_next;
					_alloc.deallocate(_first->_data, 1);
					delete _first;
					_first = ptr;
				}
				delete _end;

				_first = NULL;
				_last = NULL;
				_end = new DLLNode<T>;
				_end->_next = _end->_prev = NULL;
				_end->_data = NULL;
				_size = 0;
				_alloc = x._alloc;

				if (x._size) {
					DLLNode<T> *ptr = x._first;
					while (ptr != x._end) {
						push_back(*ptr->_data);
						ptr = ptr->_next;
					}
				}
				return (*this);
			}

	};

}

#endif
