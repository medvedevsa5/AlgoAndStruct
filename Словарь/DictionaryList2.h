#ifndef DICT_LIST
#define DICT_LIST

#include <string>

/* https://stackoverflow.com/questions/1724036/splitting-templated-c-classes-into-hpp-cpp-files-is-it-possible
It is not possible to write the implementation of a template class in a separate cpp file and compile.
All the ways to do so, if anyone claims, are workarounds to mimic the usage of separate cpp file.
*/


template <typename T>
class DictionaryArray
{
private:

	struct Node
	{
		Node* next = nullptr;
		T key = {};
	};

	Node* head_ = nullptr;

public:

	DictionaryArray() {}
	DictionaryArray(const DictionaryArray& dict) noexcept { }
	DictionaryArray& operator=(const DictionaryArray& dict) noexcept 
	{
		Node* buff = nullptr;
		Node* tmp = head_;
		while (tmp != nullptr)
		{
			buff = tmp;
			tmp = tmp->next;
			delete buf;
		}
		this->head_ = nullptr;
		tmp = dict.head_;
		while (tmp != nullptr)
		{
			Node* temp = new Node();
		}
	}
	DictionaryArray(DictionaryArray&& dict) noexcept 
	{
		this->head_ = dict.head_;
		dict.head_ = nullptr;
	}
	DictionaryArray& operator=(DictionaryArray&& dict) noexcept
	{
		if (this->head_ != dict.head_)
		{
			this->head_ = dict.head_;
			dict.head_ = nullptr;
		}
		return *this;
	}

	~DictionaryArray() 
	{
		Node* temp = head_;
		while (temp != nullptr)
		{
			Node* temp = head_;
			Node* next = head_->next;
			delete temp;
		}
	}

	void insertWord(T word)
	{
		Node* prev = nullptr;
		Node* tmp = head_;

		if (tmp == nullptr)
		{
			auto newNode = new Node();
			newNode->key = word;
			newNode->next = nullptr;
			head_ = newNode;
			return;
		}

		while (tmp != nullptr && word < tmp->key)
		{
			prev = tmp;
			tmp = tmp->next;
		}

		if (word == tmp->key)
		{
			return;
		}
		
		if (tmp == nullptr) // вставка в конец списка
		{
			auto newNode = new Node();
			newNode->key = word;
			newNode->next = nullptr;

			prev->next = newNode;
		}
		else if (prev == nullptr) // вставка в начало списка
		{
			auto newNode = new Node();
			newNode->key = word;
			newNode->next = head_;

			head_ = newNode;
		}
		else // вставка в середину списка
		{
			auto newNode = new Node();
			newNode->key = word;
			newNode->next = tmp;

			prev = newNode;
		}

		
	}

	void deleteWord(T word)
	{
		Node* prev = nullptr;
		Node* tmp = head_;

		while (tmp != nullptr && tmp->key != word)
		{
			prev = tmp;
			tmp = tmp->next;
		}

		if(tmp != nullptr)
		{
			prev->next = tmp->next;
		}
	}

	bool searchWord(T word) const
	{
		Node* tmp = head_;

		while (tmp != nullptr)
		{
			if (tmp->key == word) 
				return true;
		}

		return false;
	}

	void mergeDict(DictionaryArray& right);
	void deleteDict(DictionaryArray& right);
	friend DictionaryArray getIntersection(DictionaryArray<T>& left, DictionaryArray<T>& right);

	friend std::ostream& operator<<(std::ostream& stream, const DictionaryArray& dict)
	{
		Node* tmp = dict.head_;
		while (tmp != nullptr)
		{
			stream << tmp->key;
			tmp = tmp->next;
		}
		return stream;
	}
};

// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file

#endif