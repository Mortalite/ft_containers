#include "list.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "multimap.hpp"
#include "set.hpp"
#include "multiset.hpp"

#include "print.hpp"
#include "mainTest.hpp"
#include "stackTest.hpp"
#include "queueTest.hpp"
#include "mapTest.hpp"
#include "setTest.hpp"

size_t g_countRandNumbers = 3;
size_t g_printMargin = 15;
size_t g_mapMarginCoeff = 3;
int g_intMin = -500, g_intMax = 500;
float g_floatMin = -500.0, g_floatMax = 500.0;

void testList() {
	std::cout << RED << "||||||||||LIST||||||||||" << RESET << std::endl;

	typedef ft::list<cType> ftType;
	typedef std::list<cType> stdType;

	ft::testConstructors<ftType,stdType>();
	ft::testIterators<ftType, stdType>();
	ft::testAssign<ftType, stdType>();
	ft::testPushFront<ftType, stdType>();
	ft::testPopFront<ftType, stdType>();
	ft::testInsert<ftType, stdType>();
	ft::testErase<ftType, stdType>();
	ft::testSwap<ftType, ftType>();
	ft::testResize<ftType, stdType>();
	ft::testSplice<ftType, stdType>();
	ft::testRemove<ftType, stdType>();
	ft::testUnique<ftType, stdType>();
	ft::testMerge<ftType, stdType>();
	ft::testSort<ftType, stdType>();
	ft::testReverse<ftType, stdType>();
	ft::testOperators<ftType, stdType>();
}

void testVector() {
	std::cout << RED << "||||||||||VECTOR||||||||||" << RESET << std::endl;

	typedef ft::vector<cType> ftType;
	typedef std::vector<cType> stdType;

	ft::testConstructors<ftType, stdType>();
	ft::testIterators<ftType, stdType>();
	ft::testAssign<ftType, stdType>();
	ft::testInsert<ftType, stdType>();
	ft::testErase<ftType, stdType>();
	ft::testSwap<ftType, ftType>();
	ft::testOperators<ftType, stdType>();
}

void testMap() {
	std::cout << RED << "||||||||||MAP||||||||||" << RESET << std::endl;

	typedef ft::map<cType, cType> ftType;
	typedef std::map<cType, cType> stdType;

	ft::testMapConstructors<ftType, stdType>();
	ft::testMapIterators<ftType, stdType>();
	ft::testMapInsert<ftType, stdType>();
	ft::testMapErase<ftType, stdType>();
	ft::testMapSwap<ftType, ftType>();
	ft::testMapOperations<ftType, stdType>();
	ft::testMapNonMember<ftType, stdType>();
}

void testStack() {
	std::cout << RED << "||||||||||STACK||||||||||" << RESET << std::endl;

//	typedef ft::vector<cType> underContainer;
	typedef ft::list<cType> underContainer;

	ft::testStackAll<ft::stack<cType, underContainer>, std::stack<cType, underContainer>,  underContainer>();
}

void testQueue() {
	std::cout << RED << "||||||||||QUEUE||||||||||" << RESET << std::endl;

//	typedef ft::vector<cType> underContainer;
	typedef ft::list<cType> underContainer;

	ft::testQueueAll<ft::queue<cType, underContainer>, std::queue<cType, underContainer>,  underContainer>();
}

void testMultiMap() {
	std::cout << RED << "||||||||||MULTIMAP||||||||||" << RESET << std::endl;

	typedef ft::multimap<cType, cType> ftType;
	typedef std::multimap<cType, cType> stdType;

	ft::testMapConstructors<ftType, stdType>();
	ft::testMapIterators<ftType, stdType>();
	ft::testMapInsert<ftType, stdType>();
	ft::testMapErase<ftType, stdType>();
	ft::testMapSwap<ftType, ftType>();
	ft::testMapOperations<ftType, stdType>();
	ft::testMapNonMember<ftType, stdType>();
}

void testSet() {
 	std::cout << RED << "||||||||||SET||||||||||" << RESET << std::endl;

 	typedef ft::set<cType> ftType;
 	typedef std::set<cType> stdType;

 	ft::testSetConstructors<ftType, stdType>();
 	ft::testSetIterators<ftType, stdType>();
 	ft::testSetInsert<ftType, stdType>();
 	ft::testSetErase<ftType, stdType>();
 	ft::testSetSwap<ftType, ftType>();
 	ft::testSetOperations<ftType, stdType>();
 	ft::testSetNonMember<ftType, stdType>();
}


void testMultiSet() {
	std::cout << RED << "||||||||||MULTISET||||||||||" << RESET << std::endl;

	typedef ft::multiset<cType> ftType;
	typedef std::multiset<cType> stdType;

	ft::testSetConstructors<ftType, stdType>();
	ft::testSetIterators<ftType, stdType>();
	ft::testSetInsert<ftType, stdType>();
	ft::testSetErase<ftType, stdType>();
	ft::testSetSwap<ftType, ftType>();
	ft::testSetOperations<ftType, stdType>();
	ft::testSetNonMember<ftType, stdType>();
}

int main() {
	srand(time(NULL));
	std::cout.setf(std::ios::left);

	std::cout << RED << "Mandatory part" << RESET << std::endl;
//	testList();
//	testVector();
//	testMap();
//	testStack();
//	testQueue();

	std::cout << RED << "Bonus part" << RESET << std::endl;
//	testMultiMap();
//	testSet();
//	testMultiSet();

	std::vector<int> vec(4, 100);

	return (0);
}
