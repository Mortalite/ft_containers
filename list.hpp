#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <limits>

namespace ft {

	template<typename T> class _Node {
		public:
			T*			_data;
			_Node<T>*	_next;
			_Node<T>*	_prev;
	};

	template<typename T, typename Alloc = std::allocator<T> >
	class list {

		public:
			typedef T				value_type;
			typedef Alloc			allocator_type;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef T*				pointer;
			typedef const T* 		const_pointer;
			typedef std::ptrdiff_t	difference_type;
			typedef size_t			size_type;

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

		private:
			_Node<T>*		_first;
			_Node<T>*		_last;
			_Node<T>*		_end;
			size_t			_size;
			allocator_type	_alloc;
	};

	template<typename T, typename Alloc>
	list<T, Alloc>::list(const allocator_type& alloc) {
		_first = NULL;
		_last = NULL;
		_end = new _Node<T>;
		_end->_next = _end->_prev = NULL;
		_end->_data = NULL;
		_size = 0;
		_alloc = alloc;
	}

	template<typename T, typename Alloc>
	list<T, Alloc>::list(const list& x) {
		_first = NULL;
		_last = NULL;
		_end = new _Node<T>;
		_end->_next = _end->_prev = NULL;
		_end->_data = NULL;
		_size = 0;
		_alloc = x._alloc;

		if (x._size) {
			_Node<T> *ptr = x._first;
			while (ptr != x._end) {
				push_back(*ptr->_data);
				ptr = ptr->_next;
			}
		}
	}

	template<typename T, typename Alloc>
	list<T, Alloc>::~list() {
		_Node<T> *ptr;
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
		_Node<T> *ptr = new _Node<T>;

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
		_Node<T> *ptr = new _Node<T>;

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
		_Node<T> *ptr = _first;

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

}

#endif
