#include "websocket.h"


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

void websocket::KythonWebsocket::init() {
    _ssl_ctx = websockh_init_ssl_ctx();
}
void websocket::KythonWebsocket::config(std::string filename) {}
bool websocket::KythonWebsocket::createConection() {     
    // websockh ws = websockh_create_connection("stream.binance.com", 9443, "/ws/btcusdt@trade", ssl_ctx);
    // websockh ws = websockh_create_connection("209.126.82.146", 8080, "", NULL);
    _ws = websockh_create_connection("127.0.0.1", 5000, "/", NULL);
    if (_ws == NULL) {
        printf("ws == NULL\n");
        return  false;
    }
}
void websocket::KythonWebsocket::closeConection() {
    if (_ws == NULL) {
        return;
    }
    websockh_close_connection(_ws);
}

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
bool websocket::RandomWebsocket::createConection() { return true; }
void websocket::RandomWebsocket::closeConection() {}

bool websocket::RandomWebsocket::getWSObject(wsdata::WSObject &wso) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100) );
    wso.a = rand() % 100;
    wso.b = rand() % 100;
    // std::cout << "a: " << wso.a << " b: " << wso.b << "\n"; 
    return true;
}
