#ifndef MAINTEST_HPP
#define MAINTEST_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <set>

#include "utils.hpp"
#include "print.hpp"
#include "defines.hpp"

namespace ft {

	template<typename T>
	void containerPushBack(T& container) {
		for (size_t i = 0; i < g_countRandNumbers; i++) {
			if (typeid(typename T::value_type) == typeid(int))
				container.push_back(rand() % (g_intMax - g_intMin) + g_intMin);
			else if (typeid(typename T::value_type) == typeid(float) || typeid(typename T::value_type) == typeid(double)) {
				double scale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				container.push_back(scale * (g_floatMax - g_floatMin) + g_floatMin);
			}
		}
	}

	template<typename T>
	typename T::value_type getRandomValue() {
		for (size_t i = 0; i < g_countRandNumbers; i++) {
			if (typeid(typename T::value_type) == typeid(int))
				return (rand() % (g_intMax - g_intMin) + g_intMin);
			else if (typeid(typename T::value_type) == typeid(float) || typeid(typename T::value_type) == typeid(double)) {
				double scale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				return (scale * (g_floatMax - g_floatMin) + g_floatMin);
			}
		}
		return (0);
	}

	template<typename T>
	T getRandomValueByType() {
		for (size_t i = 0; i < g_countRandNumbers; i++) {
			if (typeid(T) == typeid(int))
				return (rand() % (g_intMax - g_intMin) + g_intMin);
			else if (typeid(T) == typeid(float) || typeid(T) == typeid(double)) {
				double scale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				return (scale * (g_floatMax - g_floatMin) + g_floatMin);
			}
		}
		return (0);
	}

	template<typename T, typename C>
	void testConstructors() {
		std::cout << RED << "Constructors" << RESET << std::endl;

		T mainContainerFill(g_countRandNumbers, getRandomValue<T>());
		C alterContainerFill(g_countRandNumbers, getRandomValue<T>());

		std::cout << BLUE << "Fill Constructor (" << g_countRandNumbers << ", rand<T>())" << RESET << std::endl;
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

		T mainContainer;
		containerPushBack(mainContainer);

		C alterContainer(mainContainer.begin(), mainContainer.end());

		std::cout << BLUE << "Random Constructor" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
		printCmpRevIterator(mainContainer, alterContainer);
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
		C alterContainer2;

		mainContainer2.assign(11, (typename T::size_type)10);
		alterContainer2.assign(11,(typename C::size_type)10);
		printCmpIterator(mainContainer2, alterContainer2);
	}

