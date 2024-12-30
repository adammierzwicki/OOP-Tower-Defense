#pragma once


template <typename T>
class Queue {
private:
    struct Node {
        T obj;
        Node *next;
    };

    Node *head;
    Node *tail;
    int size;

public:
    Queue<T>();
    ~Queue<T>();

    bool empty();
    int getSize();
    void print();
    T pop();
    void push(T obj);
};

template <typename T>
Queue<T>::Queue()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template <typename T>
Queue<T>::~Queue()
{
    while (this->head != nullptr)
    {
        Node *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
}

template <typename T>
bool Queue<T>::empty() { return this->size == 0; }

template <typename T>
int Queue<T>::getSize() { return this->size; }

template <typename T>
void Queue<T>::print()
{
    Node *temp = this->head;
    while (temp != nullptr)
    {
        std::cout << temp->obj << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template <typename T>
T Queue<T>::pop()
{
    if (this->head == nullptr)
    {
        throw std::runtime_error("Cannot pop from empty queue");
    }
    T obj = this->head->obj;
    Node *temp = head;
    this->head = this->head->next;
    if (this->head == nullptr)
    {
        this->tail = nullptr;
    }
    delete temp;
    this->size--;
    return obj;
}

template <typename T>
void Queue<T>::push(T obj)
{
    Node *newNode = new Node;
    newNode->obj = obj;
    newNode->next = nullptr;
    if (this->tail == nullptr)
    {
        this->head = newNode;
        this->tail = newNode;
        this->size++;
        return;
    }
    this->tail->next = newNode;
    this->tail = newNode;
    this->size++;
}
