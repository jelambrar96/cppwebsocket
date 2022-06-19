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

websocket::CurlWebsocket::CurlWebsocket() {}
websocket::CurlWebsocket::~CurlWebsocket() {}

void websocket::CurlWebsocket::init() {}
void websocket::CurlWebsocket::config(std::string filename) {}
bool websocket::CurlWebsocket::createConection() { return false;}
void websocket::CurlWebsocket::closeConection() {}

bool websocket::CurlWebsocket::getWSObject(wsdata::WSObject &wso) {

    std::stringstream os;

    try {
        curlpp::Cleanup myCleanup;
        curlpp::Easy myRequest;
        myRequest.setOpt<curlpp::options::Url>("http://localhost:8080");
        os << myRequest;
    }
    catch(curlpp::RuntimeError & e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    catch(curlpp::LogicError & e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    std::string strJson = os.str();
    Json::Value root;
    Json::Reader reader;

    bool parsingSuccessful = reader.parse( strJson.c_str(), root );
    if (!parsingSuccessful) {
        std::cout  << "Failed to parse" << reader.getFormattedErrorMessages();
        return false;
    }

    if (!root.isMember("a") || !root.isMember("b")) {
        return false;
    }

    int a = root.get("a", "A a Value if not exists" ).asInt();
    uint32_t b = root.get("b", "A a Value if not exists" ).asDouble();

    wso.a = a;
    wso.b = b;

    return true;
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
    _ws = websockh_create_connection("127.0.0.1", 8080, "/", NULL);
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
