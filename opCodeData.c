//
// Created by brandon on 10/28/15.
//

#include "opCodeData.h"
#include <string.h>
#include <stdlib.h>

#define OPCODETABLESIZE 50
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2
#define OPCODEFIELDSIZE 6
#define OPCODENAMESIZE 5
//TODO blez and bltz
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
        {"100000", "lb", ITYPE},
        {"010000", "mfhi", RTYPE},
        {"010010", "mflo", RTYPE},
        {"011000", "mult", RTYPE},
        {"100100", "and", RTYPE},
        {"001100", "syscall", RTYPE},
        {"011010", "div", RTYPE},
        {"101011", "sw", ITYPE},
        {"100000", "add", RTYPE},
        {"001001", "addiu", ITYPE},

};


void opCodeInit(OpCodeData* opCodeData){

    opCodeData->name = (char *)calloc(100, sizeof(char *));
    opCodeData->bits = (char *)calloc(100, sizeof(char *));
    opCodeData->formatType = -1;
}


void FindOpCodeByBits(char* bits, OpCodeData* opCodeData){

    for(unsigned int i = 0; i < OPCODETABLESIZE; i++){

        if(strcmp(opCodeTable[i].bits, bits) == 0){

            OpCodeData foundOpCode = opCodeTable[i];

            // copies over the data
            strcpy(opCodeData->bits, foundOpCode.bits);
            strcpy(opCodeData->name, foundOpCode.name);

            // copies over the format type
            opCodeData->formatType = foundOpCode.formatType;
            break;
        }
    }
}


void resetOpCode(OpCodeData* opCode){

    memset(opCode->bits, 0 , sizeof(opCode->bits));
    memset(opCode->name, 0 , sizeof(opCode->name));
    opCode->formatType = -1;
}

void freeOpCodeData(OpCodeData* opCode){

    free(opCode->bits);
    free(opCode->name);
}