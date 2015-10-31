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


char* customSubString(unsigned short start, unsigned short end, char* inputString){

    char stringHolder[40];
    char* pLine = &stringHolder[0];

    // Moves the input string to the 'start' location
    for(unsigned short i = 0; i < start; i++){
        inputString++;
    }

    // copies over the values from the input string to the new string
    for(unsigned short i = 0; i < end; i++){
        *pLine = *inputString;
        pLine++;
        inputString++;
    }

    // add line terminator
    *pLine = '\0';

    // reset pointer
    pLine = &stringHolder[0];

    return pLine;
}