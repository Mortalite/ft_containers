#include <iostream>
#include <typeinfo>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include "list.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "iteratorList.hpp"

#define RED		"\033[31m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

const	int countRandNumbers = 4;
typedef int cType;

template<typename T>
void printIterator(T& container) {
	size_t i = 0;
	std::cout << BLUE << "printIterator" << RESET << std::endl;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << "container[" << i++ << "] = " << *it << std::endl;
}

template<typename T>
void printIteratorMap(T& container) {
	size_t i = 0;
	std::cout << BLUE << "printIterator" << RESET << std::endl;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << "container[" << i++ << "] = (" << (*it).first << ", " << (*it).second << ")" << std::endl;
}

template<typename T, typename C>
void printCmpIterator(T& ftContainer, C& stdContainer) {
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

template<typename T>
void printRevIterator(T& container) {
	size_t i = container.size();
	std::cout << BLUE << "printRevIterator" << RESET << std::endl;
	for (typename T::reverse_iterator it = container.rbegin(); it != container.rend(); it++)
		std::cout << "container[" << --i << "] = " << *it << std::endl;
}

template<typename T, typename C>
void printCmpRevIterator(T& ftContainer, C& stdContainer) {
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

template<typename T>
void containerPushBack(T& container) {
	int intMin = -500, intMax = 500;
	float floatMin = -500.0, floatMax = 500.0;
	for (size_t i = 0; i < countRandNumbers; i++) {
		if (typeid(typename T::value_type) == typeid(int))
			container.push_back(rand() % (intMax - intMin) + intMin);
		else if (typeid(typename T::value_type) == typeid(float) || typeid(typename T::value_type) == typeid(double))
			container.push_back(static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(floatMax - floatMin))) + floatMin);
	}
}

template<typename T>
typename T::value_type getRandomValue() {
	int intMin = -500, intMax = 500;
	float floatMin = -500.0, floatMax = 500.0;
	for (size_t i = 0; i < countRandNumbers; i++) {
		if (typeid(typename T::value_type) == typeid(int))
			return (rand() % (intMax - intMin) + intMin);
		else if (typeid(typename T::value_type) == typeid(float) || typeid(typename T::value_type) == typeid(double))
			return (static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(floatMax - floatMin))));
	}
	return (0);
}

bool isPositive(const int& val) {
	return (val > 0);
}

bool isGreater(const int& val1, const int& val2) {
	return (val1 > val2);
}

template<typename T, typename C>
void testConstructors() {
	std::cout << RED << "Constructors" << RESET << std::endl;

	T ftContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());
	C stdContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());

	std::cout << BLUE << "Fill Constructor (5, rand<T>())" << RESET << std::endl;
	printCmpIterator(ftContainerFill, stdContainerFill);

	std::cout << BLUE << "Range Constructor" << RESET << std::endl;
	T ftContainerRange(ftContainerFill.begin(), ftContainerFill.end());
	C stdContainerRange(stdContainerFill.begin(), stdContainerFill.end());
	printCmpIterator(ftContainerRange, stdContainerRange);

	std::cout << BLUE << "Copy Constructor" << RESET << std::endl;
	T ftContainerCopy(ftContainerRange);
	C stdContainerCopy(stdContainerRange);
	printCmpIterator(ftContainerCopy, stdContainerCopy);
}

template<typename T, typename C>
void testIterators() {
	std::cout << RED << "Iterators" << RESET << std::endl;

	T ftContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());
	C stdContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());

	std::cout << BLUE << "Fill Constructor (5, rand<T>())" << RESET << std::endl;
	printCmpIterator(ftContainerFill, stdContainerFill);
	printCmpRevIterator(ftContainerFill, stdContainerFill);
}

template<typename T, typename C>
void testAssign() {
	std::cout << RED << "Assign function" << RESET << std::endl;

	T ftContainer;
	C stdContainer;

	containerPushBack(stdContainer);
	ftContainer.assign(stdContainer.begin(), stdContainer.end());
	printCmpIterator(ftContainer, stdContainer);

	T ftContainer2;
	ftContainer2.assign(11, (typename T::size_type)10);
	C stdContainer2;
	stdContainer2.assign(11,(typename C::size_type)10);
	printCmpIterator(ftContainer2, stdContainer2);
}

