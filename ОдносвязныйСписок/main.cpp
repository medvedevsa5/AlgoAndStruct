#include "DictionaryList.h"

#include <iostream>

int main()
{
	auto list1 = new DictionaryList<int>();
	auto list2 = new DictionaryList<int>();

	list2->insertWord(123);

	list1->insertWord(123);
	list1->insertWord(1234);
	list1->insertWord(12345);
	list1->insertWord(123456);
	list1->insertWord(12344);

	list2->insertWord(123);
	list2->insertWord(1233412);
	list2->insertWord(1235);
	list2->insertWord(1231231);

	list2->deleteDict(*list1);

	auto result = getIntersection(*list1, *list2);

	std::cout << *list1 << std::endl;
	std::cout << *list2 << std::endl;

	std::cout << *result;

	delete list1;
	delete list2;
	delete result;

	return 0;
}