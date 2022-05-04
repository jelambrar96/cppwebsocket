#include <iostream>
#include <thread>

#include "dequesafe.h"
#include "websocket.h"
#include "process.h"
#include "wsdata.h"



int main (int argc, char *argv[])  {

    // se crea el buffer donde se almancenan los datos obtenidos
    // del websocket
    DequeThreadSafe<wsdata::WSObject> _deque_in; 

    // se crea el objeto que  es capturar los datos de websocket
    websocket::AbstractWebsocket * _websocket = new websocket::RandomWebsocket();
    _websocket->init();

    // se crea el objeto que almancena los 100 bloques de informacion 
    DequeThreadSafe<wsdata::Wsdata *> _deque_proc; 
    for (size_t i = 0; i < 100; ++i) {
        _deque_proc.push(new wsdata::Wsdata());
    }

    // se crea el objeto "hilo" que captura los datos
    process::CaptureProcessor * capture = new process::CaptureProcessor();
    capture->setCaptureObject(_websocket);
    capture->setWsObjectDeque(&_deque_in);
    std::thread capture_thread(&process::CaptureProcessor::mainloop, capture);

    // se crea el objeto "hilo" que procesa los datos
    process::ProcessingProcessor * processor = new process::ProcessingProcessor();
    processor->setWsObjectDeque(&_deque_in);
    processor->setWsDataDeque(&_deque_proc);
    std::thread processing_thread(&process::ProcessingProcessor::mainloop, processor);

    // se crea el objeto "hilo" que imprime los datos y los restatura
    process::DisplayProcessor * displayed = new process::DisplayProcessor();
    displayed->setWsDataDeque(&_deque_proc);
    std::thread displaying_thread(&process::DisplayProcessor::mainloop, displayed);

    // se mira el estado de los hilos, en caso que alguno falle, 
    // lo correcto es terminar la aplicacion,
    // es decir, detener los hilos resultantes

    while (true) {
        bool cond = capture->getBeakFlag() || processor->getBeakFlag() || displayed->getBeakFlag();
        if (cond) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    capture_thread.join();
    processing_thread.join();
    displaying_thread.join();

    delete displayed;
    delete processor;
    delete capture;

    // se eliminan los 100 bloques de informacion
    for (size_t i = 0, n = _deque_proc.size(); i < n; ++i) {
        wsdata::Wsdata * temp_pointer;
        temp_pointer = _deque_proc.get(i);
        delete temp_pointer; // free memory
    }
    while(_deque_proc.size() > 0) {
        _deque_proc.pop();
    }

    // se eliminan los objetos capturados
    while (_deque_in.size() > 0) {
        _deque_proc.pop();
    }
    
    return 0;
}