	template<typename T, typename C>
	void testPushFront() {
		std::cout << RED << "PushFront function" << RESET << std::endl;

		T mainContainer;
		C alterContainer;

		while (mainContainer.size() != g_countRandNumbers) {
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
		typename T::iterator mainIt;

		C alterContainer;
		typename C::iterator alterIt;

		typename T::value_type randomValue = getRandomValue<T>();
		typename T::size_type randomTimes = getRandomValueByType<int>()%4 + 1;
		std::cout << BLUE << "Insert " << randomValue << " in begin()" << RESET << std::endl;
		mainIt = mainContainer.insert(mainContainer.begin(), randomValue);
		alterIt = alterContainer.insert(alterContainer.begin(), randomValue);
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Compare returning value" << RESET << std::endl;
		std::cout << "mainIt = " << *mainIt << "\t\talterIt = " << *alterIt << std::endl;

		randomValue = getRandomValue<T>();
		std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
		mainIt = mainContainer.insert(mainContainer.end(), randomValue);
		alterIt = alterContainer.insert(alterContainer.end(), randomValue);
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Compare returning value" << RESET << std::endl;
		std::cout << "mainIt = " << *mainIt << "\t\talterIt = " << *alterIt << std::endl;

		randomValue = getRandomValue<T>();
		std::cout << BLUE << "Insert " << randomValue << " in end()" << RESET << std::endl;
		mainIt = mainContainer.insert(mainContainer.end(), randomValue);
		alterIt = alterContainer.insert(alterContainer.end(), randomValue);
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Compare returning value" << RESET << std::endl;
		std::cout << "mainIt = " << *mainIt << "\t\talterIt = " << *alterIt << std::endl;

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

		typename T::iterator mainIt;
		typename C::iterator alterIt;

		std::cout << BLUE << "Erase begin()" << RESET << std::endl;
		mainIt = mainContainer.erase(mainContainer.begin());
		alterIt = alterContainer.erase(alterContainer.begin());
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Compare returning value" << RESET << std::endl;
		if (mainIt != mainContainer.end() && alterIt != alterContainer.end())
			std::cout << "mainIt = " << *mainIt << "\t\talterIt = " << *alterIt << std::endl;

		std::cout << BLUE << "Erase [begin(), end() - 1)" << RESET << std::endl;
		mainIt = mainContainer.erase(mainContainer.begin(), --mainContainer.end());
		alterIt = alterContainer.erase(alterContainer.begin(), --alterContainer.end());
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Compare returning value" << RESET << std::endl;
		if (mainIt != mainContainer.end() && alterIt != alterContainer.end())
			std::cout << "mainIt = " << *mainIt << "\t\talterIt = " << *alterIt << std::endl;

		std::cout << BLUE << "Erase last element" << RESET << std::endl;
		mainIt = mainContainer.erase(mainContainer.begin(), mainContainer.end());
		alterIt = alterContainer.erase(alterContainer.begin(), alterContainer.end());
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Compare returning value" << RESET << std::endl;
		if (mainIt != mainContainer.end() && alterIt != alterContainer.end())
			std::cout << "mainIt = " << *mainIt << "\t\talterIt = " << *alterIt << std::endl;
	}

	template<typename T, typename C>
	void testSwap() {
		std::cout << RED << "Swap function" << RESET << std::endl;

		T mainContainer;
		containerPushBack(mainContainer);
		C alterContainer;
		containerPushBack(alterContainer);

		std::cout << BLUE << "Before Swap" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
		mainContainer.swap(alterContainer);
		std::cout << BLUE << "After Swap" << RESET << std::endl;
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
		std::cout << BLUE << "Shared containers" << RESET << std::endl;
		printCmpIterator(sharedContainer1, sharedContainer2);

		T mainContainer;
		C alterContainer;

		std::cout << BLUE << "Splice begin()" << RESET << std::endl;
		mainContainer.splice(mainContainer.begin(), sharedContainer1);
		alterContainer.splice(alterContainer.begin(), sharedContainer2);
		std::cout << BLUE << "Main and alter containers" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Shared containers" << RESET << std::endl;
		printCmpIterator(sharedContainer1, sharedContainer2);

		std::cout << BLUE << "Splice second element" << RESET << std::endl;
		sharedContainer1.splice(sharedContainer1.begin(), mainContainer, ++mainContainer.begin());
		sharedContainer2.splice(sharedContainer2.begin(), alterContainer, ++alterContainer.begin());
		std::cout << BLUE << "Main and alter containers" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Shared containers" << RESET << std::endl;
		printCmpIterator(sharedContainer1, sharedContainer2);

		std::cout << BLUE << "Splice to end() -> [begin(), --end())" << RESET << std::endl;
		sharedContainer1.splice(sharedContainer1.end(), mainContainer, mainContainer.begin(), --mainContainer.end());
		sharedContainer2.splice(sharedContainer2.end(), alterContainer, alterContainer.begin(), --alterContainer.end());
		std::cout << BLUE << "Main and alter containers" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
		std::cout << BLUE << "Shared containers" << RESET << std::endl;
		printCmpIterator(sharedContainer1, sharedContainer2);
	}

	template<typename T, typename C>
	void testRemove() {
		std::cout << RED << "Remove Function" << RESET << std::endl;

		std::cout << BLUE << "Fill Constructor" << RESET << std::endl;
		typename T::value_type randomValue = getRandomValue<T>();
		T mainContainer(g_countRandNumbers, randomValue);
		C alterContainer(g_countRandNumbers, randomValue);
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
		mainContainer.remove_if(isPositive<typename T::value_type>);
		alterContainer.remove_if(isPositive<typename T::value_type>);
		printCmpIterator(mainContainer, alterContainer);

	}

	template<typename T, typename C>
	void testUnique() {
		std::cout << RED << "Unique Function" << RESET << std::endl;

		T mainContainer;
		C alterContainer;

		std::cout << BLUE << "Random Unique" << RESET << std::endl;
		for (size_t i = 0; i < g_countRandNumbers * 5; i++)
			mainContainer.push_back(getRandomValue<T>());
		alterContainer.assign(mainContainer.begin(), mainContainer.end());
		std::cout << BLUE << "Before unique" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
		mainContainer.unique();
		alterContainer.unique();
		std::cout << BLUE << "After unique" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);

		std::cout << BLUE << "Random Binary Unique" << RESET << std::endl;
		mainContainer.clear();
		for (size_t i = 0; i < g_countRandNumbers*5; i++)
			mainContainer.push_back(getRandomValue<T>());
		alterContainer.assign(mainContainer.begin(), mainContainer.end());
		std::cout << BLUE << "Before unique" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
		mainContainer.unique(isGreater<typename T::value_type>);
		alterContainer.unique(isGreater<typename T::value_type>);
		std::cout << BLUE << "After unique" << RESET << std::endl;
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

		std::cout << BLUE << "Alter containers" << RESET << std::endl;
		printCmpIterator(alterContainer, alterContainerMerge);

		alterContainer.merge(alterContainerMerge);
		mainContainer.merge(mainContainerMerge);
		std::cout << BLUE << "Main and alter containers" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);

