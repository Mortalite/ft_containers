#ifndef QUEUETEST_HPP
#define QUEUETEST_HPP

namespace ft {

	template<typename T, typename C, typename K>
	void testQueueAll() {

		K containerFirst;
		K containerSecond;

		containerPushBack(containerFirst);
		containerPushBack(containerSecond);

		T ftQueueEmpty;
		C stdQueueEmpty;

		std::cout << "ft : Empty = " << ftQueueEmpty.empty() << " , Size = " << ftQueueEmpty.size() << std::endl;
		std::cout << "std : Empty = " << stdQueueEmpty.empty() << " , Size = " << stdQueueEmpty.size() << std::endl;

		T ftQueue(containerFirst);
		C stdQueue(containerFirst);

		std::cout << "ft : front = " << ftQueue.front() << ", Back = " << ftQueue.back() << ", Empty = ";
		std::cout << ftQueue.empty() << " , Size = " << ftQueue.size() << std::endl;

		std::cout << "std : front = " << stdQueue.front() << ", Back = " << stdQueue.back() << ", Empty = ";
		std::cout << stdQueue.empty() << " , Size = " << stdQueue.size() << std::endl;

		std::cout << BLUE << "Push 10" << RESET << std::endl;
		ftQueue.push(10);
		stdQueue.push(10);

		while (!ftQueue.empty()) {
			std::cout << "ft : front = " << ftQueue.front() << ", Back = " << ftQueue.back() << ", Empty = ";
			std::cout << ftQueue.empty() << " , Size = " << ftQueue.size() << std::endl;
			std::cout << "std : front = " << stdQueue.front() << ", Back = " << stdQueue.back() << ", Empty = ";
			std::cout << stdQueue.empty() << " , Size = " << stdQueue.size() << std::endl;
			ftQueue.pop();
			stdQueue.pop();
		}

		containerFirst.clear();
		containerSecond.clear();

		size_t tmp = g_countRandNumbers;
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		containerPushBack(containerFirst);
		g_countRandNumbers = rand() % tmp + rand() % tmp;
		containerPushBack(containerSecond);
		ft::swap(tmp, g_countRandNumbers);

		T ftQueueFirst(containerFirst);
		T ftQueueSecond(containerSecond);

		C stdStackFirst(containerFirst);
		C stdStackSecond(containerSecond);

		std::cout << BLUE << "First and second queue" << RESET << std::endl;
		printIterator(containerFirst);
		printIterator(containerSecond);

		std::cout << BLUE << std::setw(15) << "Compare " << std::setw(5) << "ft" << std::setw(5) << "std" << RESET << std::endl;
		std::cout << std::setw(15) << "==" << std::setw(5) << (ftQueueFirst == ftQueueSecond) << std::setw(5) << (stdStackFirst == stdStackSecond) << std::endl;
		std::cout << std::setw(15) << "!=" << std::setw(5) << (ftQueueFirst != ftQueueSecond) << std::setw(5) << (stdStackFirst != stdStackSecond) << std::endl;
		std::cout << std::setw(15) << "<" << std::setw(5) << (ftQueueFirst < ftQueueSecond) << std::setw(5) << (stdStackFirst < stdStackSecond) << std::endl;
		std::cout << std::setw(15) << "<=" << std::setw(5) << (ftQueueFirst <= ftQueueSecond) << std::setw(5) << (stdStackFirst <= stdStackSecond) << std::endl;
		std::cout << std::setw(15) << ">" << std::setw(5) << (ftQueueFirst > ftQueueSecond) << std::setw(5) << (stdStackFirst > stdStackSecond) << std::endl;
		std::cout << std::setw(15) << ">=" << std::setw(5) << (ftQueueFirst >= ftQueueSecond) << std::setw(5) << (stdStackFirst >= stdStackSecond) << std::endl;

	}

}

#endif