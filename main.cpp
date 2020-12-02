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

template<typename T, typename C> void printCmpIterator(T& ft_container, C& std_container) {
	size_t i = 0;
	if (ft_container.size() != std_container.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}
	typename T::iterator ft_it = ft_container.begin();
	typename C::iterator std_it = std_container.begin();

	std::cout << BLUE << "printCmpIterator" << RESET << std::endl;
	for ( ;ft_it != ft_container.end(); ft_it++, std_it++, i++) {
		std::cout << "ft_container[" << i << "] = " << *ft_it;
		std::cout << "\t\t";
		std::cout << "std_container[" << i << "] = " << *std_it << std::endl;
	}
}

template<typename T> void printRevIterator(T& container) {
	size_t i = container.size();
	std::cout << BLUE << "printRevIterator" << RESET << std::endl;
	for (typename T::reverse_iterator it = container.rbegin(); it != container.rend(); it++)
		std::cout << "container[" << --i << "] = " << *it << std::endl;
}

template<typename T, typename C> void printCmpRevIterator(T& ft_container, C& std_container) {
	size_t i = 0;
	if (ft_container.size() != std_container.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}
	typename T::reverse_iterator ft_it = ft_container.rbegin();
	typename C::reverse_iterator std_it = std_container.rbegin();

	std::cout << BLUE << "printCmpRevIterator" << RESET << std::endl;
	for ( ;ft_it != ft_container.rend(); ft_it++, std_it++, i++) {
		std::cout << "ft_container[" << i << "] = " << *ft_it;
		std::cout << "\t\t";
		std::cout << "std_container[" << i << "] = " << *std_it << std::endl;
	}
}

template<typename T> void containerPushBack(T& container) {
	for (size_t i = 0; i < countRandNumbers; i++)
		container.push_back(rand() % 1000 - 500);
}

int main() {
	srand(time(NULL));

	ft::list<int> ft_list;
	containerPushBack(ft_list);
	std::list<int> std_list(ft_list.begin(), ft_list.end());

	std::cout << RED << "Compare ft_list vs std_list" << RESET << std::endl;
	printCmpIterator(ft_list, std_list);
	printCmpRevIterator(ft_list, std_list);

	std::cout << RED << "Copy constructor and assignment operator" << RESET << std::endl;
	ft::list<int> copyList(ft_list);
	ft::list<int> assignList;
	assignList = ft_list;
	printCmpIterator(copyList, assignList);

	copyList.erase(copyList.begin());
	printIterator(copyList);

	copyList.erase(copyList.begin());
	printIterator(copyList);

	copyList.erase(copyList.begin());
	printIterator(copyList);

	copyList.erase(copyList.begin());
	printIterator(copyList);
	return (0);
}
