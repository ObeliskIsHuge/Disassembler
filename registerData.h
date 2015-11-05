//
// Created by brandon on 10/28/15.
//

#ifndef DISSASEMBLER_REGISTERDATA_H
#define DISSASEMBLER_REGISTERDATA_H

#include <inttypes.h>

struct _RegisterData{

    char* bits;
    int registerField;
    char* registerName;
};

typedef struct _RegisterData RegisterData;


/***
 * Returns the RegisterData struct that corresponds to the given bits
 */
void FindRegisterDataByBits(char* bits, RegisterData* registerData);

/***
 * Creates a valid RegisterData Struct
 */
void registerDataInit(RegisterData* registerData);

/***
 * Frees the data from a RegisterData Struct
 */
void registerDataFree(RegisterData* registerData);

/***
 * Resets the register Data struct
 */
void resetRegisterData(RegisterData* registerData);

/***
 * Frees the memory of a register Data struct
 */
void freeRegisterDataStruct(RegisterData* registerData);
#endif //DISSASEMBLER_REGISTERDATA_H
