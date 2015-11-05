//
// Created by brandon on 10/28/15.
//

#include "opCodeData.h"
#include <string.h>
#include <stdlib.h>

#define OPCODETABLESIZE 20
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2
#define OPCODEFIELDSIZE 6
#define OPCODENAMESIZE 5

static OpCodeData opCodeTable[OPCODETABLESIZE] = {

        {"000000", "n/a", RTYPE},
        {"000001", "bltz", ITYPE},
        {"001010", "slti", ITYPE},
        {"000100", "beq", ITYPE},
        {"001100", "andi", ITYPE},
        {"000101", "bne", ITYPE},
        {"001111", "lui", ITYPE},
        {"000110", "blez", ITYPE},
        {"100011", "lw", ITYPE},
        {"000010", "j", JTYPE},
        {"100010", "sub", RTYPE},
        {"001000", "addi", ITYPE},
        {"001100", "syscall", RTYPE},
        {"101011", "sw", ITYPE},
        {"100000", "add", RTYPE},
        {"001001", "addiu", ITYPE},

};


void opCodeInit(OpCodeData* opCodeData){

    opCodeData->name = (char *)calloc(100, sizeof(char *));
    opCodeData->bits = (char *)calloc(100, sizeof(char *));
    opCodeData->formatType = -1;
}


OpCodeData* FindOpCodeByBits(char* bits){

    for(unsigned int i = 0; i < OPCODETABLESIZE; i++){

        if(strcmp(opCodeTable[i].bits, bits) == 0){

            OpCodeData foundOpCode = opCodeTable[i];
            OpCodeData returnOpCode;
            opCodeInit(&returnOpCode);

            // copies over the data
            strcpy(returnOpCode.bits, foundOpCode.bits);
            strcpy(returnOpCode.name, foundOpCode.name);

            // copies over the format type
            returnOpCode.formatType = foundOpCode.formatType;

            OpCodeData* returnPointer = &returnOpCode;

            return returnPointer;
        }
    }

    return NULL;

}

void freeOpCodeData(OpCodeData* opCode){

    free(opCode->bits);
    free(opCode->name);
}