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
				_comp = comp;
				_alloc = alloc;
				_size = 0;
			}

			/*
			** Iterators
			*/

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


			/*
			** Modifiers
			*/

			std::pair<iterator,bool> insert (const value_type& val) {
/*				TreeNode<Key,T> *y = NULL;
				TreeNode<Key,T> *x = _root;
				TreeNode<Key,T> *z = new TreeNode<Key,T>;
				z->_data = _alloc.allocate(1);
				_alloc.construct(z->_data, val);
				while (x) {
					y = x;
					if (z->_data->first < x->_data->first)
						x = x->_left;
					else
						x = x->_right;
				}
				z->_parent = y;
				if (!y)
					_root = z;
				else if (z->_data->first < y->_data->first)
					y->_left = z;
				else
					y->_right = z;*/
				TreeNode<const Key,T> *y = NULL;
				TreeNode<const Key,T> *x = _root;
				while (x) {
					y = x;
					if (val.first == x->_data->first)
						return (std::make_pair(iterator(x), false));
					else if (val.first < x->_data->first)
						x = x->_left;
					else
						x = x->_right;
				}
				TreeNode<const Key,T> *z = new TreeNode<const Key,T>;
				z->_data = _alloc.allocate(1);
				_alloc.construct(z->_data, val);
				z->_parent = y;
				if (!y)
					_root = z;
				else if (z->_data->first < y->_data->first)
					y->_left = z;
				else
					y->_right = z;
				return (std::make_pair(iterator(z), true));
			}

			void runPostOrderTreeWalk() {
				postOrderTreeWalk(_root);
			}

			void postOrderTreeWalk(TreeNode<const Key,T>* treeNode) {
				if (!treeNode)
					return ;
				postOrderTreeWalk(treeNode->_left);
				postOrderTreeWalk(treeNode->_right);
				std::cout << "first = " << treeNode->_data->first << ", second = " << treeNode->_data->second << std::endl;
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
