//
// Created by brandon on 10/28/15.
//

#include "opCodeData.h"
#include <string.h>
#include <stdlib.h>

#define OPCODETABLESIZE 12
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2
#define OPCODEFIELDSIZE 6
#define OPCODENAMESIZE 5

OpCodeData opCodeTable[OPCODETABLESIZE] = {

        {"000000", "n/a", RTYPE},
        {"000001", "bltz", ITYPE},
        {"001010", "slti", ITYPE},
        {"000100", "beq", ITYPE},
        {"001100", "andi", ITYPE},
        {"000101", "bne", ITYPE},
        {"001111", "lui", ITYPE},
        {"000110", "blez", ITYPE},
        {"100011", "lw", ITYPE},
        {"001000", "addi", ITYPE},
        {"101011", "sw", ITYPE},
        {"001001", "addiu", ITYPE},

};



OpCodeData* FindOpCodeByBits(char* bits){

    for(unsigned int i = 0; i < OPCODETABLESIZE; i++){

        if(strcmp(opCodeTable[i].bits, bits) == 0){

            OpCodeData foundOpCode = opCodeTable[i];
            OpCodeData returnOpCode;

            // arrays will hold the used data
            char registerBits[OPCODEFIELDSIZE];
            char registerName[OPCODENAMESIZE];

            // points to the used data
            returnOpCode.bits = &registerBits[0];
            returnOpCode.name = &registerName[0];

            // copies over the data
            strcpy(returnOpCode.bits, foundOpCode.bits);
            strcpy(returnOpCode.name, foundOpCode.name);

            OpCodeData* returnPointer = &returnOpCode;

            return returnPointer;

//            returnOpCode.bits = (char *)calloc(7, sizeof(char));
//
//            resetPointerOne = returnOpCode.bits;
//            resetPointerTwo = foundOpCode.bits;
//            // copies over the bit values
//            for(unsigned int i = 0; i < 6; i++){
//                *returnOpCode.bits = *foundOpCode.bits;
//                returnOpCode.bits++;
//                foundOpCode.bits++;
//            }
//
//            returnOpCode.bits = resetPointerOne;
//            foundOpCode.bits = resetPointerTwo;
//
//
//            returnOpCode.name = (char *)calloc(7, sizeof(char));
////            int arraySize = sizeof(foundOpCode.name) / sizeof(char *);
//            int arraySize = strlen(foundOpCode.name);
//
//            resetPointerOne = returnOpCode.name;
//            resetPointerTwo = foundOpCode.name;
//            // copies over the name
//            for(unsigned int i = 0; i < arraySize; i++){
//                *returnOpCode.name = *foundOpCode.name;
//                returnOpCode.name++;
//                foundOpCode.name++;
//            }
//            returnOpCode.name = resetPointerOne;
//            foundOpCode.name = resetPointerTwo;
//
//            // copies over the format type
//            returnOpCode.formatType = foundOpCode.formatType;
//
//            OpCodeData * returnPointer = &returnOpCode;
//            return returnPointer;
        }
    }

    return NULL;

}

void freeOpCodeData(OpCodeData* opCode){

    free(opCode->bits);
    free(opCode->name);
}