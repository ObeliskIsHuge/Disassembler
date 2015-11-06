//
// Created by brandon on 11/6/15.
//

#include <stdlib.h>
#include <string.h>
#include "labelTable.h"


void labelTableInit(LabelTable* labelTable){

    labelTable->table = (LabelData *)malloc(100 * sizeof(LabelData *));
    labelTable->addresses = (int *)malloc(100 * sizeof(int *));
    labelTable->size = 0;
}

/***
 * Frees a label table
 */
void labelTableFree(LabelTable* labelTable){

    free(labelTable->table);
    free(labelTable->addresses);
}

/***
 * Inserts a label into the table
 */
void insertToLabelTable(char* labelName, int address, LabelTable* labelTable){

    // increment to the next empty value
    for(int i = 0; i < labelTable->size; i++){
        labelTable->table++;
        labelTable->addresses++;
    }

    labelTable->table->labelName = (char *)calloc(100, sizeof(char *));
    labelTable->size++;
    strcpy(labelTable->table->labelName, labelName);
    *labelTable->addresses =address;
    labelTable->table->address = address;
}