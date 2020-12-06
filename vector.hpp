#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iteratorVector.hpp"

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class vector {

		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::IteratorVector<T>						iterator;
//			typedef ft::ReverseIteratorVector<T>				reverse_iterator;
//			typedef ft::ConstIteratorVector<T>					const_iterator;
//			typedef ft::ConstReverseIteratorVector<T>			const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

		private:
			T						*_array;
			size_type				_size;
			size_type				_capacity;
			const static size_type	_scaleFactor = 2;
			allocator_type			_alloc;

		public:

			/*
			** Constructors and destructor
			*/
			explicit vector (const allocator_type& alloc = allocator_type()) {
				_array = NULL;
				_capacity = 0;
				_size = 0;
				_alloc = alloc;
			}

			explicit vector (size_type n, const value_type& val = value_type(),
						 	const allocator_type& alloc = allocator_type()) {
				_array = NULL;
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				resize(n, val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type()) {
				size_type size = ft::distance(first, last);
				_alloc = alloc;
				_size = size;
				_capacity = size;
				if (size > 0) {
					_array = _alloc.allocate(_size);
					for (size_type i = 0; i < size; i++)
						_alloc.construct(_array + i, *first++);
				}
				else
					_array = NULL;
			}

			vector (const vector& x) {
				_alloc = x._alloc;
				_size = x._size;
				_capacity = x._capacity;
				if (x._size > 0 && x._capacity > 0) {
					_array = _alloc.allocate(_capacity);
					for (size_type i = 0; i < x._size; i++)
						_alloc.construct(_array + i, x._array[i]);
				}
				else
					_array = NULL;
			}

			~vector() {
				clear();
				if (_capacity > 0)
					_alloc.deallocate(_array, _capacity);
			}

			/*
			** Iterators
			*/

			iterator begin() {
				return (iterator(_array));
			}

			iterator end() {
				return (iterator(_array + _size));
			}

			/*
			** Capacity
			*/
			size_type 	size() const {
				return (_size);
			}

			size_type	max_size() const {
				return (std::numeric_limits<size_type>::max());
			}

			void 		resize (size_type n, value_type val = value_type()) {
				reserve(n);

				for (size_type i = _size; i < n; i++)
					_alloc.construct(_array + i, val);

				_size = n;
			}

			size_type capacity() const {
				return (_capacity);
			}

			bool empty() const {
				return (_size == 0);
			}

			void reserve (size_type n) {
				if (n > _capacity) {
					T* array = _alloc.allocate(n);

					for (size_type i = 0; i < _size; i++) {
						_alloc.construct(array + i, _array[i]);
						_alloc.destroy(_array + i);
					}

					_alloc.deallocate(_array, _capacity);
					_capacity = n;
					_array = array;
				}
			}

			/*
			** Element access
			*/
			reference operator[] (size_type n) {
				return (_array[n]);
			}

			const_reference operator[] (size_type n) const {
				return (_array[n]);
			}

			reference at (size_type n) {
				if (n >= _size)
					throw std::out_of_range("Out of range");
				return (_array[n]);
			}

			const_reference at (size_type n) const {
				if (n >= _size)
					throw std::out_of_range("Out of range");
				return (_array[n]);
			}

			reference front() {
				return (_array[0]);
			}

			const_reference front() const {
				return (_array[0]);
			}

			reference back() {
				return (_array[_size - 1]);
			}

			const_reference back() const {
				return (_array[_size - 1]);
			}

			/*
			** Modifiers
			*/

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				clear();
				while (first++ != last)
					push_back(*first);
			}

			void assign (size_type n, const value_type& val) {
				clear();
				while (n--)
					push_back(val);
			}

			void push_back(const value_type& val) {
				if (_capacity == 0)
					reserve(10);
				else if (_size + 1 > _capacity)
					reserve(_size * _scaleFactor);
				_alloc.construct(_array + _size++, val);
			}

			void pop_back() {
				if (!empty())
					_alloc.deallocate(_array, --_size);
			}

			void insert (iterator position, size_type n, const value_type& val) {
				if (ft::distance(end() - position) > n) {

				}
				else {
					
				}
			}

			void clear() {
				while (_size--)
					_alloc.destroy(_array + _size);
			}
	};

}

#endif