template<typename T, typename C>
void testPushFront() {
	std::cout << RED << "PushFront function" << RESET << std::endl;

	T ftContainer;
	C stdContainer;

	while (ftContainer.size() != countRandNumbers) {
		typename T::value_type randomValue = getRandomValue<T>();
		ftContainer.push_front(randomValue);
		stdContainer.push_front(randomValue);
		printCmpIterator(ftContainer, stdContainer);
	}
}

template<typename T, typename C>
void testPopFront()
{
	T ftContainer;
	containerPushBack(ftContainer);

	C stdContainer(ftContainer.begin(), ftContainer.end());

	if (ftContainer.size() != stdContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}

	std::cout << RED << "PopFront function" << RESET << std::endl;
	while (!ftContainer.empty()) {
		printCmpIterator(ftContainer, stdContainer);
		ftContainer.pop_front();
		stdContainer.pop_front();
	}
}

template<typename T, typename C>
void testInsert() {
	std::cout << RED << "Insert function" << RESET << std::endl;

	T ftContainer;
	typename T::iterator ftIt;

	C stdContainer(ftContainer.begin(), ftContainer.end());
	typename C::iterator stdIt;

	typename T::value_type randomValue = getRandomValue<T>();
	typename T::size_type randomTimes = (abs(getRandomValue<T>()))%4 + 1;
	std::cout << BLUE << "Insert " << randomValue << " in begin()" << RESET << std::endl;
	ftIt = ftContainer.insert(ftContainer.begin(), randomValue);
	stdIt = stdContainer.insert(stdContainer.begin(), randomValue);
	printCmpIterator(ftContainer, stdContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
	ftIt = ftContainer.insert(ftContainer.end(), randomValue);
	stdIt = stdContainer.insert(stdContainer.end(), randomValue);
	printCmpIterator(ftContainer, stdContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
	ftIt = ftContainer.insert(ftContainer.end(), randomValue);
	stdIt = stdContainer.insert(stdContainer.end(), randomValue);
	printCmpIterator(ftContainer, stdContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in begin() " << randomTimes << " times" << RESET << std::endl;
	ftContainer.insert(ftContainer.begin(), randomTimes, randomValue);
	stdContainer.insert(stdContainer.begin(), randomTimes, randomValue);
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Insert previous array in begin()" << RESET << std::endl;
	T ftContainerCopy(ftContainer);
	C stdContainerCopy(stdContainer);
	ftContainerCopy.insert(ftContainerCopy.begin(), ftContainer.begin(), ftContainer.end());
	stdContainerCopy.insert(stdContainerCopy.begin(), stdContainer.begin(), stdContainer.end());
	printCmpIterator(ftContainerCopy, stdContainerCopy);
}

template<typename T, typename C>
void testErase() {
	std::cout << RED << "Erase function" << RESET << std::endl;

	T ftContainer;
	containerPushBack(ftContainer);
	C stdContainer(ftContainer.begin(), ftContainer.end());
	printCmpIterator(ftContainer, stdContainer);

	typename T::iterator ftIt;
	typename C::iterator stdIt;

	std::cout << BLUE << "testErase begin()" << RESET << std::endl;
	ftIt = ftContainer.erase(ftContainer.begin());
	stdIt = stdContainer.erase(stdContainer.begin());
	printCmpIterator(ftContainer, stdContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	std::cout << BLUE << "testErase [begin(), end() - 1)" << RESET << std::endl;
	ftIt = ftContainer.erase(ftContainer.begin(), --ftContainer.end());
	stdIt = stdContainer.erase(stdContainer.begin(), --stdContainer.end());
	printCmpIterator(ftContainer, stdContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	std::cout << BLUE << "After Erase" << RESET << std::endl;
	printCmpIterator(ftContainer, stdContainer);
}

template<typename T, typename C>
void testSwap() {
	std::cout << RED << "Swap function" << RESET << std::endl;

	T ftContainer;
	containerPushBack(ftContainer);
	C stdContainer;
	containerPushBack(stdContainer);

	if (ftContainer.size() != stdContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}

	std::cout << RED << "Before Swap" << RESET << std::endl;
	printCmpIterator(ftContainer, stdContainer);
	ftContainer.swap(stdContainer);
	std::cout << RED << "After Swap" << RESET << std::endl;
	printCmpIterator(ftContainer, stdContainer);
}

template<typename T, typename C>
void testResize() {
	std::cout << RED << "Resize function" << RESET << std::endl;

	T ftContainer;
	containerPushBack(ftContainer);
	C stdContainer(ftContainer.begin(), ftContainer.end());
	printCmpIterator(ftContainer, stdContainer);


	std::cout << BLUE << "Resize(5)" << RESET << std::endl;
	ftContainer.resize(5);
	stdContainer.resize(5);
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Resize(8, 100)" << RESET << std::endl;
	ftContainer.resize(8, 100);
	stdContainer.resize(8, 100);
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Resize(12)" << RESET << std::endl;
	ftContainer.resize(12);
	stdContainer.resize(12);
	printCmpIterator(ftContainer, stdContainer);
}

template<typename T, typename C>
void testSplice() {
	std::cout << RED << "Splice function" << RESET << std::endl;

	T sharedContainer1;
	containerPushBack(sharedContainer1);
	C sharedContainer2(sharedContainer1.begin(), sharedContainer1.end());

	T ftContainer;
	C stdContainer;
	printIterator(sharedContainer1);

	std::cout << BLUE << "Splice begin()" << RESET << std::endl;
	ftContainer.splice(ftContainer.begin(), sharedContainer1);
	stdContainer.splice(stdContainer.begin(), sharedContainer2);
	printCmpIterator(ftContainer, stdContainer);
	printCmpIterator(sharedContainer1, sharedContainer2);

	std::cout << BLUE << "Splice second element" << RESET << std::endl;
	sharedContainer1.splice(sharedContainer1.begin(), ftContainer, ++ftContainer.begin());
	sharedContainer2.splice(sharedContainer2.begin(), stdContainer, ++stdContainer.begin());
	printCmpIterator(ftContainer, stdContainer);
	printCmpIterator(sharedContainer1, sharedContainer2);

	std::cout << BLUE << "Splice to end() -> [begin(), --end())" << RESET << std::endl;
	sharedContainer1.splice(sharedContainer1.end(), ftContainer, ftContainer.begin(), --ftContainer.end());
	sharedContainer2.splice(sharedContainer2.end(), stdContainer, stdContainer.begin(), --stdContainer.end());
	printCmpIterator(ftContainer, stdContainer);
	printCmpIterator(sharedContainer1, sharedContainer2);
}

template<typename T, typename C>
void testRemove() {
	std::cout << RED << "Remove Function" << RESET << std::endl;

	std::cout << BLUE << "Fill Constructor" << RESET << std::endl;
	typename T::value_type randomValue = getRandomValue<T>();
	T ftContainer(static_cast<size_t>(countRandNumbers), randomValue);
	C stdContainer(static_cast<size_t>(countRandNumbers), randomValue);
	printCmpIterator(ftContainer, stdContainer);

	ftContainer.remove(randomValue);
	stdContainer.remove(randomValue);
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "PushBack Random" << RESET << std::endl;
	containerPushBack(ftContainer);
	stdContainer.assign(ftContainer.begin(), ftContainer.end());
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Remove last element" << RESET << std::endl;
	typename C::iterator it = --stdContainer.end();
	ftContainer.remove(*it);
	stdContainer.remove(*it);
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Remove number > 0" << RESET << std::endl;
	ftContainer.remove_if(isPositive);
	stdContainer.remove_if(isPositive);
	printCmpIterator(ftContainer, stdContainer);

}

template<typename T, typename C>
void testUnique() {
	std::cout << RED << "Unique Function" << RESET << std::endl;

	T ftContainer;
	C stdContainer;

	std::cout << BLUE << "Random Unique" << RESET << std::endl;
	for (size_t i = 0; i < countRandNumbers*5; i++)
		ftContainer.push_back(getRandomValue<T>());
	stdContainer.assign(ftContainer.begin(), ftContainer.end());
	printCmpIterator(ftContainer, stdContainer);
	ftContainer.unique();
	stdContainer.unique();
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Random Binary Unique" << RESET << std::endl;
	ftContainer.clear();
	for (size_t i = 0; i < countRandNumbers; i++)
		ftContainer.push_back(getRandomValue<T>());
	stdContainer.assign(ftContainer.begin(), ftContainer.end());
	printCmpIterator(ftContainer, stdContainer);
	ftContainer.unique(isGreater);
	stdContainer.unique(isGreater);
	printCmpIterator(ftContainer, stdContainer);
}

template<typename T, typename C>
void testMerge() {
	std::cout << RED << "Merge Function" << RESET << std::endl;

	T ftContainer;
	T ftContainerMerge;
	C stdContainer;
	C stdContainerMerge;

	std::cout << BLUE << "Merge Random not sorted(or sorted) values" << RESET << std::endl;
	containerPushBack(stdContainer);
	containerPushBack(stdContainerMerge);
	stdContainer.sort();
	stdContainerMerge.sort();
	ftContainer.assign(stdContainer.begin(), stdContainer.end());
	ftContainerMerge.assign(stdContainerMerge.begin(), stdContainerMerge.end());

	printCmpIterator(stdContainer, stdContainerMerge);
	stdContainer.merge(stdContainerMerge);

	ftContainer.merge(ftContainerMerge);
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Merge using predicate" << RESET << std::endl;
	ftContainer.clear();
	stdContainer.clear();
	containerPushBack(stdContainer);
	containerPushBack(stdContainerMerge);
	stdContainer.sort(isGreater);
	stdContainerMerge.sort(isGreater);
	ftContainer.assign(stdContainer.begin(), stdContainer.end());
	ftContainerMerge.assign(stdContainerMerge.begin(), stdContainerMerge.end());

	printCmpIterator(stdContainer, stdContainerMerge);
	stdContainer.merge(stdContainerMerge, isGreater);

	ftContainer.merge(ftContainerMerge, isGreater);
	printCmpIterator(ftContainer, stdContainer);
}

template<typename T, typename C>
void testSort() {
	std::cout << RED << "Sort Function" << RESET << std::endl;

	T ftContainer;
	containerPushBack(ftContainer);
	C stdContainer(ftContainer.begin(), ftContainer.end());

	std::cout << BLUE << "Simple Sort" << RESET << std::endl;
	std::cout << BLUE << "Before Sort" << RESET << std::endl;
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "After Sort" << RESET << std::endl;
	ftContainer.sort();
	stdContainer.sort();
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "Predicate Sort" << RESET << std::endl;
	ftContainer.sort(isGreater);
	stdContainer.sort(isGreater);
	printCmpIterator(ftContainer, stdContainer);
}

template<typename T, typename C>
void testReverse() {
	std::cout << BLUE << "Reverse function" << RESET << std::endl;

	T ftContainer;
	containerPushBack(ftContainer);
	C stdContainer(ftContainer.begin(), ftContainer.end());

	std::cout << BLUE << "Before reverse" << RESET << std::endl;
	printCmpIterator(ftContainer, stdContainer);

	std::cout << BLUE << "After reverse" << RESET << std::endl;
	ftContainer.reverse();
	stdContainer.reverse();
	printCmpIterator(ftContainer, stdContainer);
}

template<typename T, typename C>
void testOperators() {
	std::cout << RED << "Operators function" << RESET << std::endl;

	T ftContainer;
	containerPushBack(ftContainer);
	T ftContainerOperator(ftContainer);
	C stdContainer(ftContainer.begin(), ftContainer.end());

	printCmpIterator(ftContainer, ftContainerOperator);
	std::cout << BLUE << "Operator== -> " << (ftContainer == ftContainerOperator) << RESET << std::endl;
	std::cout << BLUE << "Operator< -> " << (ftContainer < ftContainerOperator) << RESET << std::endl;

	ftContainerOperator.clear();
	containerPushBack(ftContainerOperator);
	printCmpIterator(ftContainer, ftContainerOperator);
	std::cout << BLUE << "Operator== -> " << (ftContainer == ftContainerOperator) << RESET << std::endl;
	std::cout << BLUE << "Operator< -> " << (ftContainer < ftContainerOperator) << RESET << std::endl;


}

int main() {
	srand(time(NULL));

	std::cout << RED << "||||||||||LIST||||||||||" << RESET << std::endl;
	testConstructors<ft::list<cType>, std::list<cType> >();
	testIterators<ft::list<cType>, std::list<cType> >();
	testAssign<ft::list<cType>, std::list<cType> >();
	testPushFront<ft::list<cType>, std::list<cType> >();
	testPopFront<ft::list<cType>, std::list<cType> >();
	testInsert<ft::list<cType>, std::list<cType> >();
	testErase<ft::list<cType>, std::list<cType> >();
	testSwap<ft::list<cType>, ft::list<cType> >();
	testResize<ft::list<cType>, std::list<cType> >();
	testSplice<ft::list<cType>, std::list<cType> >();
	testRemove<ft::list<cType>, std::list<cType> >();
	testUnique<ft::list<cType>, std::list<cType> >();
	testMerge<ft::list<cType>, std::list<cType> >();
	testSort<ft::list<cType>, std::list<cType> >();
	testReverse<ft::list<cType>, std::list<cType> >();
	testOperators<ft::list<cType>, std::list<cType> >();

	std::cout << RED << "||||||||||VECTOR||||||||||" << RESET << std::endl;
	testConstructors<ft::vector<cType>, std::vector<cType> >();
	testIterators<ft::vector<cType>, std::vector<cType> >();
	testAssign<ft::vector<cType>, std::vector<cType> >();
	testInsert<ft::vector<cType>, std::vector<cType> >();
	testErase<ft::vector<cType>, std::vector<cType> >();
	testSwap<ft::vector<cType>, ft::vector<cType> >();
	testOperators<ft::vector<cType>, std::vector<cType> >();

/*	ft::stack<cType, ft::list<cType> > stack;
	stack.push((cType)(10));*/
//	ft::stack<cType, ft::list<cType> > stack2;
//	stack2.push((cType)(10));
//	std::cout << BLUE << "==" << (stack == stack2) << RESET << std::endl;
	ft::map<const int, int> map;
	// 1,2,3,-50,-27,-150,-56,-1950,-1890,-10
	map.insert(std::make_pair(1, 10));
	map.insert(std::make_pair(40, 25));
	map.insert(std::make_pair(100, 35));
	map.insert(std::make_pair(20, 35));
	map.insert(std::make_pair(-50, 9309203));
	map.insert(std::make_pair(-27, -1));
	map.insert(std::make_pair(-150, 1000));
	map.insert(std::make_pair(-56, 933));
	map.insert(std::make_pair(-1950, 3));
	map.insert(std::make_pair(-1890, 103));
	map.insert(std::make_pair(-10, 99203));

	printIteratorMap(map);
	map.erase(map.begin());
	printIteratorMap(map);

//	map.runInOrderTreeWalk();

	std::map<int, int> stdMap;
	stdMap.insert(std::make_pair(1, 10));
	stdMap.insert(std::make_pair(40, 25));
	stdMap.insert(std::make_pair(100, 35));
	stdMap.insert(std::make_pair(20, 35));
	stdMap.insert(std::make_pair(-50, 9309203));
	stdMap.insert(std::make_pair(-27, -1));
	stdMap.insert(std::make_pair(-150, 1000));
	stdMap.insert(std::make_pair(-56, 933));
	stdMap.insert(std::make_pair(-1950, 3));
	stdMap.insert(std::make_pair(-1890, 103));
	stdMap.insert(std::make_pair(-10, 99203));
	printIteratorMap(stdMap);
	return (0);
}
