#include <iostream>
#include <typeinfo>
#include <list>
#include <cstdlib>
#include "list.hpp"
#include "iterator.hpp"

#define RED		"\033[31m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

const	int countRandNumbers = 3;
typedef int cType;

template<typename T>
void printIterator(T& container) {
	size_t i = 0;
	std::cout << BLUE << "printIterator" << RESET << std::endl;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << "container[" << i++ << "] = " << *it << std::endl;
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

	T ftListFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());
	C stdListFill(static_cast<size_t>(countRandNumbers), getRandomValue<T>());

	std::cout << BLUE << "Fill Constructor (5, rand<T>())" << RESET << std::endl;
	printCmpIterator(ftListFill, stdListFill);

	std::cout << BLUE << "Range Constructor" << RESET << std::endl;
	T ftListRange(ftListFill.begin(), ftListFill.end());
	C stdListRange(stdListFill.begin(), stdListFill.end());
	printCmpIterator(ftListRange, stdListRange);

	std::cout << BLUE << "Copy Constructor" << RESET << std::endl;
	T ftListCopy(ftListRange);
	C stdListCopy(stdListRange);
	printCmpIterator(ftListCopy, stdListCopy);

}

template<typename T, typename C>
void testAssign() {
	std::cout << RED << "Assign function" << RESET << std::endl;

	T ftList;
	C stdList;

	containerPushBack(stdList);
	ftList.assign(stdList.begin(), stdList.end());
	printCmpIterator(ftList, stdList);
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

	T ftList;
	typename T::iterator ftIt;

	C stdList(ftList.begin(), ftList.end());
	typename C::iterator stdIt;

	typename T::value_type randomValue = getRandomValue<T>();
	typename T::size_type randomTimes = (abs(getRandomValue<T>()))%4 + 1;
	std::cout << BLUE << "Insert " << randomValue << " in begin()" << RESET << std::endl;
	ftIt = ftList.insert(ftList.begin(), randomValue);
	stdIt = stdList.insert(stdList.begin(), randomValue);
	printCmpIterator(ftList, stdList);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
	ftIt = ftList.insert(ftList.end(), randomValue);
	stdIt = stdList.insert(stdList.end(), randomValue);
	printCmpIterator(ftList, stdList);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
	ftIt = ftList.insert(ftList.end(), randomValue);
	stdIt = stdList.insert(stdList.end(), randomValue);
	printCmpIterator(ftList, stdList);
	std::cout << BLUE << "Compare returning value" << RESET << std::endl;
	std::cout << "ftIt = " << *ftIt << "\t\tstdIt = " << *stdIt << std::endl;

	randomValue = getRandomValue<T>();
	std::cout << BLUE << "Insert " << randomValue << " in begin() " << randomTimes << " times" << RESET << std::endl;
	ftList.insert(ftList.begin(), randomTimes, randomValue);
	stdList.insert(stdList.begin(), randomTimes, randomValue);
	printCmpIterator(ftList, stdList);

	std::cout << BLUE << "Insert previous array in begin()" << RESET << std::endl;
	ftList.insert(ftList.begin(), ftList.begin(), ftList.end());
	stdList.insert(stdList.begin(), stdList.begin(), stdList.end());
	printCmpIterator(ftList, stdList);
}

template<typename T, typename C>
void testErase() {
	std::cout << RED << "Erase function" << RESET << std::endl;

	T ftContainer;
	containerPushBack(ftContainer);
	C stdContainer(ftContainer.begin(), ftContainer.end());

	if (ftContainer.size() != stdContainer.size()) {
		std::cerr << "Container diff size" << std::endl;
		return;
	}

	std::cout << RED << "testErase [begin(), end())" << RESET << std::endl;
	printCmpIterator(ftContainer, stdContainer);
	ftContainer.erase(ftContainer.begin(), ftContainer.end());
	stdContainer.erase(stdContainer.begin(), stdContainer.end());
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

	testConstructors<ft::list<cType>, std::list<cType> >();
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

	return (0);
}
