#ifndef DEQUESAFE_H
#define DEQUESAFE_H

#include <deque>
#include <mutex>
#include <thread>

#include <assert.h>

// #include "wsdata.h"

template <class T>
class DequeThreadSafe {
public:

    void clear() {
        std::lock_guard<std::mutex> lock(this->_deque_mutex);
        while (!_deque.empty()) {
            this->_deque.pop_front();
        }
    }

    T get(int index) {
        std::lock_guard<std::mutex> lock(this->_deque_mutex);
        assert(index >= 0 && index < this->_deque.size());
        return this->_deque[index];
    }

    T pop() {
        std::lock_guard<std::mutex> lock(this->_deque_mutex);
        assert(!_deque.empty());
        T item = this->_deque.front();
        this->_deque.pop_front();
        return item;
    }

    void push(T item) {
        std::lock_guard<std::mutex> lock(this->_deque_mutex);
        this->_deque.push_back (item);
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(this->_deque_mutex);
        return this->_deque.size();
    }

protected:

    std::deque<T> _deque;
    std::mutex _deque_mutex; 

};


#endif
