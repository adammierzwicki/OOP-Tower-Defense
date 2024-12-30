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
