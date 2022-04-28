#include "wsdata.h"


wsdata::Wsdata::Wsdata() {
    max_number = NULL;
    min_number = NULL;
    first_number = NULL;
    last_number = NULL;

    number_of_prime_numbers = 0;
    number_of_even_numbers = 0;
    number_of_odd_numbers = 0;
}

wsdata::Wsdata::~Wsdata() {}

void wsdata::Wsdata::add_number(uint16_t number) {

    last_number = number;

    if (wsdata::isprime(number)) {
        number_of_prime_numbers++;
    }

    if (number % 2 == 0) {
        number_of_even_numbers++;
    } else {
        number_of_odd_numbers++;
    }

    if (__first_time) {
        max_number = number;
        min_number = number;
        first_number = number;
        __first_time = false;
        return;
    }

    max_number = number > max_number ? number : max_number;
    min_number = number < min_number ? number : min_number;
    
}

void wsdata::Wsdata::clear() {

    max_number = NULL;
    min_number = NULL;
    first_number = NULL;
    last_number = NULL;

    number_of_prime_numbers = 0;
    number_of_even_numbers = 0;
    number_of_odd_numbers = 0;

    __first_time = true;
}

bool wsdata::isprime(uint16_t number) {
    if (number < 2) {
        return false;
    }
    bool even_flag = number % 2 == 0;
    if (even_flag) {
        return false;
    }
    uint16_t max_compare = number / 3;
    for (uint16_t i = 3; i < max_compare; i+=2) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
};