#include "Queue.hpp"
#include <stdexcept>

template <typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr), count(0) {}

template <typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        dequeue();
    }
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    Node* node = new Node(value);
    if (rear) {
        rear->next = node;
    } else {
        front = node;
    }
    rear = node;
    ++count;
}

template <typename T>
void Queue<T>::dequeue() {
    if (empty()) throw std::out_of_range("Queue is empty");
    Node* temp = front;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    --count;
}

template <typename T>
T& Queue<T>::peek() {
    if (empty()) throw std::out_of_range("Queue is empty");
    return front->data;
}

template <typename T>
bool Queue<T>::empty() const {
    return count == 0;
}

template <typename T>
size_t Queue<T>::size() const {
    return count;
}