#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <limits>
# include "iteratorList.hpp"
# include "utils.hpp"

namespace ft {

	template<typename T, typename Alloc = std::allocator<T> >
	class list {

		/*
		** Typedefs
		*/
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::IteratorList<T>							iterator;
			typedef ft::ReverseIteratorList<T>					reverse_iterator;
			typedef ft::ConstIteratorList<T>					const_iterator;
			typedef ft::ConstReverseIteratorList<T>				const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

		/*
		** Class members and private functions
		*/
		private:
			DLLNode<T>*		_first;
			DLLNode<T>*		_last;
			DLLNode<T>*		_end;
			size_type		_size;
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

			/*
			** Constructors, destructor and assignment operator
			*/
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
				while (n--)
					push_back(val);
		 	}

		 	template<class InputIterator>
		 	list(	InputIterator first, InputIterator last, \
		 			const allocator_type& alloc = allocator_type()) {
				_end = new DLLNode<T>;
				_first = _last = _end->_next = _end->_prev = _end;
				_end->_data = NULL;
				_size = 0;
		   		_alloc = alloc;
				while (first != last)
					push_back(*first++);
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

			list& operator=(const list& x) {
				if (this != &x) {
					clear();
					delete _end;

					_end = new DLLNode<T>;
					_first = _last = _end->_next = _end->_prev = _end;
					_end->_data = NULL;
					_size = 0;
					_alloc = x._alloc;

					if (x._size) {
						const_iterator first = x.begin(), last = x.end();
						while (first != last)
							push_back(*first++);
					}
				}
				return (*this);
			}

			/*
			** Iterators
			*/
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

			/*
			** Capacity
			*/
			bool					empty() const {
				return (!_size);
			}

			size_type				size() const {
				return (_size);
			}

			size_type				max_size() const {
				return (_alloc.max_size());
			}

			/*
			** Element access
			*/
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

			/*
			** Modifiers
			*/
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
				if (ptr == _last) {
					_last = _last->_prev;
					_last->_next = _end;
				}
				_alloc.destroy(ptr->_data);
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

			/*
			** Operations
			*/
			void 					splice(iterator position, list& x) {
				iterator first = x.begin(), end = x.end();
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
				iterator first = this->begin(), del;
				while (first != end()) {
					del = first++;
					if (*del == val)
						erase(del);
				}
			}

			template<class Predicate>
			void					remove_if(Predicate pred) {
				iterator first = this->begin(), del;
				while (first != end()) {
					del = first++;
					if (pred(*del))
						erase(del);
				}
			}

			void 					unique() {
				iterator first = this->begin(), del;
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
				iterator first = this->begin(), del;
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
					iterator first = this->begin(), end = this->end();
					iterator xFirst = x.begin(), xEnd = x.end();
					while (first != end && xFirst != xEnd) {
						if (*first > *xFirst)
							splice(first, x, xFirst++);
						else
							first++;
					}
					splice(end, x, x.begin(), x.end());
				}
			}

			template<class Compare>
			void					merge(list& x, Compare comp) {
				if (this != &x && x.size()) {
					iterator first = this->begin(), end = this->end();
					iterator xFirst = x.begin(), xEnd = x.end();
					while (first != end && xFirst != xEnd) {
						if (comp(*xFirst, *first))
							splice(first, x, xFirst++);
						else
							first++;
					}
					splice(end, x, x.begin(), x.end());
				}
			}

			void 					sort() {
				iterator first = this->begin(), end = this->end(), tmp;
				while (first != end) {
					tmp = first;
					while (++tmp != end)
						if (*first > *tmp)
							ft::swap(*first, *tmp);
					first++;
				}
			}

			template<class Compare>
			void 					sort(Compare comp) {
				iterator first = this->begin(), end = this->end(), tmp;
				while (first != end) {
					tmp = first;
					while (++tmp != end)
						if (comp(*tmp, *first))
							ft::swap(*first, *tmp);
					first++;
				}
			}

			void					reverse() {
				iterator first = this->begin(), end = this->end();
				for (size_type i = 0; i < _size / 2; i++)
					ft::swap(*first++, *--end);
			}

	};

	/*
	** Non-member function overloads
	*/
	template <class T, class Alloc>
	bool operator==	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		typename list<T, Alloc>::const_iterator firstLhs = lhs.begin(), firstRhs = rhs.begin();
		for (typename list<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (*firstLhs++ != *firstRhs++)
				return (false);
		return (true);
	}

	template <class T, class Alloc>
	bool operator!=	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<	(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		typename list<T,Alloc>::size_type cmpSize = (lhs.size() > rhs.size() ? rhs.size() : lhs.size());
		typename list<T,Alloc>::const_iterator firstLhs = lhs.begin(), firstRhs = rhs.begin();
		for (typename list<T,Alloc>::size_type i = 0; i < cmpSize; i++)
			if (*firstLhs++ >= *firstRhs++)
				return (false);
		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(rhs > lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
		x.swap(y);
	}

}

#endif
