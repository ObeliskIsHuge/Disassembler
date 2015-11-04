//
// Created by brandon on 11/1/15.
//

#ifndef DISASSEMBLER_SYMBOLTABLE_H
#define DISASSEMBLER_SYMBOLTABLE_H

#include <stdio.h>

struct _Symbol{

    char* name;
    char* type;
    char* value;
    char* address;
};

typedef struct _Symbol Symbol;


/***
 * Creates a valid SymbolData
 */
void symbolInit(Symbol* symbol);

/***
 * Inserts a value to the table
 */
void insertValueToTable(char* value, char* address);

/***
 * Returns the symbol struct associated with the address
 */
Symbol* getSymbolByAddress(char* address);

/***
 * Prints the symbol table
 */
void printSymbolTable(FILE* outputFile);
#endif //DISASSEMBLER_SYMBOLTABLE_H
