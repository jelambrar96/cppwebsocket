#include "websocket.h"
#include "wsdata.h"

// ----------------------------------------------------------------------------

websocket::BoostWebsocket::BoostWebsocket() {}
websocket::BoostWebsocket::~BoostWebsocket() {}

void websocket::BoostWebsocket::init() {}
void websocket::BoostWebsocket::config(std::string filename) {}
bool websocket::BoostWebsocket::createConection() { return false;}
void websocket::BoostWebsocket::closeConection() {}

bool websocket::BoostWebsocket::getWSObject(wsdata::WSObject &wso) {
    return false;
}

// ----------------------------------------------------------------------------

websocket::KythonWebsocket::KythonWebsocket() {}
websocket::KythonWebsocket::~KythonWebsocket() {}

void websocket::KythonWebsocket::init() {}
void websocket::KythonWebsocket::config(std::string filename) {}
bool websocket::KythonWebsocket::createConection() { return false; }
void websocket::KythonWebsocket::closeConection() {}

bool websocket::KythonWebsocket::getWSObject(wsdata::WSObject &wso) {
    return false;
}

// ----------------------------------------------------------------------------

websocket::RandomWebsocket::RandomWebsocket() {}
websocket::RandomWebsocket::~RandomWebsocket() {}

void websocket::RandomWebsocket::init() {
    srand (time(NULL));
}
void websocket::RandomWebsocket::config(std::string filename) {}
bool websocket::RandomWebsocket::createConection() { return false; }
void websocket::RandomWebsocket::closeConection() {}

bool websocket::RandomWebsocket::getWSObject(wsdata::WSObject &wso) {
    std::this_thread::sleep_for(std::chrono::milliseconds(20000) );
    wso.a = rand() % 100;
    wso.b = rand() % 100;
    return true;
}
