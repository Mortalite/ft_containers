#ifndef SETTEST_HPP
#define SETTEST_HPP

#include "print.hpp"

namespace ft {

	template<typename T>
	void setRandomInsert(T& container) {
		for (size_t i = 0; i < g_countRandNumbers; i++) {
			typename T::value_type valueTmp = getRandomValueByType<typename T::value_type>();
			container.insert(valueTmp);
		}
	}

	template<typename T, typename C>
	void setRandomInsert(T& mainContainer, C& alterContainer) {
		for (size_t i = 0; i < g_countRandNumbers; i++) {
			typename T::value_type valueTmp = getRandomValueByType<typename T::value_type>();
			mainContainer.insert(valueTmp);
			alterContainer.insert(valueTmp);
		}
	}

	template<typename T, typename C>
	void testSetConstructors() {
		std::cout << RED << "Constructors" << RESET << std::endl;

		std::cout << BLUE << "Fill (rand<T>(), rand<T>())" << RESET << std::endl;
		T mainContainerFill;
		C alterContainerFill;

		setRandomInsert(mainContainerFill, alterContainerFill);
		printCmpIterator(mainContainerFill, alterContainerFill);

		std::cout << BLUE << "Iterator constructor" << RESET << std::endl;
		T mainContainerIt(mainContainerFill.begin(), mainContainerFill.end());
		C alterContainerIt(alterContainerFill.begin(), alterContainerFill.end());
		printCmpIterator(mainContainerIt, alterContainerIt);

		std::cout << BLUE << "Copy constructor" << RESET << std::endl;
		T mainContainerCopy(mainContainerIt);
		C alterContainerCopy(alterContainerIt);
		printCmpIterator(mainContainerCopy, alterContainerCopy);

	}

	template<typename T, typename C>
	void testSetIterators() {
		std::cout << RED << "Iterators" << RESET << std::endl;

		std::cout << BLUE << "Fill (rand<T>(), rand<T>())" << RESET << std::endl;
		T mainContainerFill;
		C alterContainerFill;

		setRandomInsert(mainContainerFill, alterContainerFill);
		printCmpIterator(mainContainerFill, alterContainerFill);
		printCmpRevIterator(mainContainerFill, alterContainerFill);
	}

	template<typename T, typename C>
	void testSetInsert() {
		std::cout << RED << "Insert function" << RESET << std::endl;

		T mainContainer;
		C alterContainer;

		std::cout << BLUE << "Random map" << RESET << std::endl;
		setRandomInsert(mainContainer, alterContainer);
		printCmpIterator(mainContainer, alterContainer);

		typename T::value_type valueTmp = getRandomValueByType<typename T::key_type>();
		std::cout << BLUE << "Insert in end(" << valueTmp << ")" << RESET << std::endl;
		mainContainer.insert(mainContainer.end(), valueTmp);
		alterContainer.insert(alterContainer.end(), valueTmp);
		printCmpIterator(mainContainer, alterContainer);

		T mainContainerRand;
		C alterContainerRand;

		std::cout << BLUE << "Random map" << RESET << std::endl;
		setRandomInsert(mainContainerRand, alterContainerRand);
		printCmpIterator(mainContainerRand, alterContainerRand);

		std::cout << BLUE << "Insert using reverse iterator" << RESET << std::endl;
		mainContainer.insert(mainContainerRand.rbegin(), mainContainerRand.rend());
		alterContainer.insert(alterContainerRand.rbegin(), alterContainerRand.rend());
		printCmpIterator(mainContainer, alterContainer);

	}

