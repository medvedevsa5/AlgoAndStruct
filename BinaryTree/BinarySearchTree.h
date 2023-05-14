#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <string>
#include <iosfwd>
#include <stack>
#include <queue>
#include <strstream>

template <class T>
class BinarySearchTree
{

public:

	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;
	~BinarySearchTree();
	
	bool iterativeSearch(const T& key) const;

	bool insert(const T& key);
	
	// 3.1 Удаление элемента из дерева, не нарушающее порядка элементов
	// true, если элемент удален; false, если элемента не было
	bool deleteKey(const T& key);
	
	// 4.1 Печать строкового изображения дерева в выходной поток out,
	// использовать скобки, чтобы показать структуру дерева
	void print(std::ostream& out) const;
	
	// 5.1 Определение количества узлов дерева
	int getCount() const;
	
	// 6.1 Определение высоты дерева
	int getHeight() const;
	
	// 7 Инфиксный обход дерева (итеративный)
	void iterativeInorderWalk() const;
	
	// 8.1 Инфиксный обход дерева (рекурсивный)
	void inorderWalk() const;
	
	// 9 Обход двоичного дерева по уровням (в ширину).
	void walkByLevels() const;
	
	// 10 Являются ли два дерева похожими
	bool isSimilar(const BinarySearchTree<T>& other) const;
	
	// 11 Есть одинаковые ключи в двух деревьях поиска
	bool isIdenticalKey(const BinarySearchTree<T>& other) const;

	bool isBalancedRecurrent();

	bool isBalancedIterative();
	
private:
	template <class T>
	struct Node
	{
		T key_;
		// значение ключа, содержащееся в узле
		Node<T>* left_;
		// указатель на левое поддерево
		Node<T>* right_;
		// указатель на правое поддерево
		Node<T>* p_;
		// указатель на родителя !!! не используется
		// Конструктор узла
		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p)
		{
		}

		void purge()
		{
			if (this == nullptr)
			{
				return;
			}

			if(this->left_ != nullptr)
				this->left_->purge();

			if(this->right_ != nullptr)
				this->right_->purge();

			delete this;
		}
	};

	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
	BinarySearchTree<T>::Node<T>* iterativeSearchNode(const T& key) const;
	
	// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(std::ostream& out, Node<T>* root) const;
	
	// 5.2 Рекурсивная функция определения количества узлов дерева
	int getCount(const Node<T>* node) const;
	
	// 6.2 Рекурсивная функция определения высоты дерева
	int getHeight(const Node<T>* node) const;
	
	// 8.2 Рекурсивная функция для инфиксного обхода узлов дерева.
	void inorderWalk(Node<T>* node) const;

	Node<T>* root_; // Указатель на корневой узел

	bool isBalancedRecurrent(Node<T>* root);

	
}; // конец шаблона класса TreeBinarySearchTree

#pragma region public

template<typename T>
inline BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) { }

template<typename T>
inline BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src) noexcept
{
	this->root_ = src.root_;
	src.root = nullptr;
}

template<typename T>
inline BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) noexcept
{
	if (this != &src)
	{
		this->root_->purge();
		this->root_ = src.root_;
		src.root_ = nullptr;
	}
	return *this;
}

template<class T>
inline BinarySearchTree<T>::~BinarySearchTree()
{
	this->root_->purge();
}

template<typename T>
inline bool BinarySearchTree<T>::iterativeSearch(const T& key) const
{
	return iterativeSearchNode(key) != nullptr ? true : false;
}

template<typename T>
inline bool BinarySearchTree<T>::insert(const T& key)
{
	BinarySearchTree<T>::Node<T>* tmp = nullptr;
	BinarySearchTree<T>::Node<T>* roamer = this->root_;

	while (roamer != nullptr)
	{
		tmp = roamer;
		if (key < roamer->key_)
		{
			roamer = roamer->left_;
		}
		else if (key > roamer->key_)
		{
			roamer = roamer->right_;
		}
		else
		{
			return false;
		}
	}

	auto newNode = new BinarySearchTree<T>::Node<T>(key, nullptr, nullptr, tmp);

	if (tmp == nullptr)
	{
		this->root_ = newNode;
	}
	else if(key < tmp->key_)
	{
		tmp->left_ = newNode;
	}
	else
	{
		tmp->right_ = newNode;
	}

	return true;
}

