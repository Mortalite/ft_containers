#ifndef ITERATORMAP_HPP
#define ITERATORMAP_HPP

namespace ft {

	template<typename Key, typename T>
	class TreeNode {

		public:
			std::pair<Key, T>*	_data;
			TreeNode<Key,T>*	_left;
			TreeNode<Key,T>*	_right;
			TreeNode<Key,T>*	_parent;

	};

	template<typename Key, typename T, typename Category = std::bidirectional_iterator_tag>
	class IteratorMap {

		private:
			TreeNode<const Key,T>*	_ptr;

		public:

			typedef std::ptrdiff_t				difference_type;
			typedef std::pair<const Key, T>		value_type;
			typedef value_type*					pointer;
			typedef value_type&					reference;
			typedef Category 					iterator_category;

			IteratorMap() {}
			IteratorMap(const IteratorMap &other):_ptr(other._ptr) {}
			IteratorMap(TreeNode<const Key,T> *node):_ptr(node) {}
			~IteratorMap() {}

			TreeNode<const Key,T>*	getPtr() { return (_ptr); }
			bool operator==(const IteratorMap &other) const { return (_ptr == other._ptr); }
			bool operator!=(const IteratorMap &other) const { return (_ptr != other._ptr); }
			reference operator*() { return (*_ptr->_data); }
			pointer operator->() const { return (_ptr->_data); }

			IteratorMap &operator=(const IteratorMap &other) {
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
				IteratorMap<Key, T, Category> tmp(*this);
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
				IteratorMap<Key, T, Category> tmp(*this);
				operator--();
				return (tmp);
			}

	};

}

#endif
