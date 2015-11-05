#include "registerData.h"
#include <string.h>
#include <stdlib.h>

#define TOTALAMOUNTOFREGISTERS 32
#define REGISTERBITSIZE 5
#define REGISTERNAMESIZE 5


static RegisterData registerTable[TOTALAMOUNTOFREGISTERS] = {

        {"00000", 0, "$zero"},
        {"00001", 1, "$at"},
        {"00010", 2, "$v0"},
        {"00011", 3, "$v1"},
        {"00100", 4, "$a0"},
        {"00101", 5, "$a1"},
        {"00110", 6, "$a2"},
        {"00111", 7, "$a3"},
        {"01000", 8, "$t0"},
        {"01001", 9, "$t1"},
        {"01010", 10, "$t2"},
        {"01011", 11, "$t3"},
        {"01100", 12, "$t4"},
        {"01101", 13, "$t5"},
        {"01110", 14, "$t6"},
        {"01111", 15, "$t7"},
        {"10000", 16, "$t8"},
        {"10001", 17, "$t9"},
        {"10010", 18, "$s0"},
        {"10011", 19, "$s1"},
        {"10100", 20, "$s2"},
        {"10101", 21, "$s3"},
        {"10110", 22, "$s4"},
        {"10111", 23, "$s5"},
        {"11000", 24, "$s6"},
        {"11001", 25, "$s7"},
        {"11010", 26, "$s8"},
        {"11011", 27, "$k0"},
        {"11100", 28, "$k1"},
        {"11101", 29, "$gp"},
        {"11110", 30, "$sp"},
        {"11111", 31, "$ra"}
};

void registerDataInit(RegisterData* registerData){

    registerData->bits = (char *)calloc(100, sizeof(char *));
    registerData->registerName = (char *)calloc(100, sizeof(char *));
    registerData->registerField = 0;
}


void registerDataFree(RegisterData* registerData){

    free(registerData->bits);
    free(registerData->registerName);

}

RegisterData* FindRegisterDataByBits(char* bits){

    for(unsigned int i = 0; i < TOTALAMOUNTOFREGISTERS; i++){

        if(strcmp(registerTable[i].bits, bits) == 0){

            RegisterData foundRegister = registerTable[i];
            RegisterData returnRegister;
            registerDataInit(&returnRegister);

            // copy the strings over
            strcpy(returnRegister.bits, foundRegister.bits);
            strcpy(returnRegister.registerName, foundRegister.registerName);

            // copies over the register field
            returnRegister.registerField = foundRegister.registerField;

            RegisterData* returnPointer = &returnRegister;
            return returnPointer;
        }
    }

    return NULL;
}


void freeRegisterDataStruct(RegisterData* registerData){

    free(registerData->registerName);
    free(registerData->bits);
}