template<typename T>
inline bool BinarySearchTree<T>::deleteKey(const T& key)
{
	if (this->root_ == nullptr)
	{
		return false;
	}

	Node<T>* current = this->root_;
	Node<T>* parent = nullptr;

	// Ищем узел с ключом
	while (current != nullptr && current->key_ != key)
	{
		parent = current;
		if (key < current->key_)
		{
			current = current->left_;
		}
		else
		{
			current = current->right_;
		}
	}

	if (current == nullptr)
	{
		return false;
	}

	// Узел не имеет правого поддерева
	if (current->right_ == nullptr)
	{
		if (parent == nullptr)
		{
			root_ = current->left_;
		}
		else if (current == parent->left_)
		{
			parent->left_ = current->left_;
		}
		else
		{
			parent->right_ = current->left_;
		}
		delete current;
	}

	// Узел имеет правое поддерево, у которого нет левого потомка
	else if (current->right_->left_ == nullptr)
	{
		current->right_->left_ = current->left_;
		if (parent == nullptr)
		{
			root_ = current->right_;
		}
		else if (current == parent->left_)
		{
			parent->left_ = current->right_;
		}
		else
		{
			parent->right_ = current->right_;
		}
		delete current;
	}

	// Узел имеет правое поддерево, у которого есть левый потомок
	else
	{
		Node<T>* leftmost = current->right_->left_;
		Node<T>* leftmostParent = current->right_;
		while (leftmost->left_ != nullptr)
		{
			leftmostParent = leftmost;
			leftmost = leftmost->left_;
		}
		leftmostParent->left_ = leftmost->right_;
		leftmost->left_ = current->left_;
		leftmost->right_ = current->right_;
		if (parent == nullptr)
		{
			root_ = leftmost;
		}
		else if (current == parent->left_)
		{
			parent->left_ = leftmost;
		}
		else
		{
			parent->right_ = leftmost;
		}
		delete current;
	}

	return true;
}

template<class T>
inline void BinarySearchTree<T>::print(std::ostream& out) const
{
	printNode(out, this->root_);
}

template<typename T>
inline int BinarySearchTree<T>::getCount() const
{
	return BinarySearchTree<T>::getCount(this->root_);
}

template<class T>
inline int BinarySearchTree<T>::getHeight() const
{
	return getHeight(this->root_);
}

template<class T>
inline void BinarySearchTree<T>::iterativeInorderWalk() const
{
	std::stack<Node<T>*> stack = {};

	Node<T>* current = this->root_;

	while (current != nullptr || !stack.empty())
	{
		while (current != nullptr)
		{
			stack.push(current);
			current = current->left_;
		}
		current = stack.top();
		stack.pop();
		std::cerr << current->key_;
		current = current->right_;
	}
}

template<class T>
inline void BinarySearchTree<T>::inorderWalk() const
{
	inorderWalk(this->root_);
}

template<class T>
inline void BinarySearchTree<T>::walkByLevels() const
{
	if (this->root_ == nullptr)
	{
		return;
	}

	std::queue<Node<T>*> queue;
	queue.push(this->root_);

	while (!queue.empty())
	{
		Node<T>* current = queue.front();
		queue.pop();
		std::cout << current->key_ << " ";

		if (current->left != nullptr)
		{
			queue.push(current->left);
		}

		if (current->right_ != nullptr)
		{
			queue.push(current->right_);
		}
	}
}

