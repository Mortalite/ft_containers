#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace ft {

	template<class T, class Container = list <T> >
	class stack {

		/*
		** Typedefs
		*/
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		/*
		** Class member
		*/
		private:
			container_type container;

		public:
			/*
			** Constructor
			*/
			explicit stack (const container_type& ctnr = container_type()) {
				container = ctnr;
			}

			/*
			** Member functions
			*/
			bool		empty() const {
				return (container.empty());
			}

			size_type	size() const {
				return (container.size());
			}

			value_type&			top() {
				return (container.back());
			}

			const value_type&	top() const {
				return (container.back());
			}

			void				push (const value_type& val) {
				container.push_back(val);
			}

			void				pop() {
				container.pop_back();
			}

			/*
			** Non-member functions overloads
			*/
			friend bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return (lhs.container == rhs.container);	}
			friend bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return (lhs.container != rhs.container);	}
			friend bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return (lhs.container < rhs.container);	}
			friend bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return (lhs.container <= rhs.container);	}
			friend bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return (lhs.container > rhs.container);	}
			friend bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {	return (lhs.container >= rhs.container);	}

	};

}

#endif
