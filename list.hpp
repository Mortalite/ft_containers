#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <limits>
# include "iterator.hpp"
# include "utils.hpp"

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

			void 	erase_swap(list& x, iterator i) {
				DLLNode<T> *ptr = i.getPtr();

				ptr->_prev->_next = ptr->_next;
				ptr->_next->_prev = ptr->_prev;
				if (ptr == x._first) {
					x._end->_next = x._first->_next;
					x._first = x._first->_next;
					x._first->_prev = x._end;
				}
				else if (ptr == x._last) {
					x._last = x._last->_prev;
					x._last->_next = x._end;
				}
				x._size--;
			}

			void 	insert_swap(iterator position, iterator i) {
				DLLNode<T> *pos = position.getPtr(), *ptr = i.getPtr();

				ptr->_prev = pos->_prev;
				ptr->_next = pos;
				pos->_prev->_next = ptr;
				pos->_prev = ptr;
				if (pos == _first || _first == NULL)
					_end->_next = _first = ptr;
				if (pos == _end || _last == NULL)
					_end->_prev = _last = ptr;
				_size++;
			}

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
				ft::swap(_size, x._size);
				ft::swap(_first, x._first);
				ft::swap(_last, x._last);
				ft::swap(_end, x._end);
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
				iterator first(x.begin()), end(x.end());
				while (first != end)
					splice(position, x, first++);
			}

			void 					splice(iterator position, list& x, iterator i) {
				erase_swap(x, i);
				insert_swap(position, i);
			}

			void 					splice(iterator position, list& x, iterator first, iterator last) {
				while (first != last)
					splice(position, x, first++);
			}

			void 					remove(const value_type& val) {
				iterator first(begin()), del;
				while (first != end()) {
					del = first++;
					if (*del == val)
						erase(del);
				}
			}

			template<class Predicate>
			void					remove_if(Predicate pred) {
				iterator first(begin()), del;
				while (first != end()) {
					del = first++;
					if (pred(*del))
						erase(del);
				}
			}

			void 					unique() {
				iterator first(begin()), del;
				while (first != end()) {
					del = first;
					if (++del != end() && *first == *del)
						erase(del);
					else
						first++;
				}
			}

			template<class BinaryPredicate>
			void					unique(BinaryPredicate binary_pred) {
				iterator first(begin()), del;
				while (first != end()) {
					del = first;
					if (++del != end() && binary_pred(*first, *del))
						erase(del);
					else
						first++;
				}
			}

			void					merge(list& x) {
				if (this != &x && x.size()) {
					iterator first = begin(), end = this->end(), xFirst(x.begin()), xEnd(x.end()), tmp;
					while (first != end && xFirst != xEnd) {
						if (*first > *xFirst) {
							tmp = xFirst++;
							splice(first, x, tmp);
						}
						else
							first++;
					}
					splice(end, x, x.begin(), x.end());
				}
			}

			template<class Compare>
			void					merge(list& x, Compare comp) {
				if (this != &x && x.size()) {
					iterator first(begin()), end(this->end()), xFirst(x.begin()), xEnd(x.end());
					while (first != end) {
						if (xFirst != xEnd && comp(*xFirst, *first)) {
							insert(first, *xFirst);
							xFirst = x.erase(xFirst);
						}
						else
							first++;
					}
					insert(this->end(), x.begin(), x.end());
					x.erase(x.begin(), x.end());
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
