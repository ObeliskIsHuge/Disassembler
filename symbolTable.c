//
// Created by brandon on 11/1/15.
//

#include "symbolTable.h"
#include "fileProcessing.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 150


/***
 * Creates a valid SymbolData
 */
void symbolInit(Symbol* symbol){

    symbol->name = (char *)calloc(100, sizeof(char *));
    symbol->type = (char *)calloc(100, sizeof(char *));
    symbol->value = (char *)calloc(100, sizeof(char *));
    symbol->address = (char *)calloc(100, sizeof(char *));

}

void symbolFree(Symbol* symbol){

    free(symbol->type);
    free(symbol->name);
    free(symbol->value);
    free(symbol->address);
}


void symbolTableInit(SymbolTable* symbolTable){

    symbolTable->table = (Symbol *)malloc(100 * sizeof(Symbol *));
    symbolTable->size = 0;
}

/***
 * Inserts a value to the table
 */
void insertValueToTable(char* value, char* address, SymbolTable* symbolTable){

    Symbol newSymbol;
    symbolInit(&newSymbol);

    // increment to the next empty value
    for(int i = 0; i < symbolTable->size; i++){
        symbolTable->table++;
    }

    // handles the naming
    char* tempNameArray = (char *)calloc(100, sizeof(char *));
    symbolTable->size++;
    strcpy(newSymbol.name, "V0");
    sprintf(tempNameArray, "%d", symbolTable->size);
    strcat(newSymbol.name, tempNameArray);
    strcat(newSymbol.name, ":");

    // copies over the type
    strcpy(newSymbol.type, ".word");

    // copies over the value
    strcpy(newSymbol.value, value);

    // copies over the address
    strcpy(newSymbol.address, address);
    copySymbolToTable(&newSymbol, symbolTable);

    free(tempNameArray);
    symbolFree(&newSymbol);

}



void copySymbolToTable(Symbol* symbol, SymbolTable* symbolTable){

    symbolInit(symbolTable->table);
    strcpy(symbolTable->table->name, symbol->name);
    strcpy(symbolTable->table->value, symbol->value);
    strcpy(symbolTable->table->type, symbol->type);
    strcpy(symbolTable->table->address, symbol->address);
}


Symbol* getSymbolByAddress(char* address, SymbolTable* symbolTable){

    // Iterates over the entire symbol array
    for(int i = 0; i <= symbolTable->size; i++){

        // will only be true if the addresses are equal
        if(strcmp(symbolTable->table->address, address) == 0){
//            Symbol symbol;
//            symbolInit(&symbol);
//            symbolCopy(&symbol, symbolTable->table);

            return *&symbolTable->table;
        }
        symbolTable->table++;
    }

    return NULL;
}


void symbolCopy(Symbol* destSymbol, Symbol* copySymbol){

    strcpy(destSymbol->type, copySymbol->type);
    strcpy(destSymbol->address, copySymbol->address);
    strcpy(destSymbol->name, copySymbol->name);
    strcpy(destSymbol->value, copySymbol->value);
}


void printSymbolTable(FILE* outputFile, SymbolTable* symbolTable){

    char line[MAX_LINE_SIZE];
    char* pLine = line;
    Symbol symbolAtIndex;

    // prints the .data text
    printToOutputFile(false, ".data\n", outputFile);

    // Iterates over the entire symbolArray
    for(unsigned int i = 0; i < symbolTable->size; i++){

        symbolAtIndex = *symbolTable->table;

        // builds and prints each line of the '.data' section
        strcat(pLine, symbolAtIndex.name);
        strcat(pLine, "\t\t");
        strcat(pLine, symbolAtIndex.type);
        strcat(pLine, " ");
        strcat(pLine, symbolAtIndex.value);
        strcat(pLine, "\n");
        printToOutputFile(false, pLine, outputFile);

        symbolTable->table++;
    }

}


void freeSymbolTable(SymbolTable* symbolTable){

    Symbol* symbol;
    // iterates over the entire array deallocating values
    for(int i = 0; i < symbolTable->size; i++){

        symbol = *&symbolTable->table;
        symbolFree(symbol);
        symbolTable->table++;
    }

    // Goes back to the beginning
    for(int i = 0; i < symbolTable->size; i++){
        symbolTable->table--;
    }

    free(symbolTable->table);
}