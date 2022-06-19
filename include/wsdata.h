#ifndef WSDATA_H
#define WSDATA_H

#include <cstdint>
#include <stdio.h>
#include <iostream>
#include <mutex>

namespace wsdata {

class WSObject{
public:
    int a;
    uint32_t b;

    // WSObject(WSObject &wso) { a = wso.a; b = wso.b;}
};

struct Wsdata {
public:
    Wsdata();
    ~Wsdata();

    void add_number(uint16_t number);
    void clear(); 
    void display();

private:

    uint32_t max_number;
    uint32_t min_number;
    uint32_t first_number;
    uint32_t last_number;
    uint16_t number_of_prime_numbers;
    uint16_t number_of_even_numbers;
    uint16_t number_of_odd_numbers;

    bool __first_time = false;
    std::mutex __mutex;
}; // struct Wsdata

bool isprime(uint16_t number);

}; // namespace wsdata

#endif
