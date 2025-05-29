#pragma once

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* front;
    Node* rear;
    size_t count;

public:
    Queue();
    ~Queue();

    void enqueue(const T& value);
    void dequeue();
    T& peek();
    bool empty() const;
    size_t size() const;
};