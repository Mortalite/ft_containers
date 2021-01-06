#ifndef MAPTESTER_HPP
#define MAPTESTER_HPP

namespace ft {

	template<typename T>
	void mapRandomInsert(T& container) {
		for (size_t i = 0; i < g_countRandNumbers; i++) {
			typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
			typename T::mapped_type mappedTmp = getRandomValueByType<typename T::mapped_type>();
			container.insert(std::make_pair(keyTmp, mappedTmp));
		}
	}

	template<typename T, typename C>
	void mapRandomInsert(T& mainContainer, C& alterContainer) {
		for (size_t i = 0; i < g_countRandNumbers; i++) {
			typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
			typename T::mapped_type mappedTmp = getRandomValueByType<typename T::mapped_type>();
			mainContainer.insert(std::make_pair(keyTmp, mappedTmp));
			alterContainer.insert(std::make_pair(keyTmp, mappedTmp));
		}
	}

	template<typename T, typename C>
	void testMapConstructors() {
		std::cout << RED << "Constructors" << RESET << std::endl;

		bool isMap = (typeid(typename T::key_type) != typeid(typename T::value_type));

/*	if (typeid(typename T::value_type) == typeid(std::pair<const typename T::key_type, typename T::mapped_type>))
		std::cout << BLUE << "SUPER TESTTTT" << RESET << std::endl;*/

		std::cout << BLUE << "Fill (rand<T>(), rand<T>())" << RESET << std::endl;
		T mainContainerFill;
		C alterContainerFill;

		if ((typeid(typename T::key_type) != typeid(typename T::value_type)))
			mapRandomInsert(mainContainerFill, alterContainerFill);
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

		for (size_t i = 0; i < g_countRandNumbers; i++) {
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

		T mainContainer;
		C alterContainer;

		std::cout << BLUE << "Random map" << RESET << std::endl;
		mapRandomInsert(mainContainer, alterContainer);
		printCmpIteratorMap(mainContainer, alterContainer);

		typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
		typename T::mapped_type mappedTmp = getRandomValueByType<typename T::mapped_type>();
		std::cout << BLUE << "Insert in end(" << keyTmp << ", " << mappedTmp << ")" << RESET << std::endl;
		mainContainer.insert(mainContainer.end(), std::make_pair(keyTmp, mappedTmp));
		alterContainer.insert(alterContainer.end(), std::make_pair(keyTmp, mappedTmp));
		printCmpIteratorMap(mainContainer, alterContainer);

		T mainContainerRand;
		C alterContainerRand;

		std::cout << BLUE << "Random map" << RESET << std::endl;
		mapRandomInsert(mainContainerRand, alterContainerRand);
		printCmpIteratorMap(mainContainerRand, alterContainerRand);

		std::cout << BLUE << "Insert using reverse iterator" << RESET << std::endl;
		mainContainer.insert(mainContainerRand.rbegin(), mainContainerRand.rend());
		alterContainer.insert(alterContainerRand.rbegin(), alterContainerRand.rend());
		printCmpIteratorMap(mainContainer, alterContainer);

	}

	template<typename T, typename C>
	void testMapErase() {
		std::cout << RED << "Erase function" << RESET << std::endl;

		T mainContainer;
		C alterContainer;
		mapRandomInsert(mainContainer, alterContainer);
		printCmpIteratorMap(mainContainer, alterContainer);

		std::cout << BLUE << "Erase from begin" << RESET << std::endl;
		mainContainer.erase(mainContainer.begin());
		alterContainer.erase(alterContainer.begin());
		printCmpIteratorMap(mainContainer, alterContainer);

		std::cout << BLUE << "Erase from --end" << RESET << std::endl;
		mainContainer.erase(--mainContainer.end());
		alterContainer.erase(--alterContainer.end());
		printCmpIteratorMap(mainContainer, alterContainer);

		std::cout << BLUE << "Random map" << RESET << std::endl;
		mapRandomInsert(mainContainer, alterContainer);
		printCmpIteratorMap(mainContainer, alterContainer);

		std::cout << BLUE << "Erase [begin, end)" << RESET << std::endl;
		mainContainer.erase(mainContainer.begin(), mainContainer.end());
		alterContainer.erase(alterContainer.begin(), alterContainer.end());
		std::cout << BLUE << "After Erase" << RESET << std::endl;
		printCmpIteratorMap(mainContainer, alterContainer);
	}

	template<typename T, typename C>
	void testMapSwap() {
		std::cout << RED << "Swap function" << RESET << std::endl;

		T mainContainer;
		C alterContainer;
		mapRandomInsert(mainContainer);
		mapRandomInsert(alterContainer);

		std::cout << BLUE << "Before Swap" << RESET << std::endl;
		printIteratorMap(mainContainer);
		printIteratorMap(alterContainer);
		mainContainer.swap(alterContainer);
		std::cout << BLUE << "After Swap" << RESET << std::endl;
		printIteratorMap(mainContainer);
		printIteratorMap(alterContainer);
	}

	template<typename T, typename C>
	void testMapOperations() {
		std::cout << RED << "Map operations" << RESET << std::endl;

		T mainContainer;
		mapRandomInsert(mainContainer);
		C alterContainer(mainContainer.begin(), mainContainer.end());

		typename T::iterator mainIt;
		typename C::iterator alterIt;

		std::cout << BLUE << "Random map" << RESET << std::endl;
		printCmpIteratorMap(mainContainer, alterContainer);

		std::cout << BLUE << "Find iterator to begin + 1" << RESET << std::endl;
		mainIt = mainContainer.find((*(++mainContainer.begin())).first);
		alterIt = alterContainer.find((*(++alterContainer.begin())).first);
		if (mainIt != mainContainer.end() && alterIt != alterContainer.end())
			std::cout << "mainIt = " << (*mainIt).first << ", alterIt = " << (*alterIt).first << std::endl;

		std::cout << BLUE << "Count (begin + 1) key" << RESET << std::endl;
		typename T::size_type countMain = mainContainer.count((*(++mainContainer.begin())).first);
		typename T::size_type countAlter = alterContainer.count((*(++alterContainer.begin())).first);
		std::cout << "mainCount = " << countMain << ", alterCount = " << countAlter << std::endl;

		std::cout << BLUE << "Count random key" << RESET << std::endl;
		typename T::key_type keyTmp = getRandomValueByType<typename T::key_type>();
		std::cout << "key = " << keyTmp << ", mainCount = " << mainContainer.count(keyTmp) <<\
		", alterCount = " << alterContainer.count(keyTmp) << std::endl;

		keyTmp = getRandomValueByType<typename T::key_type>();
		std::cout << BLUE << "Lower bound of " << keyTmp << RESET << std::endl;
		mainIt = mainContainer.lower_bound(keyTmp);
		alterIt = alterContainer.lower_bound(keyTmp);
		if (mainIt != mainContainer.end())
			std::cout << "mainIt = (" << (*mainIt).first << ", " << (*mainIt).second << ")" << std::endl;
		if (alterIt != alterContainer.end())
			std::cout << "alterIt = (" << (*alterIt).first << ", " << (*alterIt).second << ")" << std::endl;

		keyTmp = getRandomValueByType<typename T::key_type>();
		std::cout << BLUE << "Upper bound of " << keyTmp << RESET << std::endl;
		mainIt = mainContainer.upper_bound(keyTmp);
		alterIt = alterContainer.upper_bound(keyTmp);
		if (mainIt != mainContainer.end())
			std::cout << "mainIt = (" << (*mainIt).first << ", " << (*mainIt).second << ")" << std::endl;
		if (alterIt != alterContainer.end())
			std::cout << "alterIt = (" << (*alterIt).first << ", " << (*alterIt).second << ")" << std::endl;

		keyTmp = getRandomValueByType<typename T::key_type>();
		std::cout << BLUE << "Equal range iterator of " << keyTmp << RESET << std::endl;
		std::pair<typename T::iterator, typename T::iterator> equalRangeMain = mainContainer.equal_range(keyTmp);
		std::pair<typename C::iterator, typename C::iterator> equalRangeAlter = alterContainer.equal_range(keyTmp);
		mainIt = equalRangeMain.first;
		alterIt = equalRangeAlter.first;
		while (alterIt != equalRangeAlter.second) {
			std::stringstream stringStream;
			stringStream << "mainIt = (" << (*mainIt).first << ", " << (*mainIt).second << ")";
			std::cout << std::setw(g_printMargin * g_mapMarginCoeff) << stringStream.str();
			std::cout << "alterIt = (" << (*alterIt).first << ", " << (*alterIt).second << ")" << std::endl;
			mainIt++;
			alterIt++;
		}

	}

	template <typename T, typename C>
	void testMapNonMember() {
		std::cout << RED << "Non-member function" << RESET << std::endl;

		T mainContainerFirst;
		T mainContainerSecond;

		size_t tmp = g_countRandNumbers;
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		mapRandomInsert(mainContainerFirst);
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		mapRandomInsert(mainContainerSecond);
		ft::swap(tmp, g_countRandNumbers);

		C alterContainerFirst(mainContainerFirst.begin(), mainContainerFirst.end());
		C alterContainerSecond(mainContainerSecond.begin(), mainContainerSecond.end());

		std::cout << BLUE << "First and second map" << RESET << std::endl;
		printCmpIteratorMap(mainContainerFirst, alterContainerFirst);
		printCmpIteratorMap(mainContainerSecond, alterContainerSecond);

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
