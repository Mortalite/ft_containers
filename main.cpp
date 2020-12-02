#include <iostream>
#include <typeinfo>
#include <list>
#include "list.hpp"
#include "iterator.h"

#define RED		"\033[31m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

int main() {

	ft::list<int> list;

	if (typeid(ft::list<int>::value_type) == typeid(int))
	std::cout << "value_type = int" << std::endl;

	std::cout << "size = " << list.size() << ", isEmpty = " << list.empty() << std::endl;

	list.push_front(10);
	list.push_front(20);
	list.front() += 1000;
	list.push_front(30);
	list.back() -= 15;
	list.push_back(-1000);
	list.back() += 500;
	list.print();

	std::cout << BLUE << "CopyList" << RESET << std::endl;
	ft::list<int> listCopy(list);
	listCopy.print();

	std::cout << "size = " << list.size() << ", isEmpty = " << list.empty() << std::endl;
	std::cout << "max_size = " << list.max_size() << std::endl;

	typedef std::list<int> Ilist;
	std::list<int> list1;
	list1.push_back(10);
	Ilist::iterator iterator(list1.begin());
	Ilist::iterator iterator1 = iterator;
	std::cout << "iterator value = " << *iterator1 << std::endl;

	typedef ft::list<int> Flist;
	Flist::iterator iterator2(list.begin());
	while (iterator2 != list.end())
		std::cout << "value = " << *iterator2++ << std::endl;

	ft::ReverseBidirectionalIterator<int> iterator3;

	return 0;
}
