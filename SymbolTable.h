//
// Created by brandon on 11/1/15.
//

#ifndef DISASSEMBLER_SYMBOLTABLE_H
#define DISASSEMBLER_SYMBOLTABLE_H


struct _SymbolTable{

    char* name;
    char* type;
    char* value;
    char* address;
};

typedef struct _SymbolTable SymbolTable;

/***
 * Creates a valid SymbolData
 */
void symbolTableInit(SymbolTable* table);

/***
 * Inserts a value to the table
 */
void insertValueToTable(char* value, char* address);

/***
 * Returns the symbol struct associated with the address
 */
SymbolTable* getSymbolByAddress(char* address);
#endif //DISASSEMBLER_SYMBOLTABLE_H
