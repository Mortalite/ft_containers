#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <limits>
# include "iterator.hpp"

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
				_end = new DLLNode<T>;
				_first = _last = _end->_next = _end->_prev = _end;
				_end->_data = NULL;
				_size = 0;
				_alloc = alloc;
			}

			explicit list(	size_type n, const value_type& val = value_type(),\
							const allocator_type& alloc = allocator_type()) {
				_end = new DLLNode<T>;
				_first = _last = _end->_next = _end->_prev = _end;
				_end->_data = NULL;
				_size = 0;
				_alloc = alloc;
				assign(n, val);
		 	}

		 	template<class InputIterator>
		 	list (	InputIterator first, InputIterator last, \
		 			const allocator_type& alloc = allocator_type()) {
				_end = new DLLNode<T>;
				_first = _last = _end->_next = _end->_prev = _end;
				_end->_data = NULL;
				_size = 0;
		   		_alloc = alloc;
		   		assign(first, last);
			}

			list(const list& x) {
				_end = new DLLNode<T>;
				_first = _last = _end->_next = _end->_prev = _end;
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
				clear();
				delete _end;
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

			template <class InputIterator>
			void					assign(InputIterator first, InputIterator last) {
				clear();
				while (first != last)
					push_back(*first++);
			}

			void					assign(size_type n, const value_type& val) {
				clear();
				while (n--)
					push_back(val);
			}

			void					push_front(const value_type& val) {
				DLLNode<T> *ptr = new DLLNode<T>;

				ptr->_prev = ptr->_next = NULL;
				ptr->_data = _alloc.allocate(1);
				_alloc.construct(ptr->_data, val);
				if (!_size) {
					_end->_prev = _end->_next = _last = _first = ptr;
					ptr->_next = ptr->_prev = _end;
				}
				else {
					_first->_prev = ptr;
					ptr->_prev = _end;
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
					ptr->_next = ptr->_prev = _end;
					_first = _last = _end->_prev = _end->_next = ptr;
				}
				else {
					_last->_next = ptr;
					ptr->_prev = _last;
					ptr->_next = _end;
					_end->_prev = _last = ptr;
				}
				_size++;
			}

			void					pop_back() {
				if (!empty())
					erase(iterator(_last));
			}

			iterator 				insert(iterator position, const value_type& val) {
				DLLNode<T> *pos = position.getPtr();
				DLLNode<T> *ptr = new DLLNode<T>;

				ptr->_prev = pos->_prev;
				ptr->_next = pos;
				ptr->_data = _alloc.allocate(1);
				_alloc.construct(ptr->_data, val);
				pos->_prev->_next = ptr;
				pos->_prev = ptr;
				if (pos == _first || _first == NULL)
					_end->_next = _first = ptr;
				if (pos == _end || _last == NULL)
					_end->_prev = _last = ptr;
				_size++;
				return (iterator(ptr));
			}

			void 					insert(iterator position, size_type n, const value_type& val) {
				while (n--)
					insert(position, val);
			}

			template<class InputIterator>
			void 					insert(iterator position, InputIterator first, InputIterator last) {
				while (first != last)
					insert(position, *first++);
			}

			iterator				erase(iterator position) {
				DLLNode<T> *ptr = position.getPtr();
				DLLNode<T> *tmp = ptr->_next;
				ptr->_prev->_next = ptr->_next;
				ptr->_next->_prev = ptr->_prev;
				if (ptr == _first) {
					_end->_next = _first->_next;
					_first = _first->_next;
					_first->_prev = _end;
				}
				else if (ptr == _last) {
					_last = _last->_prev;
					_last->_next = _end;
				}
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

			void 					swap(list& x) {
				DLLNode<T> *ptr;
				size_type size;

				size = x._size;
				x._size = _size;
				_size = size;
				ptr = x._first;
				x._first = _first;
				_first = ptr;
				ptr = x._last;
				x._last = _last;
				_last = ptr;
				ptr = x._end;
				x._end = _end;
				_end = ptr;
			}

			void 					resize(size_type n, value_type val = value_type()) {
				while (_size < n)
					push_back(val);
				while (_size > n)
					pop_back();
			}

			void 					clear() {
				while (!empty())
					pop_back();
			}

			void 					splice(iterator position, list& x) {
				insert(position, x.begin(), x.end());
				x.clear();
			}

			void 					splice(iterator position, list& x, iterator i) {
				insert(position, *i);
				x.erase(i);
			}

			void 					splice(iterator position, list& x, iterator first, iterator last) {
				insert(position, first, last);
				x.erase(first, last);
			}

			void 					remove(const value_type& val) {
				iterator first(begin()), del(begin());
				while (first != end()) {
					del = first++;
					if (*del == val)
						erase(del);
				}
			}

			template<class Predicate>
			void					remove_if(Predicate pred) {
				iterator first(begin()), del(begin());
				while (first != end()) {
					del = first++;
					if (pred(*del))
						erase(del);
				}
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
				clear();

				_end = new DLLNode<T>;
				_first = _last = _end->_next = _end->_prev = _end;
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
