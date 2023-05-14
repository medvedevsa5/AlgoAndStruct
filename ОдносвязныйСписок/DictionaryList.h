#pragma once
#include <iosfwd>

template <typename T>
class DictionaryList
{
private:

    struct Node
    {
        Node* next = nullptr;
        T key = {};

        Node(T key, Node* next = nullptr)
        {
            this->next = next;
            this->key = key;
        }
    };

    Node* head_ = nullptr;

    bool insertNode(Node* newNode)
    {
        if (newNode == nullptr)
        {
            return false;
        }
        if (head_ == nullptr)
        {
            head_ = newNode;
            return true;
        }
        if (head_->key == newNode->key)
        {
            return false;
        }
        if (head_->key > newNode->key)
        {
            newNode->next = head_;
            head_ = newNode;
            return true;
        }
        Node* temp = head_;
        while (temp->next != nullptr)
        {
            if (temp->next->key == newNode->key)
            {
                return false;
            }
            if (temp->next->key > newNode->key)
            {
                newNode->next = temp->next;
                temp->next = newNode;
                return true;
            }
            temp = temp->next;
        }
        temp->next = newNode;
        return true;
    }

public:

    DictionaryList() { }

    DictionaryList(const DictionaryList& dict) noexcept 
    {
        head_ = nullptr;
        Node* next = dict.head_;
        while (next != nullptr)
        {
            Node* temp = new Node(next->key);
            this->insertNode(temp);
            next = next->next;
        }
    }

    DictionaryList& operator=(const DictionaryList& dict) noexcept
    {
        Node* buff = nullptr;
        Node* tmp = head_;
        while (tmp != nullptr)
        {
            buff = tmp;
            tmp = tmp->next;
            delete buff;
        }
        this->head_ = nullptr;
        tmp = dict.head_;
        while (tmp != nullptr)
        {
            Node* temp = new Node(tmp->key);
            this->insertNode(temp);
            tmp = tmp->next;
        }
        return *this;
    }

    DictionaryList(DictionaryList&& dict) noexcept
    {
        this->head_ = dict.head_;
        dict.head_ = nullptr;
    }

    DictionaryList& operator=(DictionaryList&& dict) noexcept
    {
        if (this->head_ != dict.head_)
        {
            this->head_ = dict.head_;
            dict.head_ = nullptr;
        }
        return *this;
    }

    ~DictionaryList()
    {
        Node* temp = head_;
        while (temp != nullptr)
        {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    void insertWord(T word)
    {
        Node* prev = nullptr;
        Node* tmp = head_;

        if (tmp == nullptr)
        {
            auto newNode = new Node(word);
            head_ = newNode;
            return;
        }

        while (tmp != nullptr && word > tmp->key)
        {
            prev = tmp;
            tmp = tmp->next;
        }

        if (tmp != nullptr && tmp->key == word)
        {
            return;
        }

        if (tmp == nullptr) // вставка в конец списка
        {
            auto newNode = new Node(word);
            prev->next = newNode;
        }
        else if (prev == nullptr) // вставка в начало списка
        {
            auto newNode = new Node(word, head_);
            head_ = newNode;
        }
        else // вставка в середину списка
        {
            auto newNode = new Node(word, tmp);
            prev->next = newNode;
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

        if (tmp != nullptr && prev != nullptr)
        {
            prev->next = tmp->next;
        }
        else if (tmp != nullptr)
        {
            this->head_ = tmp->next;
            delete tmp;
        }
    }

    bool searchWord(T word) const
    {
        Node* tmp = head_;

        while (tmp != nullptr)
        {
            if (tmp->key == word)
                return true;
            tmp = tmp->next;
        }

        return false;
    }

    void mergeDict(DictionaryList& dict)
    {
        while (dict.head_ != nullptr)
        {
            Node* buff = dict.head_->next;
            dict.head_->next = nullptr;
            if (insertNode(dict.head_))
            {
                dict.head_ = buff;
                continue;
            }
            delete dict.head_;
            dict.head_ = buff;
        }
    }

    void deleteDict(DictionaryList& dict)
    {
        if (dict.head_ == nullptr || head_ == nullptr)
        {
            return;
        }
        Node* temp = dict.head_;
        while (temp != nullptr)
        {
            this->deleteWord(temp->key);
            temp = temp->next;
        }
    }

    friend DictionaryList* getIntersection(const DictionaryList<T>& left, const DictionaryList<T>& right)
    {
        auto newDict = new DictionaryList<T>();
        auto crowlerL = new Node(left.head_->key, left.head_->next);
        auto crowlerR = new Node(right.head_->key, right.head_->next);

        while (crowlerL != nullptr)
        {
            newDict->insertWord(crowlerL->key);
            crowlerL = crowlerL->next;
        }

        while (crowlerR != nullptr)
        {
            newDict->insertWord(crowlerR->key);
            crowlerR = crowlerR->next;
        }

        return newDict;
    }

    friend std::ostream& operator<<(std::ostream& stream, const DictionaryList& dict)
    {
        Node* tmp = dict.head_;
        while (tmp != nullptr)
        {
            stream << tmp->key << "\n";
            tmp = tmp->next;
        }
        return stream;
    }
};