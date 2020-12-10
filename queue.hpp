#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace ft {

	template <class T, class Container = list<T> >
	class queue {

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
			Container 			container;

		public:
			/*
			** Constructor
			*/
			explicit 			queue (const container_type& ctnr = container_type()) {
				container = ctnr;
			}

			/*
			** Member functions
			*/
			bool 				empty() const {
				return (list.empty());
			}

			size_type 			size() const {
				return (list.size());
			}

			value_type& 		front() {
				return (list.front());
			}

			const value_type& 	front() const {
				return (list.front());
			}

			value_type& 		back() {
				return (list.back());
			}

			const value_type& 	back() const {
				return (list.back());
			}

			void 				push (const value_type& val) {
				list.push_back(val);
			}

			void 				pop() {
				list.pop_front();
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
