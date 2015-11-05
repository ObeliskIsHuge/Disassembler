//
// Created by brandon on 10/28/15.
//

#ifndef DISSASEMBLER_FILEPROCESSING_H
#define DISSASEMBLER_FILEPROCESSING_H

#include <stdio.h>
#include <stdbool.h>
#include "symbolTable.h"

/**
 * Processes the text segment of the object file
 */
void parseTextSegment(FILE* inputFile, FILE* outputFile, SymbolTable* symbolTable);


/**
* Processes the data segment of the object file
*/
void parseDataSegment(FILE* inputFile, SymbolTable* symbolTable);

/***
 * Accepts a string and prints to the output file
 */
void printToOutputFile(bool includeSpace , char* string, FILE* outputFile);

#endif //DISSASEMBLER_FILEPROCESSING_H
