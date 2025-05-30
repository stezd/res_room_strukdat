#pragma once

#include <stdexcept>

template <typename T>
class Stack {
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    size_t count;

public:
    Stack() : topNode(nullptr), count(0) {}

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* node = new Node(value);
        node->next = topNode;
        topNode = node;
        ++count;
    }

    void pop() {
        if (empty()) throw std::out_of_range("Stack is empty");
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        --count;
    }

    T& peek() {
        if (empty()) throw std::out_of_range("Stack is empty");
        return topNode->data;
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }
};
