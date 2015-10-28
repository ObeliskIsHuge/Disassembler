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
OpCodeData* FindOpCodeByBits(char* bits);

/**
 * Frees the dynamic values in an opCodeData struct
 */
void freeOpCodeData(OpCodeData* opCode);

#endif //DISSASEMBLER_OPCODEDATA_H
