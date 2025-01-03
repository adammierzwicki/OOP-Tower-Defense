#pragma once

#include <iostream>

#include "../inc/logger.h"

template <typename T>
class Queue {
private:
    struct Node {
        T obj;
        Node* next;
    };

    Node* head;
    Node* tail;
    int size;

    Logger* logger;

public:
    Queue<T>();
    ~Queue<T>();

    void push(T obj);
    T pop();
    int getSize() const;
    bool empty() const;
    void print() const;
};

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

template <typename T>
Queue<T>::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;

    this->logger = Logger::getInstance();
}

template <typename T>
Queue<T>::~Queue() {
    while (this->head != nullptr) {
        Node* temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
}

//-----------------------------------
//          Public methods
//-----------------------------------

template <typename T>
void Queue<T>::push(T obj) {
    Node* newNode = new Node;
    newNode->obj = obj;
    newNode->next = nullptr;
    if (this->tail == nullptr) {
        this->head = newNode;
        this->tail = newNode;
        this->size++;
        return;
    }
    this->tail->next = newNode;
    this->tail = newNode;
    this->size++;
}

template <typename T>
T Queue<T>::pop() {
    if (this->head == nullptr) {
        this->logger->log(LogLevel::CRITICAL, "Cannot pop from empty queue", "Queue::pop()", __LINE__);
        throw std::runtime_error("Cannot pop from empty queue");
    }
    T obj = this->head->obj;
    Node* temp = head;
    this->head = this->head->next;
    if (this->head == nullptr) {
        this->tail = nullptr;
    }
    delete temp;
    this->size--;
    return obj;
}

template <typename T>
int Queue<T>::getSize() const { return this->size; }

template <typename T>
bool Queue<T>::empty() const { return this->size == 0; }

template <typename T>
void Queue<T>::print() const {
    Node* temp = this->head;
    while (temp != nullptr) {
        std::cout << temp->obj << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}
