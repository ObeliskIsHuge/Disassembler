//
// Created by brandon on 10/28/15.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "fileProcessing.h"
#include "miscFunctions.h"
#include "opCodeData.h"
#include "registerData.h"
#include "labelStruct.h"


#define MAX_LINE_SIZE 150
#define DATA_SEGMENT_START 8192
#define WORD_SEGMENT_START 0
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2


void parseTextSegment(FILE* inputFile, FILE* outputFile, SymbolTable* symbolTable){

    char line[MAX_LINE_SIZE];
    char* pLine = line;
    // Declares variables that will be used to hold the bits
    char* opCode;
    char* rs;
    char* rt;
    char* rd;
    char* shamt;
    char* funct;
    char* sixteenImmediate;
    char* twoSixImmediate;
    long jumpAddress;
    char* jumpLabel;
    char printedStringArray[40];
    int currentLine = 0;
    char* label;
    char* printedString = (char *)calloc(100, sizeof(char *));
    char* syscall = "00000000000000000000000000001100\n";

    // declare structs that will be pointed to
    OpCodeData opCodeData;
    OpCodeData functData;
    RegisterData rsData;
    RegisterData rtData;
    RegisterData rdData;
    Symbol symbolData;
    LabelTable labelTable;
    bool variablesPrinted = false;

    // sturcts that will be used to hold to the register information
    OpCodeData* opCodeStruct = &opCodeData;
    OpCodeData* functStruct = &functData;
    RegisterData* rsStruct = &rsData;
    RegisterData* rtStruct = &rtData;
    RegisterData* rdStruct = &rdData;
    LabelTable* pLabelTable = &labelTable;
    Symbol* symbolValue = &symbolData;
    Symbol* beginningSymbol = *&symbolTable->table;

    // allocate the values
    opCodeInit(opCodeStruct);
    opCodeInit(functStruct);
    registerDataInit(rsStruct);
    registerDataInit(rtStruct);
    registerDataInit(rdStruct);
    labelTableInit(pLabelTable);
    symbolInit(symbolValue);

    // build the label table
    buildLabelTable(inputFile, *&pLabelTable);

    // return the input file to the beginning
    rewind(inputFile);
    // prints the '.text' section
    printToOutputFile(false, ".text\n", outputFile);
    printToOutputFile(false, "main:   ", outputFile);

    bool space = false;

    fgets(line, MAX_LINE_SIZE, inputFile);

    // Keeps running until the new line is found
    while(strcmp(pLine, "\n") != 0){


        // stop when we've reached the new line
        if(strcmp(pLine, "\n") == 0){
            break;
        }

        // checks to see if a label needs to be printed
        label = findLabelAtAddress(currentLine, pLabelTable);
        if(label != NULL){
            strcat(label, ":  ");
            printToOutputFile(false, label, outputFile);
            free(label);

        }
        opCode = customSubString(0 , 6 , pLine);
        FindOpCodeByBits(opCode,  opCodeStruct);
        free(opCode);

        // R-type instruction
        if(opCodeStruct->formatType == RTYPE){

            funct = customSubString(26 , 32, pLine);
            FindOpCodeByBits(funct, functStruct);
            free(funct);

            // checks to see if the command is syscall
            if(strcmp(pLine, syscall) == 0){

                strcpy(printedString, "syscall\n");
                printToOutputFile(space, printedString, outputFile);
                space = true;
                // isn't syscall
            } else {
                // handles rs info
                rs = customSubString(6 , 11, pLine);
                FindRegisterDataByBits(rs, rsStruct);
                free(rs);

                // handles rt info
                rt = customSubString(11 , 16, pLine);
                FindRegisterDataByBits(rt, rtStruct);
                free(rt);

                // handles rd info
                rd = customSubString(16 , 21, pLine);
                FindRegisterDataByBits(rd, rdStruct);
                free(rd);

                //TODO what to do here?
                shamt = customSubString(21 , 26, pLine);
                free(shamt);

                // Builds the string that will be printed
                strcat(printedString, functStruct->name);
                strcat(printedString, "    ");
                strcat(printedString, rdStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rsStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, "\n");

                // prints to output file
                printToOutputFile(space, printedString, outputFile);
                space = true;
                resetRegisterData(rsStruct);
                resetRegisterData(rtStruct);
                resetRegisterData(rdStruct);
            }

            resetOpCode(functStruct);
            // I-type instruction
        } else if (opCodeStruct->formatType == ITYPE){

            // checks to see if the instruction is 'addi'
            if(strcmp(opCodeStruct->name, "addi") == 0){

                // Gets the 'rs' register data
                rs = customSubString(6 , 11, pLine);
                FindRegisterDataByBits(rs, rsStruct);
                free(rs);

                // Gets the 'rt' register data
                rt = customSubString(11 , 16, pLine);
                FindRegisterDataByBits(rt, rtStruct);
                free(rt);

                // converts the immediate and gets it to a printable format
                sixteenImmediate = customSubString(16 , 32, pLine);
                char* sixteenBitString = convertBinToDecString(sixteenImmediate, false);
                free(sixteenImmediate);

                // builds the print string
                strcat(printedString, opCodeStruct->name);
                strcat(printedString, "   ");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rsStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, sixteenBitString);
                strcat(printedString, "\n");

                // frees the string
                free(sixteenBitString);
                resetRegisterData(rsStruct);
                resetRegisterData(rtStruct);

                // prints the string
                printToOutputFile(space, printedString, outputFile);
                space = true;
                // will be true when the instruction is 'beq'
            } else if(strcmp(opCodeStruct->name, "beq") == 0){

                // Gets the 'rs' register data
                rs = customSubString(6 , 11, pLine);
                FindRegisterDataByBits(rs, rsStruct);
                free(rs);

                // Gets the 'rt' register data
                rt = customSubString(11 , 16, pLine);
                FindRegisterDataByBits(rt, rtStruct);
                free(rt);

                // Gets the address that the 16-bit immediate references
                char* tempLabel = findLabelAtAddress(currentLine + 2, pLabelTable);
//                free(sixteenImmediate);

                strcat(printedString, opCodeStruct->name);
                strcat(printedString, "\t");
                strcat(printedString, rsStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, tempLabel);
                strcat(printedString, "\n");

                // prints to output file
                printToOutputFile(space, printedString, outputFile);
                space = true;

                // frees values
                free(tempLabel);
                resetRegisterData(rsStruct);
                resetRegisterData(rtStruct);
                symbolReset(symbolValue);

                // will be true when the command is 'lw' or 'sw'
            } else if (strcmp(opCodeStruct->name, "sw") == 0 || strcmp(opCodeStruct->name, "lw") == 0){

                long base;
                long newAddress;
                char* basePointer;
                variablesPrinted = true;

                // reads the 'base' value
                basePointer = customSubString(6 , 11, pLine);
                base = stringBinaryToInt(basePointer, false);
                free(basePointer);

                // reads the 'rt' Value
                rt = customSubString(11 , 16, pLine);
                FindRegisterDataByBits(rt, rtStruct);
                free(rt);

                // converts 16-bit and does the math to find the address
                sixteenImmediate = customSubString(16, 32, pLine);
                newAddress = stringBinaryToInt(sixteenImmediate, false) + base;
                char* addressString = (char *)calloc(100, sizeof(char *));
                sprintf(addressString, "%li", newAddress);
                free(sixteenImmediate);

                // Gets the address of the instruction
                getSymbolByAddress(addressString, symbolTable, symbolValue);

                strcat(printedString, opCodeStruct->name);
                strcat(printedString, "     ");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, symbolValue->name);
                strcat(printedString, "\n");

                printToOutputFile(space, printedString, outputFile);
                space = true;
                symbolTable->table = *&beginningSymbol;
                free(addressString);
                symbolReset(symbolValue);
                resetRegisterData(rtStruct);
            }

            // J-type instruction
        } else {
            twoSixImmediate = customSubString(6 , 32, pLine);
            jumpAddress = stringBinaryToInt(twoSixImmediate, false);
//            jumpAddress++;
            jumpLabel = findLabelAtAddress(jumpAddress, pLabelTable);

            strcat(printedString, opCodeStruct->name);
            strcat(printedString, "    ");
            strcat(printedString, jumpLabel);
            strcat(printedString, "\n");

            printToOutputFile(space, printedString, outputFile);
            space = true;
            free(twoSixImmediate);

        }

        // clear the arrays of previous data
        memset(line, '\0', sizeof(line));
        memset(printedString, '\0', sizeof(printedString));

        fgets(line, MAX_LINE_SIZE, inputFile);
        resetOpCode(opCodeStruct);
        currentLine++;
    }


    printToOutputFile(false, "\n", outputFile);
    symbolTable->table = *&beginningSymbol;
