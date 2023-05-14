#include <iosfwd>

class DoublyLinkedList
{
private:

    struct Node
    {
        Node* prev;
        Node* next;

        int key;

        Node(int key, Node* prev, Node* next);
    };

    Node* head_;

public:

    DoublyLinkedList();
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList& dict) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList& dict) = delete;
    DoublyLinkedList(DoublyLinkedList&& dict) = delete;
    DoublyLinkedList& operator=(DoublyLinkedList&& dict) = delete;

    void insertHead(int key);
    void insertTail(int key);
    void replaceByMin();

    friend std::ostream& operator<<(std::ostream&, DoublyLinkedList& list);

};