#ifndef WSDATA_H
#define WSDATA_H

#include <cstdint>
#include <stdio.h>

namespace wsdata {

class WSObject{
public:
    int a;
    int b;
};

struct Wsdata {
public:
    uint32_t max_number;
    uint32_t min_number;
    uint32_t first_number;
    uint32_t last_number;
    uint16_t number_of_prime_numbers;
    uint16_t number_of_even_numbers;
    uint16_t number_of_odd_numbers;

    Wsdata();
    ~Wsdata();

    void add_number(uint16_t number);
    void clear(); 

private:
    bool __first_time = false;
}; // struct Wsdata

bool isprime(uint16_t number);

}; // namespace wsdata

#endif
