#pragma once

#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node* node = new Node(value);
        if (rear) {
            rear->next = node;
        } else {
            front = node;
        }
        rear = node;
        ++count;
    }

    void dequeue() {
        if (empty()) throw std::out_of_range("Queue is empty");
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        --count;
    }

    T& peek() {
        if (empty()) throw std::out_of_range("Queue is empty");
        return front->data;
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }
};

