//
// Created by brandon on 10/28/15.
//

#include "miscFunctions.h"


int16_t stringBinaryToInt(char* string){

    int16_t total = 0;
    while (*string){
        total *= 2;
        if (*string++ == '1'){
            total += 1;
        }
    }

    return total;
}