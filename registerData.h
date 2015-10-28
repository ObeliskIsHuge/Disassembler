//
// Created by brandon on 10/28/15.
//

#ifndef DISSASEMBLER_REGISTERDATA_H
#define DISSASEMBLER_REGISTERDATA_H

#include <inttypes.h>

struct _RegisterData{

    char* bits;
    uint8_t registerField;
    char* registerName;
};

typedef struct _RegisterData RegisterData;


/***
 * Returns the RegisterData struct that corresponds to the given bits
 */
RegisterData* FindRegisterDataByBits(char* bits);

/***
 * Frees the memory of a register Data struct
 */
void freeRegisterDataStruct(RegisterData* registerData);
#endif //DISSASEMBLER_REGISTERDATA_H
