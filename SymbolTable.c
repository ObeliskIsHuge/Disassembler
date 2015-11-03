//
// Created by brandon on 11/1/15.
//

#include "SymbolTable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZEOFSYMBOLARRAY 0

static SymbolTable symbolArray[30] = {

};



/***
 * Creates a valid SymbolData
 */
void symbolTableInit(SymbolTable* symbol){

    char nameArray[50];
    char typeArray[50];
    char valueArray[50];
    char addressArray[50];

    symbol->name = &nameArray[0];
    symbol->type = &typeArray[0];
    symbol->value = &valueArray[0];
    symbol->address = &addressArray[0];

}

/***
 * Inserts a value to the table
 */
void insertValueToTable(char* value, char* address){

    SymbolTable newTable;
    symbolTableInit(&newTable);

    // handles the naming
    char* tempNameArray = (char *)calloc(100, sizeof(char *));
    strcat(newTable.name, "V0");
    sprintf(tempNameArray, "%d", SIZEOFSYMBOLARRAY);
    strcat(newTable.name, tempNameArray);

    // copies over the type
    strcpy(newTable.type, ".word");

    // copies over the value
    strcpy(newTable.value, value);

    // copies over the address
    strcpy(newTable.address, address);

    free(tempNameArray);

    symbolArray[SIZEOFSYMBOLARRAY] = newTable;

    SIZEOFSYMBOLARRAY = SIZEOFSYMBOLARRAY + 1;

}


SymbolTable* getSymbolByAddress(char* address){

    // Iterates over the entire symbol array
    for(int i = 0; i <= SIZEOFSYMBOLARRAY; i++){

        // will only be true if the addresses are equal
        if(strcmp(symbolArray[i].address, address) == 0){

            return &symbolArray[i];
        }
    }

    return NULL;
}