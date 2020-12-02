#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <limits>
# include "iterator.h"

namespace ft {

	template<typename T, typename Alloc = std::allocator<T> >
	class list {

		public:
			typedef T								value_type;
			typedef Alloc							allocator_type;
			typedef T&								reference;
			typedef const T&						const_reference;
			typedef T*								pointer;
			typedef const T* 						const_pointer;
			typedef std::ptrdiff_t					difference_type;
			typedef size_t							size_type;
			typedef ft::BidirectionalIterator<T>	iterator;

			explicit list(const allocator_type& alloc = allocator_type());
			list(const list& x);
			~list();


			void			push_front(const value_type& val);
			void 			push_back(const value_type& val);

			bool			empty() const;
			size_type		size() const;
			size_type		max_size() const;

			reference		front();
			const_reference	front() const;
			reference		back();
			const_reference back() const;

			void			print();

			iterator		begin();
			iterator		end();

		private:
			DLLNode<T>*		_first;
			DLLNode<T>*		_last;
			DLLNode<T>*		_end;
			size_t			_size;
			allocator_type	_alloc;
	};

	template<typename T, typename Alloc>
	list<T, Alloc>::list(const allocator_type& alloc) {
		_first = NULL;
		_last = NULL;
		_end = new DLLNode<T>;
		_end->_next = _end->_prev = NULL;
		_end->_data = NULL;
		_size = 0;
		_alloc = alloc;
	}

	template<typename T, typename Alloc>
	list<T, Alloc>::list(const list& x) {
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
	}

	template<typename T, typename Alloc>
	list<T, Alloc>::~list() {
		DLLNode<T> *ptr;
		while (_first != _end) {
			ptr = _first->_next;
			_alloc.deallocate(_first->_data, 1);
			delete _first;
			_first = ptr;
		}
		delete _end;
	}

	template<typename T, typename Alloc>
	void list<T, Alloc>::push_front(const value_type &val) {
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

	template<typename T, typename Alloc>
	void list<T, Alloc>::push_back(const value_type &val) {
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
			_last->_next = ptr;
			ptr->_prev = _last;
			ptr->_next = _end;
			_last = ptr;
		}
		_size++;
	}

	template<typename T, typename Alloc>
	void list<T, Alloc>::print() {
		DLLNode<T> *ptr = _first;

		while (ptr != _end) {
			std::cout << *ptr->_data << std::endl;
			ptr = ptr->_next;
		}

	}

	template<typename T, typename Alloc>
	bool list<T, Alloc>::empty() const {
		return (!_size);
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::size_type list<T, Alloc>::size() const {
		return (_size);
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::size_type list<T, Alloc>::max_size() const {
		return (std::numeric_limits<size_type>::max());
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::reference list<T, Alloc>::front() {
		return (*_first->_data);
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::const_reference list<T, Alloc>::front() const {
		return (*_first->_data);
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::reference list<T, Alloc>::back() {
		return (*_last->_data);
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::const_reference list<T, Alloc>::back() const {
		return (*_last->_data);
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::begin() {
		return (iterator(_end->_next));
	}

	template<typename T, typename Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::end() {
		return (iterator(_end));
	}

}

#endif
