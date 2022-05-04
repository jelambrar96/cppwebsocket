#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <chrono>
#include <string>
#include <thread>

#ifdef __cplusplus 
extern "C" {
#endif

#include "handshake.h"
#include "websockh.h"

#ifdef __cplusplus 
}
#endif

#include "wsdata.h"


namespace websocket
{
    
// ----------------------------------------------------------------------------
const std::string HOST = "209.126.82.146";
const int PORT = 8080;
const std::string PATH = "/";
// ----------------------------------------------------------------------------


class AbstractWebsocket {
public:
    AbstractWebsocket() {};
    virtual ~AbstractWebsocket() {};

    virtual void init() = 0;
    virtual void config(std::string filename) = 0;
    virtual bool createConection() = 0;
    virtual void closeConection() = 0;
    
    virtual bool getWSObject(wsdata::WSObject &wso) = 0;

    bool getDebug() { return _debug; }
    bool setDebug(bool b) { _debug = b; }

protected:
    bool _debug = false;
};


class BoostWebsocket : public AbstractWebsocket {
public:
    BoostWebsocket();
    virtual ~BoostWebsocket();

    virtual void init();
    virtual void config(std::string filename);
    virtual bool createConection();
    virtual void closeConection();

    bool getWSObject(wsdata::WSObject &wso);
};


class KythonWebsocket: public AbstractWebsocket {
public:
    KythonWebsocket();
    virtual ~KythonWebsocket();

    virtual void init();
    virtual void config(std::string filename);
    virtual bool createConection();
    virtual void closeConection();

    bool getWSObject(wsdata::WSObject &wso);

private:
    websockh _ws; 
    SSL_CTX *_ssl_ctx;
};


class RandomWebsocket: public AbstractWebsocket {
public:
    RandomWebsocket();
    virtual ~RandomWebsocket();

    virtual void init();
    virtual void config(std::string filename);
    virtual bool createConection();
    virtual void closeConection();

    bool getWSObject(wsdata::WSObject &wso);
};


} // namespace websocket


#endif