//    labelTableFree(pLabelTable); TODO fix this when done
    // free all the structs
    freeOpCodeData(opCodeStruct);
    freeOpCodeData(functStruct);
    freeRegisterDataStruct(rsStruct);
    freeRegisterDataStruct(rtStruct);
    freeRegisterDataStruct(rdStruct);
    symbolFree(symbolValue);
    free(printedString);

    // prints the symbol table
    printSymbolTable(outputFile, symbolTable, variablesPrinted);
    symbolTable->table = *&beginningSymbol;

    freeSymbolTable(symbolTable);

}


void buildLabelTable(FILE* inputFile, LabelTable* labelTable){

    char line[MAX_LINE_SIZE];
    char* pLine = &line[0];
    int address = WORD_SEGMENT_START;
    long jumpAddress;
    char* opCode;
    char* jumpBits;
    char* nameString = (char *)calloc(100, sizeof(char *));

    OpCodeData opCodeData;
    OpCodeData* opCodeStruct = &opCodeData;
    opCodeInit(opCodeStruct);

    //  keeps running until the end of the file is found
    while(!feof(inputFile)){

        memset(line, '\0', sizeof(line));
        memset(nameString, '\0', sizeof(nameString));
        fgets(line, MAX_LINE_SIZE, inputFile);


        // break the loop if we process a new line character or a blank line
        if(strcmp(pLine, "\n") == 0 || strcmp(pLine, "") == 0){
            break;
        }

        opCode = customSubString(0 , 6 , pLine);
        FindOpCodeByBits(opCode,  opCodeStruct);
        free(opCode);

        // will be true when the instruction is a jump
        if(strcmp(opCodeStruct->name,"j") == 0){

            char* tempNameArray = (char *)calloc(100, sizeof(char *));
            labelTable->size++;
            jumpBits = customSubString(6 , 32, pLine);
            jumpAddress = stringBinaryToInt(jumpBits, false);
            strcpy(nameString, "L0");
            sprintf(tempNameArray, "%d", labelTable->size);
            strcat(nameString, tempNameArray);

            insertToLabelTable(nameString, jumpAddress, *&labelTable);
            free(tempNameArray);
            // will be true when the current command is beq
        } else if (strcmp(opCodeStruct->name, "beq") == 0){

            char* tempNameArray = (char *)calloc(100, sizeof(char *));
            labelTable->size++;
            strcpy(nameString, "L0");
            sprintf(tempNameArray, "%d", labelTable->size);
            strcat(nameString, tempNameArray);
            insertToLabelTable(nameString, address + 2, *&labelTable);
            free(tempNameArray);

        }
        address++;
    }

    freeOpCodeData(opCodeStruct);
    free(nameString);
}


