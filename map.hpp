#ifndef MAP_HPP
#define MAP_HPP

#include "iteratorMap.hpp"

namespace ft {

	template 	< 	class Key,                                     // map::key_type
					class T,                                       // map::mapped_type
					class Compare = std::less<Key>,                     // map::key_compare
					class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
				>
	class map {

		/*
		** Typedefs
		*/
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef std::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::IteratorMap<Key,T>						iterator;
//			typedef ft::ReverseIteratorList<T>					reverse_iterator;
//			typedef ft::ConstIteratorList<T>					const_iterator;
//			typedef ft::ConstReverseIteratorList<T>				const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

			class value_compare: public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
			};

		/*
		** Class members
		*/
		private:
			TreeNode<const Key,T>*	_root;
			TreeNode<const Key,T>*	_begin;
			TreeNode<const Key,T>*	_end;
			key_compare				_comp;
			allocator_type			_alloc;
			size_type				_size;

			TreeNode<const Key,T>* treeMinimum(TreeNode<const Key,T>* ptr) {
				TreeNode<const Key,T>* leftMost = ptr;

				while (leftMost->_left)
					leftMost = leftMost->_left;

				return (leftMost);
			}

			TreeNode<const Key,T>* treeMaximum(TreeNode<const Key,T>* ptr) {
				TreeNode<const Key,T>* rightMost = ptr;

				while (rightMost->_right)
					rightMost = rightMost->_right;

				return (rightMost);
			}

			void refresh_iterators() {
				TreeNode<const Key,T>* leftMost = this->treeMinimum(_root), *rightMost = this->treeMaximum(_root);

				_begin = leftMost;
				if (_end && _end->_parent && _end->_parent->_right != _end) {
					rightMost->_right = _end;
					_end->_parent = rightMost;
				}
/*				if (_begin && _begin->_parent && _begin->_parent->_left != _begin) {
					leftMost->_left = _begin;
					_begin->_parent = leftMost;
				}*/
			}

			void transplant(TreeNode<const Key,T> *first, TreeNode<const Key,T> *second) {
				if (!first->_parent)
					_root = second;
				else if (first == first->_parent->_left)
					first->_parent->_left = second;
				else
					first->_parent->_right = second;
				if (second)
					second->_parent = first->_parent;
			}


		public:
			/*
			** Constructors
			*/
			explicit map (const key_compare& comp = key_compare(),
						  const allocator_type& alloc = allocator_type()) {
				_root = NULL;
				_begin = _end = new TreeNode<const Key,T>;
				_begin->_left = _begin->_right = _end->_left = _end->_right = NULL;
				_begin->_data = _end->_data = NULL;
				_comp = comp;
				_alloc = alloc;
				_size = 0;
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				 const key_compare& comp = key_compare(),
				 const allocator_type& alloc = allocator_type()) {
				_root = NULL;
				_begin = _end = new TreeNode<const Key,T>;
				_begin->_left = _begin->_right = _end->_left = _end->_right = NULL;
				_comp = comp;
				_alloc = alloc;
				_size = 0;
				while (first != last)
					insert(*first++);
			}

			map (const map& x) {
				_root = NULL;
				_begin = _end = new TreeNode<const Key,T>;
				_begin->_left = _begin->_right = _end->_left = _end->_right = NULL;
				_comp = x._comp;
				_alloc = x._alloc;
				_size = 0;

				if (x.size()) {
					iterator first = x.begin(), last = x.end();
					while (first != last)
						insert(*first++);
				}
			}

			~map() {
				clear();
				delete _end;
			}

			/*
			** Iterators
			*/
			iterator	begin() {
				return (iterator(_begin));
			}

			iterator	end() {
				return (iterator(_end));
			}


			/*
			** Capacity
			*/
			bool 		empty() const {
				return (_size == 0);
			}

			size_type	size() const {
				return (_size);
			}

			size_type	max_size() const {
				return (_alloc.max_size());
			}

			/*
			** Element access
			*/
			mapped_type& operator[](const key_type& k) {
				return ((*((this->insert(make_pair(k,mapped_type()))).first)).second);
			};

			/*
			** Modifiers
			*/

