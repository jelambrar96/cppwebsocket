#ifndef DEQUESAFE_H
#define DEQUESAFE_H

#include <deque>
#include <mutex>
#include <thread>

#include <assert.h>

#include "wsdata.h"

class DequeThreadSafe {
public:

    void clear();
    wsdata::Wsdata pop();
    void push(wsdata::Wsdata item);
    size_t size();

protected:

    std::deque<wsdata::Wsdata> _deque;
    std::mutex _deque_mutex; 

};


#endif