	template<typename T, typename C>
	void testSetErase() {
		std::cout << RED << "Erase function" << RESET << std::endl;

		T mainContainer;
		C alterContainer;
		setRandomInsert(mainContainer, alterContainer);
		printCmpIterator(mainContainer, alterContainer);

		std::cout << BLUE << "Erase from begin" << RESET << std::endl;
		mainContainer.erase(mainContainer.begin());
		alterContainer.erase(alterContainer.begin());
		printCmpIterator(mainContainer, alterContainer);

		std::cout << BLUE << "Erase from --end" << RESET << std::endl;
		mainContainer.erase(--mainContainer.end());
		alterContainer.erase(--alterContainer.end());
		printCmpIterator(mainContainer, alterContainer);

		std::cout << BLUE << "Random map" << RESET << std::endl;
		setRandomInsert(mainContainer, alterContainer);
		printCmpIterator(mainContainer, alterContainer);

		std::cout << BLUE << "Erase [begin, end)" << RESET << std::endl;
		mainContainer.erase(mainContainer.begin(), mainContainer.end());
		alterContainer.erase(alterContainer.begin(), alterContainer.end());
		std::cout << BLUE << "After Erase" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);
	}

	template<typename T, typename C>
	void testSetSwap() {
		std::cout << RED << "Swap function" << RESET << std::endl;

		T mainContainer;
		C alterContainer;
		setRandomInsert(mainContainer);
		setRandomInsert(alterContainer);

		std::cout << BLUE << "Before Swap" << RESET << std::endl;
		printIterator(mainContainer);
		printIterator(alterContainer);
		mainContainer.swap(alterContainer);
		std::cout << BLUE << "After Swap" << RESET << std::endl;
		printIterator(mainContainer);
		printIterator(alterContainer);
	}

	template<typename T, typename C>
	void testSetOperations() {
		std::cout << RED << "Map operations" << RESET << std::endl;

		T mainContainer;
		setRandomInsert(mainContainer);
		C alterContainer(mainContainer.begin(), mainContainer.end());

		typename T::iterator mainIt;
		typename C::iterator alterIt;

		std::cout << BLUE << "Random map" << RESET << std::endl;
		printCmpIterator(mainContainer, alterContainer);

		std::cout << BLUE << "Find iterator to begin + 1" << RESET << std::endl;
		mainIt = mainContainer.find(*(++mainContainer.begin()));
		alterIt = alterContainer.find(*(++alterContainer.begin()));
		if (mainIt != mainContainer.end() && alterIt != alterContainer.end())
			std::cout << "mainIt = " << *mainIt << ", alterIt = " << *alterIt << std::endl;

		std::cout << BLUE << "Count (begin + 1) key" << RESET << std::endl;
		typename T::size_type countMain = mainContainer.count(*(++mainContainer.begin()));
		typename T::size_type countAlter = alterContainer.count(*(++alterContainer.begin()));
		std::cout << "mainCount = " << countMain << ", alterCount = " << countAlter << std::endl;

		std::cout << BLUE << "Count random key" << RESET << std::endl;
		typename T::value_type valueTmp = getRandomValueByType<typename T::value_type>();
		std::cout << "value = " << valueTmp << ", mainCount = " << mainContainer.count(valueTmp) <<\
		", alterCount = " << alterContainer.count(valueTmp) << std::endl;

		valueTmp = getRandomValueByType<typename T::value_type>();
		std::cout << BLUE << "Lower bound of " << valueTmp << RESET << std::endl;
		mainIt = mainContainer.lower_bound(valueTmp);
		alterIt = alterContainer.lower_bound(valueTmp);
		if (mainIt != mainContainer.end())
			std::cout << "mainIt = (" << *mainIt << ", " << *mainIt << ")" << std::endl;
		if (alterIt != alterContainer.end())
			std::cout << "alterIt = (" << *alterIt << ", " << *alterIt << ")" << std::endl;

		valueTmp = getRandomValueByType<typename T::value_type>();
		std::cout << BLUE << "Upper bound of " << valueTmp << RESET << std::endl;
		mainIt = mainContainer.upper_bound(valueTmp);
		alterIt = alterContainer.upper_bound(valueTmp);
		if (mainIt != mainContainer.end())
			std::cout << "mainIt = (" << *mainIt << ", " << *mainIt << ")" << std::endl;
		if (alterIt != alterContainer.end())
			std::cout << "alterIt = (" << *alterIt << ", " << *alterIt << ")" << std::endl;

		valueTmp = getRandomValueByType<typename T::value_type>();
		std::cout << BLUE << "Equal range iterator of " << valueTmp << RESET << std::endl;
		std::pair<typename T::iterator, typename T::iterator> equalRangeMain = mainContainer.equal_range(valueTmp);
		std::pair<typename C::iterator, typename C::iterator> equalRangeAlter = alterContainer.equal_range(valueTmp);
		mainIt = equalRangeMain.first;
		alterIt = equalRangeAlter.first;
		while (alterIt != equalRangeAlter.second) {
			std::stringstream stringStream;
			stringStream << "mainIt = (" << *mainIt << ", " << *mainIt << ")";
			std::cout << std::setw(g_printMargin * g_mapMarginCoeff) << stringStream.str();
			std::cout << "alterIt = (" << *alterIt << ", " << *alterIt << ")" << std::endl;
			mainIt++;
			alterIt++;
		}

	}

	template <typename T, typename C>
	void testSetNonMember() {
		std::cout << RED << "Non-member function" << RESET << std::endl;

		T mainContainerFirst;
		T mainContainerSecond;

		size_t tmp = g_countRandNumbers;
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		setRandomInsert(mainContainerFirst);
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		setRandomInsert(mainContainerSecond);
		ft::swap(tmp, g_countRandNumbers);

		C alterContainerFirst(mainContainerFirst.begin(), mainContainerFirst.end());
		C alterContainerSecond(mainContainerSecond.begin(), mainContainerSecond.end());

		std::cout << BLUE << "First and second map" << RESET << std::endl;
		printCmpIterator(mainContainerFirst, alterContainerFirst);
		printCmpIterator(mainContainerSecond, alterContainerSecond);

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