			std::pair<iterator,bool> insert (const value_type& val) {
				TreeNode<const Key,T> *y = NULL;
				TreeNode<const Key,T> *x = _root;
				while (x && x != _end) {
					y = x;
					if (_comp(val.first, x->_data->first))
						x = x->_left;
					else if (_comp(x->_data->first, val.first))
						x = x->_right;
					else
						return (std::make_pair(iterator(x), false));
				}
				TreeNode<const Key,T> *z = new TreeNode<const Key,T>;
				z->_data = _alloc.allocate(1);
				_alloc.construct(z->_data, val);
				z->_parent = y;
				z->_left = z->_right = NULL;
				if (!y) {
					z->_right = _end;
					_root = _begin = _end->_parent = z;
				}
				else if (_comp(z->_data->first, y->_data->first))
					y->_left = _begin = z;
				else
					y->_right = z;
				_size++;
				refresh_iterators();
				return (std::make_pair(iterator(z), true));
			}

			iterator insert (iterator position, const value_type& val) {
				TreeNode<const Key,T> *y = NULL;
				TreeNode<const Key,T> *x = position;
				while (x && x != _end) {
					y = x;
					if (_comp(val.first, x->_data->first))
						x = x->_left;
					else if (_comp(x->_data->first, val.first))
						x = x->_right;
					else
						return (iterator(x));
				}
				TreeNode<const Key,T> *z = new TreeNode<const Key,T>;
				z->_data = _alloc.allocate(1);
				_alloc.construct(z->_data, val);
				z->_parent = y;
				z->_left = z->_right = NULL;
				if (!y) {
					z->_right = _end;
					_root = _begin = _end->_parent = z;
				}
				else if (_comp(z->_data->first, y->_data->first))
					y->_left = _begin = z;
				else
					y->_right = z;
				_size++;
				refresh_iterators();
				return (iterator(z));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) {
				while (first != last)
					insert(*first++);
			}

			void erase (iterator position) {
				TreeNode<const Key,T>* ptr = position.getPtr(), *y;

				if (!ptr->_left)
					transplant(ptr, ptr->_right);
				else if (!ptr->_right)
					transplant(ptr, ptr->_left);
				else {
					y = treeMinimum(ptr->_right);
					if (y->_parent != ptr) {
						transplant(y, y->_right);
						y->_right = ptr->_right;
						y->_right->_parent = y;
					}
					transplant(ptr, y);
					y->_left = ptr->_left;
					y->_left->_parent = y;
				}
				_alloc.destroy(ptr->_data);
				_alloc.deallocate(ptr->_data, 1);
				delete ptr;
				_size--;
				refresh_iterators();
			}

			size_type erase (const key_type& k) {
				iterator del = find(k);
				if (del == end())
					return (0);
				erase(del);
				return (1);
			}

			void erase (iterator first, iterator last) {
				iterator tmp;

				while (first != last) {
					tmp = first++;
					erase(tmp);
				}
			}

			void swap (map& x) {
				ft::swap(_root, x._root);
				ft::swap(_begin, x._begin);
				ft::swap(_end, x._end);
				ft::swap(_comp, x._comp);
				ft::swap(_alloc, x._alloc);
				ft::swap(_size, x._size);
			}

			void	clear() {
				while (!empty())
					erase(this->begin());
			}

			/*
			** Observers
			*/
			key_compare		key_comp() const {
				return (_comp);
			}

			value_compare	value_comp() const {
				return (value_compare(_comp));
			}

			/*
			** Operations
			*/
			iterator find (const key_type& k) {
				iterator first = this->begin(), last = this->end();

				while (first != last) {
					if (!_comp((*first).first, k) && !_comp(k, (*first).first))
						return (first);
					first++;
				}
				return (last);
			}

/*			const_iterator find (const key_type& k) const {
				const_iterator first = this->begin(), last = this->end();

				while (first != last) {
					if (!_comp((*first).first, k) && !_comp(k, (*first).first))
						return (first);
					first++;
				}
				return (last);
			}*/

/*			size_type count (const key_type& k) const {
				return (this->find(k) != this->end());
			}*/

			iterator lower_bound (const key_type& k) {
				iterator first = begin(), last = end();

				while (first != last) {
					if (!(_comp((*first).first, k)))
						return (first);
					first++;
				}
				return (last);
			}

//			const_iterator lower_bound (const key_type& k) const {
//
//			}

			iterator upper_bound (const key_type& k) {
				iterator first = begin(), last = end();

				while (first != last) {
					if (_comp(k, (*first).first))
						return (first);
					first++;
				}
				return (last);
			}

//			const_iterator upper_bound (const key_type& k) const {
//
//			}

			std::pair<iterator,iterator>	equal_range (const key_type& k) {
				iterator upperBound = upper_bound(k);


			}

	};

}

#endif
