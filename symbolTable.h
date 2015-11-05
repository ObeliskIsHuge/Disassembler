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


struct _SymbolTable{
    int size;
    Symbol* table;
};

typedef struct _SymbolTable SymbolTable;

/***
 * Creates a valid Symbol
 */
void symbolInit(Symbol* symbol);

/**
 * Resets the arrays in the symbol
 */
void symbolReset(Symbol* symbol);

/***
 * Creates a Valid Symbol Table
 */
void symbolTableInit(SymbolTable* symbolTable);

/***
 * Inserts a value to the table
 */
void insertValueToTable(char* value, char* address, SymbolTable* symbolTable);

/***
 * Makes a deep copy of the symbol to the symbol Table
 */
void copySymbolToTable(Symbol* symbol, SymbolTable* symbolTable);

/**
 * Performs a deep copy of a symbol to another symbol
 */
void symbolCopy(Symbol* destSymbol, Symbol* copySymbol);

/***
 * Frees symbol struct
 */
void symbolFree(Symbol* symbol);

/***
 * Returns the symbol struct associated with the address
 */
Symbol* getSymbolByAddress(char* address, SymbolTable* symbolTable);

/***
 * Prints the symbol table
 */
void printSymbolTable(FILE* outputFile, SymbolTable* symbolTable);

/***
 * Frees the values of the Symbol table
 */
void freeSymbolTable(SymbolTable* symbolTable);
#endif //DISASSEMBLER_SYMBOLTABLE_H
