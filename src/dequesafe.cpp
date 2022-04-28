#include "dequesafe.h"

void DequeThreadSafe::clear() {
    std::lock_guard<std::mutex> lock(this->_deque_mutex);
    while (!_deque.empty()) {
        this->_deque.pop_front();
    }
}

wsdata::Wsdata DequeThreadSafe::pop() {
    std::lock_guard<std::mutex> lock(this->_deque_mutex);
    assert(!_deque.empty());
    wsdata::Wsdata item = this->_deque.front();
    this->_deque.pop_front();
    return item;
}

void DequeThreadSafe::push(wsdata::Wsdata item) {
    std::lock_guard<std::mutex> lock(this->_deque_mutex);
    this->_deque.push_back (item);
}

size_t DequeThreadSafe::size() {
    std::lock_guard<std::mutex> lock(this->_deque_mutex);
    return this->_deque.size();
}

