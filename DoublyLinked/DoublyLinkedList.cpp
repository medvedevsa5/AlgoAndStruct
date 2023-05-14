#include "DoublyLinkedList.h"

#include <iostream>

DoublyLinkedList::DoublyLinkedList() : head_(nullptr) {}

DoublyLinkedList::~DoublyLinkedList()
{
	if (head_ == nullptr)
	{
		return;
	}

	Node* temp = this->head_;
	Node* next = this->head_->next;

	while (next != nullptr)
	{
		delete temp;

		temp = next;
		next = next->next;

	}
}

void DoublyLinkedList::insertHead(int key)
{
	if (head_ == nullptr)
	{
		head_ = new Node(key, nullptr, head_);
		return;
	}

	Node* tmp = new Node(key, nullptr, head_);
	head_->prev = tmp;
	head_ = tmp;
}

void DoublyLinkedList::insertTail(int key)
{
	Node* crowler = head_;

	if (crowler == nullptr)
	{
		insertHead(key);
		return;
	}

	while (crowler->next != nullptr)
	{
		crowler = crowler->next;
	}

	Node* tmp = new Node(key, crowler, nullptr);
	crowler->next = tmp;
}

// я не понял что мне делать при одинаковых значениях, поэтому просто удаляется левый.
void DoublyLinkedList::replaceByMin()
{
	Node* crowler = this->head_;
	Node* maxNode = nullptr;

	while (crowler != nullptr && crowler->next != nullptr)
	{
		if (crowler->key < crowler->next->key)
		{
			maxNode = crowler->next;
			crowler = crowler->next;
			if (crowler != nullptr)
			{
				crowler = crowler->next;
			}
		}
		else
		{
			maxNode = crowler;
			crowler = crowler->next;
			if (crowler != nullptr)
			{
				crowler = crowler->next;
			}
		}

		Node* left = maxNode->prev;
		Node* right = maxNode->next;

		if (left != nullptr && right != nullptr)
		{
			left->next = right;
			right->prev = left;
		}
		else if (left == nullptr && right != nullptr)
		{
			head_ = right;
			right->prev = nullptr;
		}
		else if (left != nullptr && right == nullptr)
		{
			left->next = right;
			return;
		}

		delete maxNode;
	}
}

DoublyLinkedList::Node::Node(int key, Node* prev, Node* next)
{
	this->key = key;
	this->prev = prev;
	this->next = next;
}

std::ostream& operator<<(std::ostream& out, DoublyLinkedList& list)
{
	DoublyLinkedList::Node* crowler = list.head_;

	while (crowler != nullptr)
	{
		if (crowler->prev == nullptr)
		{
			std::cout << "err";
		}
		out << crowler->key << ' ';
		crowler = crowler->next;
	}

	return out;
}
