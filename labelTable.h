//
// Created by brandon on 11/6/15.
//

#ifndef DISASSEMBLER_LABELTABLE_H
#define DISASSEMBLER_LABELTABLE_H

#include "labelStruct.h"

struct _labelTable{

    LabelData* table;
    int size;
    int* addresses;
};


typedef struct _labelTable LabelTable;

/**
 * Creates a valid LabelTable
 */
void labelTableInit(LabelTable* labelTable);

/***
 * Frees a label table
 */
void labelTableFree(LabelTable* labelTable);

/***
 * Inserts a label into the table
 */
void insertToLabelTable(char* labelName, int address, LabelTable* labelTable);

/***
 * Finds the label at the given address
 */
char * findLabelAtAddress(int labelAddress, LabelTable* labelTable);
#endif //DISASSEMBLER_LABELTABLE_H
