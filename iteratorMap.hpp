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

			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef Category 		iterator_category;

			IteratorMap() {}
			IteratorMap(const IteratorMap &other):_ptr(other._ptr) {}
			IteratorMap(TreeNode<const Key,T> *node):_ptr(node) {}
			~IteratorMap() {}

			TreeNode<Key,T>*	getPtr() { return (_ptr); }
			bool operator==(const IteratorMap &other) const { return (_ptr == other._ptr); }
			bool operator!=(const IteratorMap &other) const { return (_ptr != other._ptr); }
			reference operator*() { return (*_ptr->_data); }
			pointer operator->() const { return (_ptr->_data); }

			IteratorMap &operator=(const IteratorMap &other) {
				_ptr = other._ptr;
				return (*this);
			}

			IteratorMap &operator++() {
				if (_ptr && _ptr->_next)
					_ptr = _ptr->_next;
				return (*this);
			}

			IteratorMap operator++(int) {
				IteratorList < T, Category > tmp(*this);
				operator++();
				return (tmp);
			}

			IteratorMap &operator--() {
				if (_ptr && _ptr->_prev)
					_ptr = _ptr->_prev;
				return (*this);
			}

			IteratorMap operator--(int) {
				IteratorList < T, Category > tmp(*this);
				operator--();
				return (tmp);
			}

	};

}

#endif
