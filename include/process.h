#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <mutex>
#include <thread>

#include "dequesafe.h"
#include "websocket.h"


namespace process {


class AbstractProcessor {
public:

    AbstractProcessor();
    ~AbstractProcessor();

    bool getBeakFlag();
    void setBeakFlag(bool b);

    virtual void mainloop() = 0;

protected:
    bool _break_flag = false;
    std::mutex _break_mutex;
};




class CaptureProcessor : public AbstractProcessor {
public:

    CaptureProcessor();
    ~CaptureProcessor();

    void setCaptureObject(websocket::AbstractWebsocket *websocket);
    void setWsObjectDeque(DequeThreadSafe<wsdata::WSObject> *_wsdata_object);
    void mainloop();


protected:
    websocket::AbstractWebsocket *_websocket;
    DequeThreadSafe<wsdata::WSObject> *_wsobject_deque;

};

// ----------------------------------------------------------------------------

class DisplayProcessor : public AbstractProcessor {
public:

    DisplayProcessor();
    ~DisplayProcessor();

    void setWsDataDeque(DequeThreadSafe<wsdata::Wsdata *> *_wsdata_deque);
    void mainloop();

protected:
    DequeThreadSafe<wsdata::Wsdata *> *_wsdata_deque;
};

// ----------------------------------------------------------------------------

class ProcessingProcessor : public DisplayProcessor {
public:

    ProcessingProcessor();
    ~ProcessingProcessor();

    void setWsObjectDeque(DequeThreadSafe<wsdata::WSObject> *_wsdata_object);
    void mainloop();

protected:
    DequeThreadSafe<wsdata::WSObject> *_wsobject_deque;
};


};




#endif
