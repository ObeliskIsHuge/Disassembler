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


    int distance = 0;
    // increment to the next empty value
    for(int i = 1; i < labelTable->size; i++){
        labelTable->table++;
        labelTable->addresses++;
        distance++;
    }

    labelTable->table->labelName = (char *)calloc(100, sizeof(char *));
    strcpy(labelTable->table->labelName, labelName);
    *labelTable->addresses = address;
    labelTable->table->address = address;

    // moves the pointers back
    for(int i = 0; i < distance; i++){
        labelTable->table--;
        labelTable->addresses--;
    }
}

char* findLabelAtAddress(int labelAddress, LabelTable* labelTable){

    int distance = 0;
    char* returnString = (char *)calloc(100, sizeof(char *));

    for(int i = 0; i < labelTable->size; i++){
        // will be true when the addresses are equal
        if(labelTable->table->address == labelAddress){
            strcpy(returnString, labelTable->table->labelName);
            // return to the beginning of the array
            for(int i = 0; i < distance; i++){
                labelTable->table--;
            }
            return returnString;
        }

        labelTable->table++;
        distance++;
    }

    // return to the beginning of the array
    for(int i = 0; i < distance; i++){
        labelTable->table--;
    }

    free(returnString);
    return NULL;
}