template<class T>
inline bool BinarySearchTree<T>::isSimilar(const BinarySearchTree<T>& other) const
{
	if (this == &other)
	{
		return true;
	}
	if (this->root_ == nullptr && other.root_ == nullptr)
	{
		return true;
	}
	if (this->root_ == nullptr || other.root_ == nullptr)
	{
		return false;
	}

	std::stack<Node<T>*> stack1, stack2;
	Node<T>* current1 = this->root_;
	Node<T>* current2 = other.root_;

	while (current1 != nullptr || !stack1.empty() || current2 != nullptr || !stack2.empty())
	{
		while (current1 != nullptr)
		{
			stack1.push(current1);
			current1 = current1->left_;
		}

		while (current2 != nullptr)
		{
			stack2.push(current2);
			current2 = current2->left_;
		}

		if (stack1.size() != stack2.size())
		{
			return false;
		}

		current1 = stack1.top();
		stack1.pop();

		current2 = stack2.top();
		stack2.pop();

		if (current1->key_ != current2->key_)
		{
			return false;
		}
		current1 = current1->right_;
		current2 = current2->right_;
	}
	return true;
}

template<class T>
inline bool BinarySearchTree<T>::isIdenticalKey(const BinarySearchTree<T>& other) const
{
	if (root_ == nullptr || other.root_ == nullptr)
	{
		return false;
	}

	std::stack<Node<T>*> stack1, stack2;
	stack1.push(root_);
	stack2.push(other.root_);

	while (!stack1.empty() && !stack2.empty())
	{
		Node<T>* node1 = stack1.top();
		stack1.pop();
		Node<T>* node2 = stack2.top();
		stack2.pop();

		if (node1->key_ == node2->key_)
		{
			return true;
		}

		if (node1->right_ != nullptr && node2->right_ != nullptr)
		{
			stack1.push(node1->right_);
			stack2.push(node2->right_);
		}

		if (node1->left_ != nullptr && node2->left_ != nullptr)
		{
			stack1.push(node1->left_);
			stack2.push(node2->left_);
		}
	}

	return false;
}

template<class T>
inline bool BinarySearchTree<T>::isBalancedRecurrent()
{
	return isBalancedRecurrent(this->root_);
}

template<class T>
inline bool BinarySearchTree<T>::isBalancedIterative()
{
	if (this->root_ == nullptr)
	{
		return true;
	}

	std::stack<Node<T>*> nodes; // Вы говорили, что можно.... (мне лень подключать заголовки)
	std::stack<int> heights;

	nodes.push(this->root_);
	heights.push(0);
	int heightDifference = 0;

	while (!nodes.empty())
	{
		Node<T>* current = nodes.top();

		nodes.pop();

		int height = heights.top();

		heights.pop();

		if (current->left_ == nullptr && current->right_ == nullptr)
		{
			if (heights.empty())
			{
				return true;
			}

			heightDifference = height - heights.top();

			if (abs(heightDifference) > 1)
			{
				return false;
			}
		}
		else
		{
			if (current->left_ != nullptr)
			{
				nodes.push(current->left_);
				heights.push(height + 1);
			}
			if (current->right_ != nullptr)
			{
				nodes.push(current->right_);
				heights.push(height + 1);
			}
		}
	}

	return true;
}

#pragma endregion

#pragma region private

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	BinarySearchTree<T>::Node<T>* buff = this->root_;

	while (buff != nullptr)
	{
		if (key < buff->key_)
		{
			buff = buff->left_;
		}
		else if (key > buff->key_)
		{
			buff = buff->right_;
		}
		else
		{
			return buff;
		}
	}

	return nullptr;
}

template<class T>
inline void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const
{
	if (root == nullptr)
	{
		return;
	}

	out << "(";
	printNode(out, root->left_);

	out << root->key_;

	printNode(out, root->right_);
	out << ")";
}

template<class T>
inline int BinarySearchTree<T>::getCount(const Node<T>* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return (1 + getCount(node->left) + getCount(node->right));
}

template<class T>
inline int BinarySearchTree<T>::getHeight(const Node<T>* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
}

template<class T>
inline void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
{
	if (node != nullptr)
	{
		inorderWalk(node->left_);
		std::cerr << node->key_;
		inorderWalk(node->right_);
	}
}

template<class T>
inline bool BinarySearchTree<T>::isBalancedRecurrent(Node<T>* root)
{
	if (root == nullptr)
	{
		return true;
	}

	int leftLength = getHeight(root->left_);
	int rightLength = getHeight(root_->right_);

	if (std::abs(leftLength - rightLength) > 1)
	{
		return false;
	}

	return true;
}



#pragma endregion

#endif


