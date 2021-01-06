#ifndef SET_HPP
#define SET_HPP

namespace ft {

	template < 	class T,                        // set::key_type/value_type
				class Compare = less<T>,        // set::key_compare/value_compare
				class Alloc = allocator<T>      // set::allocator_type
	> class set {

		/*
		** Typedefs
		*/
		public:
			typedef T													key_type;
			typedef T													value_type;
			typedef Compare												key_compare;
			typedef Compare												value_compare;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::IteratorMap<Key, T, value_type>					iterator;
			typedef ft::ReverseIteratorMap<Key, T, value_type>			reverse_iterator;
			typedef ft::ConstIteratorMap<Key, T, value_type>			const_iterator;
			typedef ft::ConstReverseIteratorMap<Key, T, value_type>		const_reverse_iterator;
			typedef std::ptrdiff_t										difference_type;
			typedef std::size_t											size_type;

			/*
			** Class members
			*/
			private:
				TreeNode<const Key, T, value_type>*	_root;
				TreeNode<const Key, T, value_type>*	_begin;
				TreeNode<const Key, T, value_type>*	_end;
				key_compare							_comp;
				allocator_type						_alloc;
				size_type							_size;

	};

}

#endif
