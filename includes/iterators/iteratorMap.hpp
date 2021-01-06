#ifndef ITERATORMAP_HPP
#define ITERATORMAP_HPP

namespace ft {

	template<typename Key, typename T>
	class TreeNode {

		public:
			std::pair<const Key,T>*	_data;
			TreeNode<Key,T>*		_left;
			TreeNode<Key,T>*		_right;
			TreeNode<Key,T>*		_parent;

	};

	template<typename Key, typename T, typename Category = std::bidirectional_iterator_tag>
	class IteratorMap {

		private:
			TreeNode<const Key,T>*	_ptr;

		public:

			typedef std::ptrdiff_t			difference_type;
			typedef std::pair<const Key,T>	value_type;
			typedef value_type*				pointer;
			typedef value_type&				reference;
			typedef Category 				iterator_category;

			IteratorMap() {}
			IteratorMap(const IteratorMap& other): _ptr(other._ptr) {}
			IteratorMap(TreeNode<const Key,T>* node): _ptr(node) {}
			~IteratorMap() {}

			TreeNode<const Key,T>*	getPtr() const { return (_ptr); }
			pointer operator->() const { return (_ptr->_data); }
			reference operator*() const { return (*_ptr->_data); }
			bool operator==(const IteratorMap& other) const { return (_ptr == other._ptr); }
			bool operator!=(const IteratorMap& other) const { return (_ptr != other._ptr); }

			IteratorMap &operator=(const IteratorMap& other) {
				_ptr = other._ptr;
				return (*this);
			}

