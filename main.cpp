#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include "list.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

#define RED		"\033[31m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

const	int countRandNumbers = 3;
const	int printMargin = 45;
typedef int cType;

template<typename T>
void printIterator(T& container) {
	size_t i = 0;
	std::cout << BLUE << "printIterator" << RESET << std::endl;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << "container[" << i++ << "] = " << *it << std::endl;
}

template<typename T, typename C>
void printCmpIterator(T& mainContainer, C& alterContainer) {
	size_t i = 0;
	if (mainContainer.size() != alterContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}
	typename T::iterator mainIt = mainContainer.begin();
	typename C::iterator alterIt = alterContainer.begin();

	std::cout << BLUE << "printCmpIterator" << RESET << std::endl;
	for ( ; mainIt != mainContainer.end(); mainIt++, alterIt++, i++) {
		std::cout << "mainContainer[" << i << "] = " << *mainIt;
		std::cout << "\t\t";
		std::cout << "alterContainer[" << i << "] = " << *alterIt << std::endl;
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
void printCmpRevIterator(T& mainContainer, C& alterContainer) {
	size_t i = 0;

	if (mainContainer.size() != alterContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}

	typename T::reverse_iterator mainIt = mainContainer.rbegin();
	typename C::reverse_iterator alterIt = alterContainer.rbegin();

	std::cout << BLUE << "printCmpRevIterator" << RESET << std::endl;
	for ( ; mainIt != mainContainer.rend(); mainIt++, alterIt++, i++) {
		std::stringstream stringStream;
		stringStream << "mainContainer[" << i << "] = " << *mainIt;
		std::cout << std::setw(printMargin) << std::left << stringStream.str();
		std::cout << "alterContainer[" << i << "] = " << *alterIt << std::endl;
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

template<typename T>
T getRandomValueByType() {
	int intMin = -500, intMax = 500;
	float floatMin = -500.0, floatMax = 500.0;
	for (size_t i = 0; i < countRandNumbers; i++) {
		if (typeid(T) == typeid(int))
			return (rand() % (intMax - intMin) + intMin);
		else if (typeid(T) == typeid(float) || typeid(T) == typeid(double))
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

template <class T>
struct small: std::binary_function <T,T,bool> {
	bool operator() (const T& x, const T& y) const {
		return (y<x);
	}
};

template <class T>
struct greater: std::binary_function <T,T,bool> {
	bool operator() (const T& x, const T& y) const {
		return (x<y);
	}
};

template<typename T, typename C>
void testConstructors() {
	std::cout << RED << "Constructors" << RESET << std::endl;

	T mainContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());
	C alterContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());

	std::cout << BLUE << "Fill Constructor (5, rand<T>())" << RESET << std::endl;
	printCmpIterator(mainContainerFill, alterContainerFill);

	std::cout << BLUE << "Range Constructor" << RESET << std::endl;
	T mainContainerRange(mainContainerFill.begin(), mainContainerFill.end());
	C alterContainerRange(alterContainerFill.begin(), alterContainerFill.end());
	printCmpIterator(mainContainerRange, alterContainerRange);

	std::cout << BLUE << "Copy Constructor" << RESET << std::endl;
	T mainContainerCopy(mainContainerRange);
	C alterContainerCopy(alterContainerRange);
	printCmpIterator(mainContainerCopy, alterContainerCopy);
}

template<typename T, typename C>
void testIterators() {
	std::cout << RED << "Iterators" << RESET << std::endl;

	T mainContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());
	C alterContainerFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());

	std::cout << BLUE << "Fill Constructor (5, rand<T>())" << RESET << std::endl;
	printCmpIterator(mainContainerFill, alterContainerFill);
	printCmpRevIterator(mainContainerFill, alterContainerFill);
}

template<typename T, typename C>
void testAssign() {
	std::cout << RED << "Assign function" << RESET << std::endl;

	T mainContainer;
	C alterContainer;

	containerPushBack(alterContainer);
	mainContainer.assign(alterContainer.begin(), alterContainer.end());
	printCmpIterator(mainContainer, alterContainer);

	T mainContainer2;
	mainContainer2.assign(11, (typename T::size_type)10);
	C alterContainer2;
	alterContainer2.assign(11,(typename C::size_type)10);
	printCmpIterator(mainContainer2, alterContainer2);
}

template<typename T, typename C>
void testPushFront() {
	std::cout << RED << "PushFront function" << RESET << std::endl;

	T mainContainer;
	C alterContainer;

	while (mainContainer.size() != countRandNumbers) {
		typename T::value_type randomValue = getRandomValue<T>();
		mainContainer.push_front(randomValue);
		alterContainer.push_front(randomValue);
		printCmpIterator(mainContainer, alterContainer);
	}
}

template<typename T, typename C>
void testPopFront()
{
	T mainContainer;
	containerPushBack(mainContainer);

	C alterContainer(mainContainer.begin(), mainContainer.end());

	if (mainContainer.size() != alterContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}

	std::cout << RED << "PopFront function" << RESET << std::endl;
	while (!mainContainer.empty()) {
		printCmpIterator(mainContainer, alterContainer);
		mainContainer.pop_front();
		alterContainer.pop_front();
	}
}

template<typename T, typename C>
void testInsert() {
	std::cout << RED << "Insert function" << RESET << std::endl;

	T mainContainer;
	typename T::iterator ftIt;

	C alterContainer(mainContainer.begin(), mainContainer.end());
	typename C::iterator stdIt;

	typename T::value_type randomValue = getRandomValue<T>();
	typename T::size_type randomTimes = (abs(getRandomValue<T>()))%4 + 1;
	std::cout << BLUE << "Insert " << randomValue << " in begin()" << RESET << std::endl;
	ftIt = mainContainer.insert(mainContainer.begin(), randomValue);
	stdIt = alterContainer.insert(alterContainer.begin(), randomValue);
	printCmpIterator(mainContainer, alterContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
	ftIt = mainContainer.insert(mainContainer.end(), randomValue);
	stdIt = alterContainer.insert(alterContainer.end(), randomValue);
	printCmpIterator(mainContainer, alterContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
	ftIt = mainContainer.insert(mainContainer.end(), randomValue);
	stdIt = alterContainer.insert(alterContainer.end(), randomValue);
	printCmpIterator(mainContainer, alterContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in begin() " << randomTimes << " times" << RESET << std::endl;
	mainContainer.insert(mainContainer.begin(), randomTimes, randomValue);
	alterContainer.insert(alterContainer.begin(), randomTimes, randomValue);
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Insert previous array in begin()" << RESET << std::endl;
	T mainContainerCopy(mainContainer);
	C alterContainerCopy(alterContainer);
	mainContainerCopy.insert(mainContainerCopy.begin(), mainContainer.begin(), mainContainer.end());
	alterContainerCopy.insert(alterContainerCopy.begin(), alterContainer.begin(), alterContainer.end());
	printCmpIterator(mainContainerCopy, alterContainerCopy);
}

template<typename T, typename C>
void testErase() {
	std::cout << RED << "Erase function" << RESET << std::endl;

	T mainContainer;
	containerPushBack(mainContainer);
	C alterContainer(mainContainer.begin(), mainContainer.end());
	printCmpIterator(mainContainer, alterContainer);

	typename T::iterator ftIt;
	typename C::iterator stdIt;

	std::cout << BLUE << "testErase begin()" << RESET << std::endl;
	ftIt = mainContainer.erase(mainContainer.begin());
	stdIt = alterContainer.erase(alterContainer.begin());
	printCmpIterator(mainContainer, alterContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	std::cout << BLUE << "testErase [begin(), end() - 1)" << RESET << std::endl;
	ftIt = mainContainer.erase(mainContainer.begin(), --mainContainer.end());
	stdIt = alterContainer.erase(alterContainer.begin(), --alterContainer.end());
	printCmpIterator(mainContainer, alterContainer);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	std::cout << BLUE << "After Erase" << RESET << std::endl;
	printCmpIterator(mainContainer, alterContainer);
}

template<typename T, typename C>
void testSwap() {
	std::cout << RED << "Swap function" << RESET << std::endl;

	T mainContainer;
	containerPushBack(mainContainer);
	C alterContainer;
	containerPushBack(alterContainer);

	if (mainContainer.size() != alterContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}

	std::cout << RED << "Before Swap" << RESET << std::endl;
	printCmpIterator(mainContainer, alterContainer);
	mainContainer.swap(alterContainer);
	std::cout << RED << "After Swap" << RESET << std::endl;
	printCmpIterator(mainContainer, alterContainer);
}

template<typename T, typename C>
void testResize() {
	std::cout << RED << "Resize function" << RESET << std::endl;

	T mainContainer;
	containerPushBack(mainContainer);
	C alterContainer(mainContainer.begin(), mainContainer.end());
	printCmpIterator(mainContainer, alterContainer);


	std::cout << BLUE << "Resize(5)" << RESET << std::endl;
	mainContainer.resize(5);
	alterContainer.resize(5);
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Resize(8, 100)" << RESET << std::endl;
	mainContainer.resize(8, 100);
	alterContainer.resize(8, 100);
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Resize(12)" << RESET << std::endl;
	mainContainer.resize(12);
	alterContainer.resize(12);
	printCmpIterator(mainContainer, alterContainer);
}

template<typename T, typename C>
void testSplice() {
	std::cout << RED << "Splice function" << RESET << std::endl;

	T sharedContainer1;
	containerPushBack(sharedContainer1);
	C sharedContainer2(sharedContainer1.begin(), sharedContainer1.end());

	T mainContainer;
	C alterContainer;
	printIterator(sharedContainer1);

	std::cout << BLUE << "Splice begin()" << RESET << std::endl;
	mainContainer.splice(mainContainer.begin(), sharedContainer1);
	alterContainer.splice(alterContainer.begin(), sharedContainer2);
	printCmpIterator(mainContainer, alterContainer);
	printCmpIterator(sharedContainer1, sharedContainer2);

	std::cout << BLUE << "Splice second element" << RESET << std::endl;
	sharedContainer1.splice(sharedContainer1.begin(), mainContainer, ++mainContainer.begin());
	sharedContainer2.splice(sharedContainer2.begin(), alterContainer, ++alterContainer.begin());
	printCmpIterator(mainContainer, alterContainer);
	printCmpIterator(sharedContainer1, sharedContainer2);

	std::cout << BLUE << "Splice to end() -> [begin(), --end())" << RESET << std::endl;
	sharedContainer1.splice(sharedContainer1.end(), mainContainer, mainContainer.begin(), --mainContainer.end());
	sharedContainer2.splice(sharedContainer2.end(), alterContainer, alterContainer.begin(), --alterContainer.end());
	printCmpIterator(mainContainer, alterContainer);
	printCmpIterator(sharedContainer1, sharedContainer2);
}

template<typename T, typename C>
void testRemove() {
	std::cout << RED << "Remove Function" << RESET << std::endl;

	std::cout << BLUE << "Fill Constructor" << RESET << std::endl;
	typename T::value_type randomValue = getRandomValue<T>();
	T mainContainer(static_cast<size_t>(countRandNumbers), randomValue);
	C alterContainer(static_cast<size_t>(countRandNumbers), randomValue);
	printCmpIterator(mainContainer, alterContainer);

	mainContainer.remove(randomValue);
	alterContainer.remove(randomValue);
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "PushBack Random" << RESET << std::endl;
	containerPushBack(mainContainer);
	alterContainer.assign(mainContainer.begin(), mainContainer.end());
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Remove last element" << RESET << std::endl;
	typename C::iterator it = --alterContainer.end();
	mainContainer.remove(*it);
	alterContainer.remove(*it);
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Remove number > 0" << RESET << std::endl;
	mainContainer.remove_if(isPositive);
	alterContainer.remove_if(isPositive);
	printCmpIterator(mainContainer, alterContainer);

}

template<typename T, typename C>
void testUnique() {
	std::cout << RED << "Unique Function" << RESET << std::endl;

	T mainContainer;
	C alterContainer;

	std::cout << BLUE << "Random Unique" << RESET << std::endl;
	for (size_t i = 0; i < countRandNumbers*5; i++)
		mainContainer.push_back(getRandomValue<T>());
	alterContainer.assign(mainContainer.begin(), mainContainer.end());
	printCmpIterator(mainContainer, alterContainer);
	mainContainer.unique();
	alterContainer.unique();
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Random Binary Unique" << RESET << std::endl;
	mainContainer.clear();
	for (size_t i = 0; i < countRandNumbers; i++)
		mainContainer.push_back(getRandomValue<T>());
	alterContainer.assign(mainContainer.begin(), mainContainer.end());
	printCmpIterator(mainContainer, alterContainer);
	mainContainer.unique(isGreater);
	alterContainer.unique(isGreater);
	printCmpIterator(mainContainer, alterContainer);
}

template<typename T, typename C>
void testMerge() {
	std::cout << RED << "Merge Function" << RESET << std::endl;

	T mainContainer;
	T mainContainerMerge;
	C alterContainer;
	C alterContainerMerge;

	std::cout << BLUE << "Merge Random not sorted(or sorted) values" << RESET << std::endl;
	containerPushBack(alterContainer);
	containerPushBack(alterContainerMerge);
	alterContainer.sort();
	alterContainerMerge.sort();
	mainContainer.assign(alterContainer.begin(), alterContainer.end());
	mainContainerMerge.assign(alterContainerMerge.begin(), alterContainerMerge.end());

	printCmpIterator(alterContainer, alterContainerMerge);
	alterContainer.merge(alterContainerMerge);

	mainContainer.merge(mainContainerMerge);
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Merge using predicate" << RESET << std::endl;
	mainContainer.clear();
	alterContainer.clear();
	containerPushBack(alterContainer);
	containerPushBack(alterContainerMerge);
	alterContainer.sort(isGreater);
	alterContainerMerge.sort(isGreater);
	mainContainer.assign(alterContainer.begin(), alterContainer.end());
	mainContainerMerge.assign(alterContainerMerge.begin(), alterContainerMerge.end());

	printCmpIterator(alterContainer, alterContainerMerge);
	alterContainer.merge(alterContainerMerge, isGreater);

	mainContainer.merge(mainContainerMerge, isGreater);
	printCmpIterator(mainContainer, alterContainer);
}

template<typename T, typename C>
void testSort() {
	std::cout << RED << "Sort Function" << RESET << std::endl;

	T mainContainer;
	containerPushBack(mainContainer);
	C alterContainer(mainContainer.begin(), mainContainer.end());

	std::cout << BLUE << "Simple Sort" << RESET << std::endl;
	std::cout << BLUE << "Before Sort" << RESET << std::endl;
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "After Sort" << RESET << std::endl;
	mainContainer.sort();
	alterContainer.sort();
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "Predicate Sort" << RESET << std::endl;
	mainContainer.sort(isGreater);
	alterContainer.sort(isGreater);
	printCmpIterator(mainContainer, alterContainer);
}

template<typename T, typename C>
void testReverse() {
	std::cout << BLUE << "Reverse function" << RESET << std::endl;

	T mainContainer;
	containerPushBack(mainContainer);
	C alterContainer(mainContainer.begin(), mainContainer.end());

	std::cout << BLUE << "Before reverse" << RESET << std::endl;
	printCmpIterator(mainContainer, alterContainer);

	std::cout << BLUE << "After reverse" << RESET << std::endl;
	mainContainer.reverse();
	alterContainer.reverse();
	printCmpIterator(mainContainer, alterContainer);
}

template<typename T, typename C>
void testOperators() {
	std::cout << RED << "Operators function" << RESET << std::endl;

	T mainContainer;
	containerPushBack(mainContainer);
	T mainContainerOperator(mainContainer);
	C alterContainer(mainContainer.begin(), mainContainer.end());

	printCmpIterator(mainContainer, mainContainerOperator);
	std::cout << BLUE << "Operator== -> " << (mainContainer == mainContainerOperator) << RESET << std::endl;
	std::cout << BLUE << "Operator< -> " << (mainContainer < mainContainerOperator) << RESET << std::endl;

	mainContainerOperator.clear();
	containerPushBack(mainContainerOperator);
	printCmpIterator(mainContainer, mainContainerOperator);
	std::cout << BLUE << "Operator== -> " << (mainContainer == mainContainerOperator) << RESET << std::endl;
	std::cout << BLUE << "Operator< -> " << (mainContainer < mainContainerOperator) << RESET << std::endl;


}

// Map

template<typename T>
void printIteratorMap(T& container) {
	size_t i = 0;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << "container[" << i++ << "] = (" << (*it).first << ", " << (*it).second << ")" << std::endl;
}

template<typename T>
void printRevIteratorMap(T& container) {
	size_t i = 0;
	for (typename T::iterator it = container.rbegin(); it != container.rend(); it++)
		std::cout << "container[" << i++ << "] = (" << (*it).first << ", " << (*it).second << ")" << std::endl;
}

template<typename T, typename C>
void printCmpIteratorMap(T& mainContainer, C& alterContainer) {
	std::cout << BLUE << "ForwardIterator" << RESET << std::endl;
	size_t i = 0;

	if (mainContainer.size() != alterContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}
	typename T::iterator mainIt = mainContainer.begin();
	typename C::iterator alterIt = alterContainer.begin();

	for ( ; mainIt != mainContainer.end(); mainIt++, alterIt++, i++) {
		std::stringstream stringStream;
		stringStream << "mainContainer[" << i << "] = (" << (*mainIt).first << ", " << (*mainIt).second << ")";
		std::cout << std::setw(printMargin) << std::left << stringStream.str();
		std::cout << "alterContainer[" << i << "] = (" << (*alterIt).first << ", " << (*alterIt).second << ")" << std::endl;
	}
}

template<typename T, typename C>
void printCmpRevIteratorMap(T& mainContainer, C& alterContainer) {
	std::cout << BLUE << "ReverseIterator" << RESET << std::endl;
	size_t i = 0;

	if (mainContainer.size() != alterContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}
	typename T::reverse_iterator mainIt = mainContainer.rbegin();
	typename C::reverse_iterator alterIt = alterContainer.rbegin();

	for ( ; mainIt != mainContainer.rend(); mainIt++, alterIt++, i++) {
		std::stringstream stringStream;
		stringStream << "mainContainer[" << i << "] = (" << (*mainIt).first << ", " << (*mainIt).second << ")";
		std::cout << std::setw(printMargin) << std::left << stringStream.str();
		std::cout << "alterContainer[" << i << "] = (" << (*alterIt).first << ", " << (*alterIt).second << ")" << std::endl;
	}
}

template<typename T, typename C>
void testMapConstructors() {
	std::cout << RED << "Constructors" << RESET << std::endl;

	std::cout << BLUE << "Fill (rand<T>(), rand<T>())" << RESET << std::endl;
	T mainContainerFill;
	C alterContainerFill;

	for (size_t i = 0; i < countRandNumbers; i++) {
		typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
		typename T::mapped_type mappedTmp = getRandomValueByType<typename T::mapped_type>();
		mainContainerFill.insert(std::make_pair(keyTmp, mappedTmp));
		alterContainerFill.insert(std::make_pair(keyTmp, mappedTmp));
	}
	printCmpIteratorMap(mainContainerFill, alterContainerFill);

	std::cout << BLUE << "Iterator constructor" << RESET << std::endl;
	T mainContainerIt(mainContainerFill.begin(), mainContainerFill.end());
	C alterContainerIt(alterContainerFill.begin(), alterContainerFill.end());
	printCmpIteratorMap(mainContainerIt, alterContainerIt);

	std::cout << BLUE << "Copy constructor" << RESET << std::endl;
	T mainContainerCopy(mainContainerIt);
	C alterContainerCopy(alterContainerIt);
	printCmpIteratorMap(mainContainerCopy, alterContainerCopy);

}

template<typename T, typename C>
void testMapIterators() {
	std::cout << RED << "Iterators" << RESET << std::endl;

	std::cout << BLUE << "Fill (rand<T>(), rand<T>())" << RESET << std::endl;
	T mainContainerFill;
	C alterContainerFill;

	for (size_t i = 0; i < countRandNumbers; i++) {
		typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
		typename T::mapped_type mappedTmp = getRandomValueByType<typename T::mapped_type>();
		mainContainerFill.insert(std::make_pair(keyTmp, mappedTmp));
		alterContainerFill.insert(std::make_pair(keyTmp, mappedTmp));
	}
	printCmpIteratorMap(mainContainerFill, alterContainerFill);
	printCmpRevIteratorMap(mainContainerFill, alterContainerFill);

}

template<typename T, typename C>
void testMapInsert() {
	std::cout << RED << "Insert function" << RESET << std::endl;

	std::cout << BLUE << "Insert pair(rand<T>(), rand<T>())" << RESET << std::endl;
	T mainContainer;
	C alterContainer;

	for (size_t i = 0; i < countRandNumbers; i++) {
		typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
		typename T::mapped_type mappedTmp = getRandomValueByType<typename T::mapped_type>();
		mainContainer.insert(std::make_pair(keyTmp, mappedTmp));
		alterContainer.insert(std::make_pair(keyTmp, mappedTmp));
	}
	printCmpIteratorMap(mainContainer, alterContainer);

	std::cout << BLUE << "Insert end(rand<T>(), rand<T>())" << RESET << std::endl;
	typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
	typename T::mapped_type mappedTmp = getRandomValueByType<typename T::mapped_type>();
	mainContainer.insert(mainContainer.end(), std::make_pair(keyTmp, mappedTmp));
	alterContainer.insert(alterContainer.end(), std::make_pair(keyTmp, mappedTmp));

	printCmpIteratorMap(mainContainer, alterContainer);
}

void testList() {
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
}

void testVector() {
	std::cout << RED << "||||||||||VECTOR||||||||||" << RESET << std::endl;
	testConstructors<ft::vector<cType>, std::vector<cType> >();
	testIterators<ft::vector<cType>, std::vector<cType> >();
	testAssign<ft::vector<cType>, std::vector<cType> >();
	testInsert<ft::vector<cType>, std::vector<cType> >();
	testErase<ft::vector<cType>, std::vector<cType> >();
	testSwap<ft::vector<cType>, ft::vector<cType> >();
	testOperators<ft::vector<cType>, std::vector<cType> >();
}

void testMap() {
	testMapConstructors<ft::map<const int, int, greater<int> >, std::map<const int, int, greater<int> > >();
//	testMapConstructors<ft::map<int, int>, std::map<int, int> >();
	testMapIterators<ft::map<const int, int>, std::map<const int, int> >();
	testMapInsert<ft::map<const int, int>, std::map<const int, int> >();

}

int main() {
	srand(time(NULL));

//	testList();
//	testVector();
	testMap();

	return (0);
}
