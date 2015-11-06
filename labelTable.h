//
// Created by brandon on 11/6/15.
//

#ifndef DISASSEMBLER_LABELTABLE_H
#define DISASSEMBLER_LABELTABLE_H

#include "labelStruct.h"

struct _labelTable{

    LabelData* labelTable;
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
void insertToLabelTable(LabelData* labelData, LabelTable* labelTable);
#endif //DISASSEMBLER_LABELTABLE_H
