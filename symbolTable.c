//
// Created by brandon on 11/1/15.
//

#include "symbolTable.h"
#include "fileProcessing.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 150

static int sizeOfSymbolArray = 0;

static Symbol symbolArray[30] = {

};



/***
 * Creates a valid SymbolData
 */
void symbolInit(Symbol* symbol){

    char nameArray[50];
    char typeArray[50];
    char valueArray[50];
    char addressArray[50];

    memset(nameArray, '\0', sizeof(nameArray));
    memset(typeArray, '\0', sizeof(typeArray));
    memset(valueArray, '\0', sizeof(valueArray));
    memset(addressArray, '\0', sizeof(addressArray));

    symbol->name = &nameArray[0];
    symbol->type = &typeArray[0];
    symbol->value = &valueArray[0];
    symbol->address = &addressArray[0];

}

/***
 * Inserts a value to the table
 */
void insertValueToTable(char* value, char* address){

    Symbol newTable;
    symbolInit(&newTable);

    sizeOfSymbolArray++;

    // handles the naming
    char* tempNameArray = (char *)calloc(100, sizeof(char *));
    strcpy(newTable.name, "V0");
    sprintf(tempNameArray, "%d", sizeOfSymbolArray);
    strcat(newTable.name, tempNameArray);
    strcat(newTable.name, ":");

    // copies over the type
    strcpy(newTable.type, ".word");

    // copies over the value
    strcpy(newTable.value, value);

    // copies over the address
    strcpy(newTable.address, address);

    free(tempNameArray);

    symbolArray[sizeOfSymbolArray] = newTable;

}


Symbol* getSymbolByAddress(char* address){

    // Iterates over the entire symbol array
    for(int i = 0; i <= sizeOfSymbolArray; i++){

        // will only be true if the addresses are equal
        if(strcmp(symbolArray[i].address, address) == 0){

            return &symbolArray[i];
        }
    }

    return NULL;
}


void printSymbolTable(FILE* outputFile){

    char line[MAX_LINE_SIZE];
    char* pLine = line;
    Symbol symbolAtIndex;

    // prints the .data text
    printToOutputFile(false, ".data\n", outputFile);

    // Iterates over the entire symbolArray
    for(unsigned int i = 0; i <= sizeOfSymbolArray; i++){

        symbolAtIndex = symbolArray[i];

        // builds and prints each line of the '.data' section
        strcat(pLine, symbolAtIndex.name);
        strcat(pLine, "\t\t");
        strcat(pLine, symbolAtIndex.type);
        strcat(pLine, " ");
        strcat(pLine, symbolAtIndex.value);
        strcat(pLine, "\n");
        printToOutputFile(false, pLine, outputFile);
    }

}