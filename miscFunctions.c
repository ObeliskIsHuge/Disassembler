//
// Created by brandon on 10/28/15.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "miscFunctions.h"


int stringBinaryToInt(char* string, bool halfValue){

    int total = 0;
    while (*string){
        total *= 2;
        if (*string++ == '1'){
            total += 1;
        }
    }

    if(halfValue){

        return total/2;
    }

    return total;
}


char* customSubString(unsigned short start, unsigned short end, char* inputString){


    char* pLine = (char *)calloc(100, sizeof(char *));

    // calculates the new end point
    end -= start;

    // Moves the input string to the 'start' location
    for(unsigned short i = 0; i < start; i++){
        inputString++;
    }

    // stores how far the pointer is away from the beginning
    int resetPointer = 0;
    // copies over the values from the input string to the new string
    for(unsigned short i = 0; i < end; i++){
        *pLine = *inputString;
        pLine++;
        inputString++;
        resetPointer++;
    }

    // goes back to the beginning of the array
    for(unsigned short i = 0; i < resetPointer; i++){
        pLine--;
    }

    return pLine;
}

char* convertBinToDecString(char* binaryString, bool halfValue){

    char* stringPointer = (char *)calloc(100, sizeof(char *));
    int immediate;

    // converts the binary string to an integer
    immediate = stringBinaryToInt(binaryString, halfValue);

    char* tempNameArray = (char *)calloc(100, sizeof(char *));
    sprintf(tempNameArray, "%d", immediate);

    // copies the string over to a permanent location
    strcpy(stringPointer, tempNameArray);

    free(tempNameArray);

    return stringPointer;
}