void parseDataSegment(FILE* inputFile, SymbolTable* symbolTable){

    char line[MAX_LINE_SIZE];
    char* pLine = &line[0];
    char printedStringArray[40];
    char* printedString = &printedStringArray[0];
    int currentAddress = DATA_SEGMENT_START;
    char nameArray[50];
    char* tempNameArray = &nameArray[50];
    char* lineValue;

    fgets(line, MAX_LINE_SIZE, inputFile);
    memset(tempNameArray, '\0', sizeof(tempNameArray));

    // Keeps running until a new line is found
    while(strcmp(pLine, "\n") != 0){
        // clear line array for new value
        memset(line, '\0', sizeof(line));
        fgets(line, MAX_LINE_SIZE, inputFile);
    }

    while(!feof(inputFile)){

        // clear the arrays of previous data
        memset(line, '\0', sizeof(line));
        memset(printedStringArray, '\0', sizeof(printedStringArray));

        fgets(line, MAX_LINE_SIZE, inputFile);

        // break the loop if we process a new line character or a blank line
        if(strcmp(pLine, "\n") == 0 || strcmp(pLine, "") == 0){
            break;
        }

        // converts the binary string to a decimal string
        lineValue = convertBinToDecString(pLine, true);

        sprintf(tempNameArray, "%d", currentAddress);

        // inserts the value to the symbol table
        insertValueToTable(lineValue, tempNameArray, symbolTable);

        // move back to the beginning
        for(int i = 1; i < symbolTable->size; i++){
            symbolTable->table--;
        }
        free(lineValue);

        currentAddress += 4;
        memset(tempNameArray, '\0', sizeof(tempNameArray));
    }
}



void printToOutputFile(bool includeSpace , char* outputString, FILE* outputFile){

    char* printString = (char *)calloc(100, sizeof(char *));

    // adds space if true
    if(includeSpace){
        strcpy(printString, "        ");

    }

    strcat(printString, outputString);
    fprintf(outputFile , "%s" , printString);

    free(printString);
}