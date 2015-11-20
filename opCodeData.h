//
// Created by brandon on 10/28/15.
//

#ifndef DISSASEMBLER_OPCODEDATA_H
#define DISSASEMBLER_OPCODEDATA_H

struct _opCodeData{

    char* bits;
    char* name;
    unsigned int formatType;
};

typedef struct _opCodeData OpCodeData;

/***
 * Returns the opCodeData struct that corresponds to the given bits
 */
void FindOpCodeByBits(char* bits, OpCodeData* opCodeData);

/**
 * Creates valid OpCodeData struct
 */
void opCodeInit(OpCodeData* opCodeData);

/**
 * Frees the dynamic values in an opCodeData struct
 */
void freeOpCodeData(OpCodeData* opCode);

/**
 * Clears the arrays of an opCodeData Struct
 */
void resetOpCode(OpCodeData* opCode);

/***
 * Finds the funct by bits
 */
void FindFunctByBits(char* bits, OpCodeData* opCodeData);

#endif //DISSASEMBLER_OPCODEDATA_H
