#include <iostream>
#include <typeinfo>
#include <list>
#include <cstdlib>
#include "list.hpp"
#include "iterator.h"

#define RED		"\033[31m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

const int countRandNumbers = 5;

template<typename T> void printIterator(T& container) {
	size_t i = 0;
	std::cout << BLUE << "printIterator" << RESET << std::endl;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << "container[" << i++ << "] = " << *it << std::endl;
}

template<typename T, typename C> void printCmpIterator(T& ftContainer, C& stdContainer) {
	size_t i = 0;
	if (ftContainer.size() != stdContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}
	typename T::iterator ft_it = ftContainer.begin();
	typename C::iterator std_it = stdContainer.begin();

	std::cout << BLUE << "printCmpIterator" << RESET << std::endl;
	for ( ; ft_it != ftContainer.end(); ft_it++, std_it++, i++) {
		std::cout << "ftContainer[" << i << "] = " << *ft_it;
		std::cout << "\t\t";
		std::cout << "stdContainer[" << i << "] = " << *std_it << std::endl;
	}
}

template<typename T> void printRevIterator(T& container) {
	size_t i = container.size();
	std::cout << BLUE << "printRevIterator" << RESET << std::endl;
	for (typename T::reverse_iterator it = container.rbegin(); it != container.rend(); it++)
		std::cout << "container[" << --i << "] = " << *it << std::endl;
}

template<typename T, typename C> void printCmpRevIterator(T& ftContainer, C& stdContainer) {
	size_t i = 0;
	if (ftContainer.size() != stdContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}
	typename T::reverse_iterator ft_it = ftContainer.rbegin();
	typename C::reverse_iterator std_it = stdContainer.rbegin();

	std::cout << BLUE << "printCmpRevIterator" << RESET << std::endl;
	for ( ; ft_it != ftContainer.rend(); ft_it++, std_it++, i++) {
		std::cout << "ft_container[" << i << "] = " << *ft_it;
		std::cout << "\t\t";
		std::cout << "std_container[" << i << "] = " << *std_it << std::endl;
	}
}

template<typename T, typename C> void printCmpPopFront(T& ftContainer, C& stdContainer) {

	if (ftContainer.size() != stdContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}

	std::cout << BLUE << "printCmpPopFront" << RESET << std::endl;
	while (!ftContainer.empty()) {
		printCmpIterator(ftContainer, stdContainer);
		ftContainer.pop_front();
		stdContainer.pop_front();
	}
}

template<typename T> void containerPushBack(T& container) {
	for (size_t i = 0; i < countRandNumbers; i++)
		container.push_back(rand() % 1000 - 500);
}

int main() {
	srand(time(NULL));

	ft::list<int> ftList;
	containerPushBack(ftList);
	std::list<int> stdList(ftList.begin(), ftList.end());

	std::cout << RED << "Compare ftList vs stdList" << RESET << std::endl;
	printCmpIterator(ftList, stdList);
	printCmpRevIterator(ftList, stdList);

	std::cout << RED << "Copy constructor and assignment operator" << RESET << std::endl;
	ft::list<int> copyList(ftList);
	ft::list<int> assignList;
	assignList = ftList;
	printCmpIterator(copyList, assignList);

	std::cout << RED << "Erase all" << RESET << std::endl;
	copyList.erase(copyList.begin(), copyList.end());
	printIterator(copyList);

	std::cout << RED << "Compare popFront function" << RESET << std::endl;
	stdList.assign(copyList.begin(), copyList.end());
	printCmpPopFront(copyList, stdList);

	return (0);
}
