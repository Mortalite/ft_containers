#ifndef MAP_HPP
#define MAP_HPP

namespace ft {

	template<typename K, typename T>
	class RedBlackTreeNode {
		K*				_key;
		T*				_data;
		TreeNode<T>*	_left;
		TreeNode<T>*	_right;
		TreeNode<T>*	_parent;
		short 			_color;
	};

	template 	< 	class Key,                                     // map::key_type
					class T,                                       // map::mapped_type
					class Compare = less<Key>,                     // map::key_compare
					class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
				>
	class map {

		/*
		** Typedefs
		*/
		public:
			typedef Key											key_type;
			typedef T											mapped_value;
			typedef pair<const key_type,mapped_type>			value_type;
			typedef Compare										key_compare;
			//typedef
			typedef Alloc										allocator_type;
			typedef reference									allocator_type::reference;
			typedef const_reference								allocator_type::const_reference;
			typedef pointer										allocator_type::pointer;
			typedef const_pointer								allocator_type::const_pointer;
//			typedef ft::IteratorList<T>							iterator;
//			typedef ft::ReverseIteratorList<T>					reverse_iterator;
//			typedef ft::ConstIteratorList<T>					const_iterator;
//			typedef ft::ConstReverseIteratorList<T>				const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

		/*
		** Class members
		*/
		private:
			RedBlackTreeNode<Key,T>*	_root;
			key_compare					comp;
			allocator_type				_alloc;
			size_type					_size;

		public:

	};

}

#endif
