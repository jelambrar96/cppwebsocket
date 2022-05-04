#include "process.h"

process::AbstractProcessor::AbstractProcessor() {
    this->_break_flag = false;
}

process::AbstractProcessor::~AbstractProcessor() {
}

void process::AbstractProcessor::setBeakFlag(bool b) {
    std::lock_guard<std::mutex> lock(this->_break_mutex);
    this->_break_flag = b;
}

bool process::AbstractProcessor::getBeakFlag() {
    std::lock_guard<std::mutex> lock(this->_break_mutex);
    return this->_break_flag; //  = b;
}

// ----------------------------------------------------------------------------

process::CaptureProcessor::CaptureProcessor() {
    this->_break_flag = false;
}

process::CaptureProcessor::~CaptureProcessor() {
}

void process::CaptureProcessor::setCaptureObject(websocket::AbstractWebsocket *websocket) {
    this->_websocket = websocket;
}

void process::CaptureProcessor::setWsObjectDeque(DequeThreadSafe<wsdata::WSObject> *_wsobject_deque) {
    this->_wsobject_deque = _wsobject_deque;
}

void process::CaptureProcessor::mainloop() {

    std::chrono::_V2::system_clock::time_point t_start;
    std::chrono::_V2::system_clock::time_point t_end;
    std::chrono::nanoseconds::rep t_delta;

    t_start = std::chrono::high_resolution_clock::now();

    while(!this->getBeakFlag()) {

        wsdata::WSObject wsobject;
        bool flag = _websocket->getWSObject(wsobject);
        if (!flag) {
            continue;
        }
        // std::cout << "push\n";
        // std::cout << "size: " << _wsobject_deque->size() << "\n";
        this->_wsobject_deque->push(wsobject);
        // std::cout << "size: " << _wsobject_deque->size() << "\n";

    }

    this->setBeakFlag(true);
}


// ---------------------------------------------------------------------------

process::DisplayProcessor::DisplayProcessor() {
    this->_break_flag = false;
}

process::DisplayProcessor::~DisplayProcessor() {
}

void process::DisplayProcessor::setWsDataDeque(DequeThreadSafe<wsdata::Wsdata *> *_wsdata_deque) {
    this->_wsdata_deque = _wsdata_deque;
}

void process::DisplayProcessor::mainloop() {
    
    std::chrono::_V2::system_clock::time_point t_start;
    std::chrono::_V2::system_clock::time_point t_end;
    std::chrono::nanoseconds::rep t_delta;

    t_start = std::chrono::high_resolution_clock::now();

    while(!this->getBeakFlag()) {

        // wait 1 minute
        t_end = std::chrono::high_resolution_clock::now();
        t_delta = 60 * 1e9  - (t_end-t_start).count();
        // t_delta = t_delta < 0 ? 0 : t_delta;
        // std::cout << "t delta: " << (int)t_delta << "\n";
        std::this_thread::sleep_for(std::chrono::nanoseconds(t_delta));
        t_start = std::chrono::high_resolution_clock::now();

        // print data
        for (size_t i = 0, n = this->_wsdata_deque->size(); i < n; ++i) {
            wsdata::Wsdata * temp_wsdata = this->_wsdata_deque->get(i);
            std::cout << "i: " << i << std::endl;
            temp_wsdata->display();
            std::cout << "\n";
        }

        // clean data
        for (size_t i = 0, n = this->_wsdata_deque->size(); i < n; ++i) {
            wsdata::Wsdata * temp_wsdata = this->_wsdata_deque->get(i);
            temp_wsdata->clear();
        }

    }
    
    this->setBeakFlag(true);
}

// ----------------------------------------------------------------------------

process::ProcessingProcessor::ProcessingProcessor() {
    this->_break_flag = false;
}

process::ProcessingProcessor::~ProcessingProcessor() {
}

void process::ProcessingProcessor::setWsObjectDeque(DequeThreadSafe<wsdata::WSObject> *_wsobject_deque) {
    this->_wsobject_deque = _wsobject_deque;
}

void process::ProcessingProcessor::mainloop() {

    while(!this->getBeakFlag()) {

        size_t capture_buffer_size = this->_wsobject_deque->size();
        if (capture_buffer_size == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sleep 100 ms
            continue;
        }

        // continue;

        wsdata::WSObject temp_object = this->_wsobject_deque->pop();
        int index = temp_object.a;
        int value = temp_object.b;

        // std::cout << "POP.a: " << index << " POP.b: " << value << "\n"; 


        wsdata::Wsdata * block_data = this->_wsdata_deque->get(index);
        block_data->add_number(value);
        // block_data->display();

    }

    this->setBeakFlag(true);
}

