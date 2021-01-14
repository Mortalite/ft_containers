#ifndef PRINT_HPP
#define PRINT_HPP

#include "defines.hpp"

namespace ft {

/*
** Simple containers
*/
	template<typename T>
	void printIterator(T &container) {
		size_t i = 0;
		std::cout << BLUE << "ForwardIterator" << RESET << std::endl;
		for (typename T::iterator it = container.begin(); it != container.end(); it++)
			std::cout << "container[" << i++ << "] = " << *it << std::endl;
	}

	template<typename T, typename C>
	void printCmpIterator(T &mainContainer, C &alterContainer) {
		size_t i = 0;
		bool isEqual = true;

		if (mainContainer.size() != alterContainer.size()) {
			std::cerr << "Container diff size" << std::endl;
			return;
		}

		typename T::iterator mainIt = mainContainer.begin();
		typename C::iterator alterIt = alterContainer.begin();

		std::cout << BLUE << "ForwardIterator" << RESET << std::endl;
		for (; mainIt != mainContainer.end(); mainIt++, alterIt++, i++) {
			std::cout << "mainContainer[" << i << "] = " << std::setw(g_printMargin) << *mainIt;
			std::cout << "alterContainer[" << i << "] = " << *alterIt << std::endl;
			if (*mainIt != *alterIt)
				isEqual = false;
		}

		if (isEqual)
			std::cout << "Containers are equal" << std::endl;
		else
			std::cout << "Containers are not equal" << std::endl;

	}

	template<typename T>
	void printRevIterator(T &container) {
		size_t i = container.size();
		std::cout << BLUE << "ReverseIterator" << RESET << std::endl;
		for (typename T::reverse_iterator it = container.rbegin(); it != container.rend(); it++)
			std::cout << "container[" << --i << "] = " << *it << std::endl;
	}

	template<typename T, typename C>
	void printCmpRevIterator(T &mainContainer, C &alterContainer) {
		size_t i = 0;
		bool isEqual = true;

		if (mainContainer.size() != alterContainer.size()) {
			std::cerr << "Container diff size" << std::endl;
			return;
		}

		typename T::reverse_iterator mainIt = mainContainer.rbegin();
		typename C::reverse_iterator alterIt = alterContainer.rbegin();

		std::cout << BLUE << "ReverseIterator" << RESET << std::endl;
		for (; mainIt != mainContainer.rend(); mainIt++, alterIt++, i++) {
			std::cout << "mainContainer[" << i << "] = " << std::setw(g_printMargin) << *mainIt;
			std::cout << "alterContainer[" << i << "] = " << *alterIt << std::endl;
			if (*mainIt != *alterIt)
				isEqual = false;
		}

		if (isEqual)
			std::cout << "Containers are equal" << std::endl;
		else
			std::cout << "Containers are not equal" << std::endl;
	}

/*
** Map, multimap
*/
	template<typename T>
	void printIteratorMap(T &container) {
		std::cout << BLUE << "ForwardIterator" << RESET << std::endl;

		size_t i = 0;
		for (typename T::iterator it = container.begin(); it != container.end(); it++)
			std::cout << "container[" << i++ << "] = (" << (*it).first << ", " << (*it).second << ")" << std::endl;
	}

	template<typename T>
	void printRevIteratorMap(T &container) {
		std::cout << BLUE << "ReverseIterator" << RESET << std::endl;

		size_t i = 0;
		for (typename T::iterator it = container.rbegin(); it != container.rend(); it++)
			std::cout << "container[" << i++ << "] = (" << (*it).first << ", " << (*it).second << ")" << std::endl;
	}

	template<typename T, typename C>
	void printCmpIteratorMap(T &mainContainer, C &alterContainer) {
		std::cout << BLUE << "ForwardIterator" << RESET << std::endl;

		size_t i = 0;
		bool isEqual = true;

		if (mainContainer.size() != alterContainer.size()) {
			std::cerr << "Container diff size" << std::endl;
			return;
		}
		typename T::iterator mainIt = mainContainer.begin();
		typename C::iterator alterIt = alterContainer.begin();

		for (; mainIt != mainContainer.end(); mainIt++, alterIt++, i++) {
			std::stringstream stringStream;
			stringStream << "mainContainer[" << i << "] = (" << (*mainIt).first << ", " << (*mainIt).second << ")";
			std::cout << std::setw(g_printMargin * g_mapMarginCoeff) << stringStream.str();
			std::cout << "alterContainer[" << i << "] = (" << (*alterIt).first << ", " << (*alterIt).second << ")"
					  << std::endl;
			if ((*mainIt).first != (*alterIt).first || (*mainIt).second != (*alterIt).second)
				isEqual = false;
		}

		if (isEqual)
			std::cout << "Containers are equal" << std::endl;
		else
			std::cout << "Containers are not equal" << std::endl;

	}

	template<typename T, typename C>
	void printCmpRevIteratorMap(T &mainContainer, C &alterContainer) {
		std::cout << BLUE << "ReverseIterator" << RESET << std::endl;

		size_t i = 0;
		bool isEqual = true;

		if (mainContainer.size() != alterContainer.size()) {
			std::cerr << "Container diff size" << std::endl;
			return;
		}
		typename T::reverse_iterator mainIt = mainContainer.rbegin();
		typename C::reverse_iterator alterIt = alterContainer.rbegin();

		for (; mainIt != mainContainer.rend(); mainIt++, alterIt++, i++) {
			std::stringstream stringStream;
			stringStream << "mainContainer[" << i << "] = (" << (*mainIt).first << ", " << (*mainIt).second << ")";
			std::cout << std::setw(g_printMargin * g_mapMarginCoeff) << stringStream.str();
			std::cout << "alterContainer[" << i << "] = (" << (*alterIt).first << ", " << (*alterIt).second << ")"
					  << std::endl;
			if ((*mainIt).first != (*alterIt).first || (*mainIt).second != (*alterIt).second)
				isEqual = false;
		}

		if (isEqual)
			std::cout << "Containers are equal" << std::endl;
		else
			std::cout << "Containers are not equal" << std::endl;

	}

}

#endif
