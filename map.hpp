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

			TreeNode<Key,T>* treeSearch(TreeNode<Key,T> root, value_type& val) {
				while (root && val != root._data->first) {
					if (val < root._data->first)
						root = root._left;
					else
						root = root._right;
				}
				return (root);
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
				bool isRightMost = true;
				while (x && x != _end) {
					y = x;
					if (_comp(val.first, x->_data->first)) {
						x = x->_left;
						isRightMost = false;
					}
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
				else {
					y->_right = z;
					if (isRightMost) {
						z->_right = _end;
						_end->_parent = z;
					}
				}
				_size++;
				return (std::make_pair(iterator(z), true));
			}

			iterator insert (iterator position, const value_type& val) {

			}

			void	clear() {
				iterator first = this->begin(), last = this->end();

				while (first != last) {
					_alloc.destroy(&(*first));
					first++;
					_size--;
				}
			}

			void runPostOrderTreeWalk() {
				postOrderTreeWalk(_root);
			}

			void postOrderTreeWalk(TreeNode<const Key,T>* treeNode) {
				if (!treeNode || treeNode == _end)
					return ;
				postOrderTreeWalk(treeNode->_left);
				postOrderTreeWalk(treeNode->_right);
				std::cout << "first = " << treeNode->_data->first << ", second = " << treeNode->_data->second << std::endl;
			}

			void runInOrderTreeWalk() {
				InOrderTreeWalk(_root);
			}

			void InOrderTreeWalk(TreeNode<const Key,T>* treeNode) {
				if (!treeNode || treeNode == _end)
					return ;
				InOrderTreeWalk(treeNode->_left);
				std::cout << "first = " << treeNode->_data->first << ", second = " << treeNode->_data->second << std::endl;
				InOrderTreeWalk(treeNode->_right);
			}

			/*
			** Observers
			*/

			/*
			** Operations
			*/


	};

}

#endif
