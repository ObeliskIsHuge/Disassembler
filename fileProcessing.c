//
// Created by brandon on 10/28/15.
//

#include <stdlib.h>
#include <string.h>

#include "fileProcessing.h"
#include "miscFunctions.h"
#include "opCodeData.h"
#include "registerData.h"
#include "symbolTable.h"


#define MAX_LINE_SIZE 150
#define DATA_SEGMENT_START 8192
#define WORD_SEGMENT_START 0
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2


void parseTextSegment(FILE* inputFile, FILE* outputFile){

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
    char printedStringArray[40];
    char* printedString = &printedStringArray[0];

    // sturcts that will be used to hold to the register information
    OpCodeData* opCodeStruct;
    OpCodeData* functStruct;
    RegisterData* rsStruct;
    RegisterData* rtStruct;
    RegisterData* rdStruct;
    Symbol* symbolValue;

    // prints the '.text' section
    printToOutputFile(false, ".text", outputFile);
    printToOutputFile(false, "main:\t", outputFile);

    fgets(line, MAX_LINE_SIZE, inputFile);

    // Keeps running until the new line is found
    while(strcmp(pLine, "\n") != 0){


        // stop when we've reached the new line
        if(strcmp(pLine, "\n") == 0){
            break;
        }

        opCode = customSubString(0 , 6 , pLine);
        opCodeStruct = FindOpCodeByBits(opCode);

        // R-type instruction
        if(opCodeStruct->formatType == RTYPE){

            funct = customSubString(26 , 31, pLine);
            functStruct = FindOpCodeByBits(funct);

            // checks to see if the command is syscall
            if(strcmp(functStruct->name, "syscall") == 0){

                strcpy(printedString, "syscall\n");
                printedStringArray[32] = '\n';

                printToOutputFile(true, printedString, outputFile);
                // isn't syscall
            } else {
                // handles rs info
                rs = customSubString(6 , 10, pLine);
                rsStruct = FindRegisterDataByBits(rs);

                // handles rt info
                rt = customSubString(10 , 15, pLine);
                rtStruct = FindRegisterDataByBits(rt);

                // handles rd info
                rd = customSubString(15 , 20, pLine);
                rdStruct = FindRegisterDataByBits(rd);

                //TODO what to do here?
                shamt = customSubString(20 , 25, pLine);

                // Builds the string that will be printed
                strcat(printedString, functStruct->name);
                strcat(printedString, "\t");
                strcat(printedString, rdStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rsStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, "\n");

                // prints to output file
                printToOutputFile(false, printedString, outputFile);
            }
            // I-type instruction
        } else if (opCodeStruct->formatType == ITYPE){

            // checks to see if the instruction is 'addi'
            if(strcmp(opCodeStruct->name, "addi") == 0){

                // Gets the 'rs' register data
                rs = customSubString(6 , 12, pLine);
                rsStruct = FindRegisterDataByBits(rs);

                // Gets the 'rt' register data
                rt = customSubString(12 , 16, pLine);
                rtStruct = FindRegisterDataByBits(rt);

                // converts the immediate and gets it to a printable format
                sixteenImmediate = customSubString(16 , 32, pLine);
                char* sixteenBitString = convertBinToDecString(sixteenImmediate);

                // builds the print string
                strcat(printedString, opCodeStruct->name);
                strcat(printedString, "\t");
                strcat(printedString, rsStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, sixteenBitString);
                strcat(printedString, "\n");

                // frees the string
                free(sixteenBitString);

                // prints the string
                printToOutputFile(false, printedString, outputFile);
                // will be true when the instruction is 'beq'
            } else if(strcmp(opCodeStruct->name, "beq") == 0){

                // Gets the 'rs' register data
                rs = customSubString(6 , 11, pLine);
                rsStruct = FindRegisterDataByBits(rs);

                // Gets the 'rt' register data
                rt = customSubString(11 , 16, pLine);
                rtStruct = FindRegisterDataByBits(rt);

                sixteenImmediate = customSubString(16, 32, pLine);

                // Gets the address that the 16-bit immediate references
                char* tempAddress = convertBinToDecString(sixteenImmediate);

                symbolValue = getSymbolByAddress(tempAddress);

                strcat(printedString, opCodeStruct->name);
                strcat(printedString, "\t");
                strcat(printedString, rsStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, symbolValue->name);

                // prints to output file
                printToOutputFile(false, printedString, outputFile);

                // will be true when the command is 'lw' or 'sw'
            } else if (strcmp(opCodeStruct->name, "sw") == 0 || strcmp(opCodeStruct->name, "lw") == 0){

                int base;
                int newAddress;
                char* basePointer;

                // reads the 'base' value
                basePointer = customSubString(6 , 11, pLine);
                base = stringBinaryToInt(basePointer);

                // reads the 'rt' Value
                rt = customSubString(11 , 16, pLine);
                rtStruct = FindRegisterDataByBits(rt);

                // converts 16-bit and does the math to find the address
                sixteenImmediate = customSubString(16, 32, pLine);
                newAddress = stringBinaryToInt(sixteenImmediate) + base;
                char* addressString = (char *)calloc(100, sizeof(char *));
                sprintf(addressString, "%d", newAddress);

                // Gets the address of the instruction
                symbolValue = getSymbolByAddress(addressString);

                strcat(printedString, opCodeStruct->name);
                strcat(printedString, "\t");
                strcat(printedString, rtStruct->registerName);
                strcat(printedString, ", ");
                strcat(printedString, symbolValue->name);
                strcat(printedString, "\n");

                printToOutputFile(false, printedString, outputFile);

                free(addressString);
            }

            // J-type instruction
        } else {

            twoSixImmediate = customSubString(6 , 32, pLine);

        }

        // clear the arrays of previous data
        memset(line, '\0', sizeof(line));
        memset(printedStringArray, '\0', sizeof(printedStringArray));

        fgets(line, MAX_LINE_SIZE, inputFile);
    }

}


void parseDataSegment(FILE* inputFile){

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

        // break the loop if we process a new line character
        if(strcmp(pLine, "\n") == 0){
            break;
        }

        // converts the binary string to a decimal string
        lineValue = convertBinToDecString(pLine);

        sprintf(tempNameArray, "%d", currentAddress);

        // inserts the value to the symbol table
        insertValueToTable(lineValue, tempNameArray);

        currentAddress += 4;
        memset(tempNameArray, '\0', sizeof(tempNameArray));
    }

}



void printToOutputFile(bool includeSpace , char* outputString, FILE* outputFile){

    char* printString = (char *)calloc(100, sizeof(char *));

    // adds space if true
    if(includeSpace){
        strcpy(printString, "\t\t");

    }

    strcat(printString, outputString);
    fprintf(outputFile , "%s" , printString);

    free(printString);
}