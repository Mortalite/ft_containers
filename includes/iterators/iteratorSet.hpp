#ifndef ITERATORSET_HPP
#define ITERATORSET_HPP

namespace ft {

	template<typename T>
	class SetNode {

	public:
		T*			_data;
		SetNode<T>*	_left;
		SetNode<T>*	_right;
		SetNode<T>*	_parent;

	};

	template <bool flag, class IsTrue, class IsFalse>
	struct choose;

	template <class IsTrue, class IsFalse>
	struct choose<true, IsTrue, IsFalse> {
		typedef IsTrue type;
	};

	template <class IsTrue, class IsFalse>
	struct choose<false, IsTrue, IsFalse> {
		typedef IsFalse type;
	};

	template<bool isConst, typename T, typename Category = std::bidirectional_iterator_tag>
	class IteratorSet {

	private:
		SetNode<T>*	_ptr;

	public:

		typedef std::ptrdiff_t								difference_type;
		typedef T											value_type;
		typedef typename choose<isConst,const T&,T&>::type 	reference;
		typedef typename choose<isConst,const T*,T*>::type 	pointer;
		typedef Category 									iterator_category;

		IteratorSet() {}
		IteratorSet(const IteratorSet<false,T,Category>& other): _ptr(other._ptr) {}
		IteratorSet(const IteratorSet<true,T,Category>& other): _ptr(other.getPtr()) {}
		IteratorSet(SetNode<T>* node): _ptr(node) {}
		~IteratorSet() {}

		SetNode<T>*	getPtr() const { return (_ptr); }
		pointer operator->() const { return (_ptr->_data); }
		reference operator*() const { return (*_ptr->_data); }
		bool operator==(const IteratorSet& other) const { return (_ptr == other._ptr); }
		bool operator!=(const IteratorSet& other) const { return (_ptr != other._ptr); }

		IteratorSet &operator=(const IteratorSet& other) {
			if (this != &other) {
				_ptr = other._ptr;
			}
			return (*this);
		}

		IteratorSet &operator++() {
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

		IteratorSet operator++(int) {
			IteratorSet<isConst,T,Category> tmp(*this);
			operator++();
			return (tmp);
		}

		IteratorSet &operator--() {
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

		IteratorSet operator--(int) {
			IteratorSet<isConst,T,Category> tmp(*this);
			operator--();
			return (tmp);
		}

	};

	template<typename T, typename Category = std::bidirectional_iterator_tag>
	class ReverseIteratorSet {

	private:
		SetNode<T>*	_ptr;

	public:

		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef Category 		iterator_category;

		ReverseIteratorSet() {}
		ReverseIteratorSet(const IteratorSet<false,T,Category>& other): _ptr(other.getPtr()) {}
		ReverseIteratorSet(const ReverseIteratorSet& other): _ptr(other._ptr) {}
		ReverseIteratorSet(SetNode<T>* node): _ptr(node) {}
		~ReverseIteratorSet() {}

		SetNode<T>*	getPtr() const { return (_ptr); }
		pointer operator->() const { return (_ptr->_data); }
		reference operator*() const {
			SetNode<T>* tmp = _ptr;

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
		bool operator==(const ReverseIteratorSet& other) const { return (_ptr == other._ptr); }
		bool operator!=(const ReverseIteratorSet& other) const { return (_ptr != other._ptr); }

		ReverseIteratorSet &operator=(const ReverseIteratorSet& other) {
			if (this != &other) {
				_ptr = other._ptr;
			}
			return (*this);
		}

		ReverseIteratorSet &operator++() {
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

		ReverseIteratorSet operator++(int) {
			ReverseIteratorSet<T,Category> tmp(*this);
			operator++();
			return (tmp);
		}

		ReverseIteratorSet &operator--() {
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

		ReverseIteratorSet operator--(int) {
			ReverseIteratorSet<T,Category> tmp(*this);
			operator--();
			return (tmp);
		}

	};

	template<typename T, typename Category = std::bidirectional_iterator_tag>
	class ConstReverseIteratorSet {

	private:
		SetNode<T>*	_ptr;

	public:

		typedef std::ptrdiff_t	difference_type;
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef Category 		iterator_category;

		ConstReverseIteratorSet() {}
		ConstReverseIteratorSet(const IteratorSet<false,T,Category>& other): _ptr(other.getPtr()) {}
		ConstReverseIteratorSet(const IteratorSet<true,Category>& other): _ptr(other.getPtr()) {}
		ConstReverseIteratorSet(const ReverseIteratorSet<T,Category>& other): _ptr(other.getPtr()) {}
		ConstReverseIteratorSet(const ConstReverseIteratorSet& other): _ptr(other._ptr) {}
		ConstReverseIteratorSet(SetNode<T>* node): _ptr(node) {}
		~ConstReverseIteratorSet() {}

		SetNode<T>*	getPtr() const { return (_ptr); }
		const value_type* operator->() const { return (_ptr->_data); }
		const value_type& operator*() const {
			SetNode<T>* tmp = _ptr;

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
		bool operator==(const ConstReverseIteratorSet& other) const { return (_ptr == other._ptr); }
		bool operator!=(const ConstReverseIteratorSet& other) const { return (_ptr != other._ptr); }

		ConstReverseIteratorSet &operator=(const ConstReverseIteratorSet& other) {
			if (this != &other) {
				_ptr = other._ptr;
			}
			return (*this);
		}

		ConstReverseIteratorSet &operator++() {
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

		ConstReverseIteratorSet operator++(int) {
			ConstReverseIteratorSet<T,Category> tmp(*this);
			operator++();
			return (tmp);
		}

		ConstReverseIteratorSet &operator--() {
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

		ConstReverseIteratorSet operator--(int) {
			ConstReverseIteratorSet<T,Category> tmp(*this);
			operator--();
			return (tmp);
		}

	};

}

#endif