		std::cout << BLUE << "Merge using predicate" << RESET << std::endl;
		mainContainer.clear();
		alterContainer.clear();
		containerPushBack(alterContainer);
		containerPushBack(alterContainerMerge);
		alterContainer.sort(isGreater<typename T::value_type>);
		alterContainerMerge.sort(isGreater<typename T::value_type>);
		mainContainer.assign(alterContainer.begin(), alterContainer.end());
		mainContainerMerge.assign(alterContainerMerge.begin(), alterContainerMerge.end());

		std::cout << BLUE << "Alter containers" << RESET << std::endl;
		printCmpIterator(alterContainer, alterContainerMerge);
		alterContainer.merge(alterContainerMerge, isGreater<typename T::value_type>);

		std::cout << BLUE << "Main and alter containers" << RESET << std::endl;
		mainContainer.merge(mainContainerMerge, isGreater<typename T::value_type>);
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
		mainContainer.sort(isGreater<typename T::value_type>);
		alterContainer.sort(isGreater<typename T::value_type>);
		printCmpIterator(mainContainer, alterContainer);
	}

	template<typename T, typename C>
	void testReverse() {
		std::cout << RED << "Reverse function" << RESET << std::endl;

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

		T mainContainerFirst;
		T mainContainerSecond;

		size_t tmp = g_countRandNumbers;
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		containerPushBack(mainContainerFirst);
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		containerPushBack(mainContainerSecond);
		ft::swap(tmp, g_countRandNumbers);

		C alterContainerFirst(mainContainerFirst.begin(), mainContainerFirst.end());
		C alterContainerSecond(mainContainerSecond.begin(), mainContainerSecond.end());

		std::cout << BLUE << std::setw(15) << "Compare " << std::setw(5) << "ft" << std::setw(5) << "std" << RESET << std::endl;
		std::cout << std::setw(15) << "==" << std::setw(5) << (mainContainerFirst == mainContainerSecond) << std::setw(5) << (alterContainerFirst == alterContainerSecond) << std::endl;
		std::cout << std::setw(15) << "!=" << std::setw(5) << (mainContainerFirst != mainContainerSecond) << std::setw(5) << (alterContainerFirst != alterContainerSecond) << std::endl;
		std::cout << std::setw(15) << "<" << std::setw(5) << (mainContainerFirst < mainContainerSecond) << std::setw(5) << (alterContainerFirst < alterContainerSecond) << std::endl;
		std::cout << std::setw(15) << "<=" << std::setw(5) << (mainContainerFirst <= mainContainerSecond) << std::setw(5) << (alterContainerFirst <= alterContainerSecond) << std::endl;
		std::cout << std::setw(15) << ">" << std::setw(5) << (mainContainerFirst > mainContainerSecond) << std::setw(5) << (alterContainerFirst > alterContainerSecond) << std::endl;
		std::cout << std::setw(15) << ">=" << std::setw(5) << (mainContainerFirst >= mainContainerSecond) << std::setw(5) << (alterContainerFirst >= alterContainerSecond) << std::endl;

	}


}

#endif
