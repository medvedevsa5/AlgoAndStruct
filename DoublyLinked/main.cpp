#include <iostream>
#include "DoublyLinkedList.h"

void testList();

int main()
{

	testList();



	return 0;
}

void testList()
{
	DoublyLinkedList* list = new DoublyLinkedList();

	for (size_t i = 0; i < 10; i++)
	{
		list->insertHead(i);
	}
	for (size_t i = 0; i < 10; i++)
	{
		list->insertTail(i);
	}

	std::cout << *list << std::endl;

	list->replaceByMin();

	std::cout << *list;

	delete list;
}