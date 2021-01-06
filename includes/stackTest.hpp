#ifndef STACKTEST_HPP
#define STACKTEST_HPP

namespace ft {


	template<typename T, typename C, typename K>
	void testStackAll() {

		K containerFirst;
		K containerSecond;

		containerPushBack(containerFirst);
		containerPushBack(containerSecond);

		T ftStackEmpty;
		C stdStackEmpty;

		std::cout << "ft : Empty = " << ftStackEmpty.empty() << " , Size = " << ftStackEmpty.size() << std::endl;
		std::cout << "std : Empty = " << stdStackEmpty.empty() << " , Size = " << stdStackEmpty.size() << std::endl;

		T ftStack(containerFirst);
		C stdStack(containerFirst);

		std::cout << "ft : Top = " << ftStack.top() << ", Empty = " << ftStack.empty() << " , Size = " << ftStack.size() << std::endl;
		std::cout << "std : Top = " << stdStack.top() << ", Empty = " << stdStack.empty() << " , Size = " << stdStack.size() << std::endl;

		std::cout << BLUE << "Push 10" << RESET << std::endl;
		ftStack.push(10);
		stdStack.push(10);

		while (!ftStack.empty()) {
			std::cout << "ft : Top = " << ftStack.top() << ", Empty = " << ftStack.empty() << " , Size = " << ftStack.size() << std::endl;
			std::cout << "std : Top = " << stdStack.top() << ", Empty = " << stdStack.empty() << " , Size = " << stdStack.size() << std::endl;
			ftStack.pop();
			stdStack.pop();
		}

		containerFirst.clear();
		containerSecond.clear();

		size_t tmp = g_countRandNumbers;
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		containerPushBack(containerFirst);
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		containerPushBack(containerSecond);
		ft::swap(tmp, g_countRandNumbers);

		T ftStackFirst(containerFirst);
		T ftStackSecond(containerSecond);

		C stdStackFirst(containerFirst);
		C stdStackSecond(containerSecond);

		std::cout << BLUE << "First and second stack" << RESET << std::endl;
		printIterator(containerFirst);
		printIterator(containerSecond);

		std::cout << BLUE << std::setw(15) << "Compare " << std::setw(5) << "ft" << std::setw(5) << "std" << RESET << std::endl;
		std::cout << std::setw(15) << "==" << std::setw(5) << (ftStackFirst == ftStackSecond) << std::setw(5) << (stdStackFirst == stdStackSecond) << std::endl;
		std::cout << std::setw(15) << "!=" << std::setw(5) << (ftStackFirst != ftStackSecond) << std::setw(5) << (stdStackFirst != stdStackSecond) << std::endl;
		std::cout << std::setw(15) << "<" << std::setw(5) << (ftStackFirst < ftStackSecond) << std::setw(5) << (stdStackFirst < stdStackSecond) << std::endl;
		std::cout << std::setw(15) << "<=" << std::setw(5) << (ftStackFirst <= ftStackSecond) << std::setw(5) << (stdStackFirst <= stdStackSecond) << std::endl;
		std::cout << std::setw(15) << ">" << std::setw(5) << (ftStackFirst > ftStackSecond) << std::setw(5) << (stdStackFirst > stdStackSecond) << std::endl;
		std::cout << std::setw(15) << ">=" << std::setw(5) << (ftStackFirst >= ftStackSecond) << std::setw(5) << (stdStackFirst >= stdStackSecond) << std::endl;

	}

}

#endif