			IteratorMap &operator++() {
				if (_ptr->_right)
				{
					_ptr = _ptr->_right;
					while (_ptr->_left)
						_ptr = _ptr->_left;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_right)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			IteratorMap operator++(int) {
				IteratorMap<Key,T,Category> tmp(*this);
				operator++();
				return (tmp);
			}

			IteratorMap &operator--() {
				if (_ptr->_left)
				{
					_ptr = _ptr->_left;
					while (_ptr->_right)
						_ptr = _ptr->_right;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_left)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			IteratorMap operator--(int) {
				IteratorMap<Key,T,Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename Key, typename T, typename Category = std::bidirectional_iterator_tag>
	class ReverseIteratorMap {

		private:
			TreeNode<const Key,T>*	_ptr;

		public:

			typedef std::ptrdiff_t				difference_type;
			typedef std::pair<const Key,T>		value_type;
			typedef value_type*					pointer;
			typedef value_type&					reference;
			typedef Category 					iterator_category;

			ReverseIteratorMap() {}
			ReverseIteratorMap(const IteratorMap<Key,T>& other): _ptr(other.getPtr()) {}
			ReverseIteratorMap(const ReverseIteratorMap& other): _ptr(other._ptr) {}
			ReverseIteratorMap(TreeNode<const Key,T>* node): _ptr(node) {}
			~ReverseIteratorMap() {}

			TreeNode<const Key,T>*	getPtr() const { return (_ptr); }
			pointer operator->() const { return (_ptr->_data); }
			reference operator*() const {
				TreeNode<const Key,T>* tmp = _ptr;

				if (tmp->_left)
				{
					tmp = tmp->_left;
					while (tmp->_right)
						tmp = tmp->_right;
				}
				else
				{
					while (tmp->_parent && tmp == tmp->_parent->_left)
						tmp = tmp->_parent;
					tmp = tmp->_parent;
				}
				return (*tmp->_data);
			}
			bool operator==(const ReverseIteratorMap& other) const { return (_ptr == other._ptr); }
			bool operator!=(const ReverseIteratorMap& other) const { return (_ptr != other._ptr); }

			ReverseIteratorMap &operator=(const ReverseIteratorMap& other) {
				_ptr = other._ptr;
				return (*this);
			}

			ReverseIteratorMap &operator++() {
				if (_ptr->_left)
				{
					_ptr = _ptr->_left;
					while (_ptr->_right)
						_ptr = _ptr->_right;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_left)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			ReverseIteratorMap operator++(int) {
				ReverseIteratorMap<Key,T,Category> tmp(*this);
				operator++();
				return (tmp);
			}

			ReverseIteratorMap &operator--() {
				if (_ptr->_right)
				{
					_ptr = _ptr->_right;
					while (_ptr->_left)
						_ptr = _ptr->_left;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_right)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			ReverseIteratorMap operator--(int) {
				ReverseIteratorMap<Key,T,Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};

	template<typename Key, typename T, typename Category = std::bidirectional_iterator_tag>
	class ConstIteratorMap {

		private:
			TreeNode<const Key,T>*	_ptr;

		public:

			typedef std::ptrdiff_t				difference_type;
			typedef std::pair<const Key,T>		value_type;
			typedef value_type*					pointer;
			typedef value_type&					reference;
			typedef Category 					iterator_category;

			ConstIteratorMap() {}
			ConstIteratorMap(const IteratorMap<Key,T>& other): _ptr(other.getPtr()) {}
			ConstIteratorMap(const ConstIteratorMap& other): _ptr(other._ptr) {}
			ConstIteratorMap(TreeNode<const Key,T>* node): _ptr(node) {}
			~ConstIteratorMap() {}

			TreeNode<const Key,T>*	getPtr() const { return (_ptr); }
			const value_type* operator->() const { return (_ptr->_data); }
			const value_type& operator*() const { return (*_ptr->_data); }
			bool operator==(const ConstIteratorMap& other) const { return (_ptr == other._ptr); }
			bool operator!=(const ConstIteratorMap& other) const { return (_ptr != other._ptr); }

			ConstIteratorMap &operator=(const ConstIteratorMap& other) {
				_ptr = other._ptr;
				return (*this);
			}

			ConstIteratorMap &operator++() {
				if (_ptr->_right)
				{
					_ptr = _ptr->_right;
					while (_ptr->_left)
						_ptr = _ptr->_left;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_right)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			ConstIteratorMap operator++(int) {
				ConstIteratorMap<Key,T,Category> tmp(*this);
				operator++();
				return (tmp);
			}

			ConstIteratorMap &operator--() {
				if (_ptr->_left)
				{
					_ptr = _ptr->_left;
					while (_ptr->_right)
						_ptr = _ptr->_right;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_left)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			ConstIteratorMap operator--(int) {
				ConstIteratorMap<Key,T,Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};


	template<typename Key, typename T, typename Category = std::bidirectional_iterator_tag>
	class ConstReverseIteratorMap {

		private:
			TreeNode<const Key,T>*	_ptr;

		public:

			typedef std::ptrdiff_t				difference_type;
			typedef std::pair<const Key,T>		value_type;
			typedef value_type*					pointer;
			typedef value_type&					reference;
			typedef Category 					iterator_category;

			ConstReverseIteratorMap() {}
			ConstReverseIteratorMap(const IteratorMap<Key,T>& other): _ptr(other.getPtr()) {}
			ConstReverseIteratorMap(const ConstIteratorMap<Key,T>& other): _ptr(other.getPtr()) {}
			ConstReverseIteratorMap(const ReverseIteratorMap<Key,T>& other): _ptr(other.getPtr()) {}
			ConstReverseIteratorMap(const ConstReverseIteratorMap& other): _ptr(other._ptr) {}
			ConstReverseIteratorMap(TreeNode<const Key,T>* node): _ptr(node) {}
			~ConstReverseIteratorMap() {}

			TreeNode<const Key,T>*	getPtr() const { return (_ptr); }
			const value_type* operator->() const { return (_ptr->_data); }
			const value_type& operator*() const {
				TreeNode<const Key,T>* tmp = _ptr;

				if (tmp->_left)
				{
					tmp = tmp->_left;
					while (tmp->_right)
						tmp = tmp->_right;
				}
				else
				{
					while (tmp->_parent && tmp == tmp->_parent->_left)
						tmp = tmp->_parent;
					tmp = tmp->_parent;
				}
				return (*tmp->_data);
			}
			bool operator==(const ConstReverseIteratorMap& other) const { return (_ptr == other._ptr); }
			bool operator!=(const ConstReverseIteratorMap& other) const { return (_ptr != other._ptr); }

			ConstReverseIteratorMap &operator=(const ConstReverseIteratorMap& other) {
				_ptr = other._ptr;
				return (*this);
			}

			ConstReverseIteratorMap &operator++() {
				if (_ptr->_left)
				{
					_ptr = _ptr->_left;
					while (_ptr->_right)
						_ptr = _ptr->_right;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_left)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			ConstReverseIteratorMap operator++(int) {
				ConstReverseIteratorMap<Key,T,Category> tmp(*this);
				operator++();
				return (tmp);
			}

			ConstReverseIteratorMap &operator--() {
				if (_ptr->_right)
				{
					_ptr = _ptr->_right;
					while (_ptr->_left)
						_ptr = _ptr->_left;
				}
				else
				{
					while (_ptr->_parent && _ptr == _ptr->_parent->_right)
						_ptr = _ptr->_parent;
					_ptr = _ptr->_parent;
				}
				return (*this);
			}

			ConstReverseIteratorMap operator--(int) {
				ConstReverseIteratorMap<Key,T,Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};

}

#endif
