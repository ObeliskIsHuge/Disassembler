//
// Created by brandon on 10/28/15.
//

#include <stdlib.h>
#include <string.h>

#include "fileProcessing.h"
#include "miscFunctions.h"
#include "opCodeData.h"
#include "registerData.h"


#define MAX_LINE_SIZE 150
#define DATA_SEGMENT_START 8192
#define WORD_SEGMENT_START 0
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2
enum printType{data , text};


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
    OpCodeData* opCodeStruct;


    RegisterData* registerStruct;

    // reads entire input file
    while(!feof(inputFile)){


        fgets(line, MAX_LINE_SIZE, inputFile);

        opCode = customSubString(0 , 5 , pLine);
        opCodeStruct = FindOpCodeByBits(opCode);

        // R-type instruction
        if(opCodeStruct->formatType == RTYPE){

            funct = customSubString(26 , 31, pLine);
            OpCodeData* functStruct = FindOpCodeByBits(funct);

            // checks to see if the command is syscall
            if(strcmp(functStruct->name, "syscall") == 0){

                strcpy(printedString, "0000000000000000000000000");
                strcat(printedString , functStruct->bits);
                printedStringArray[32] = '\n';

                printToOutputFile(true, printedString, outputFile);
                // isn't syscall
            } else {
                rs = customSubString(6 , 10, pLine);
                rt = customSubString(11 , 15, pLine);
                rd = customSubString(16 , 20, pLine);
                shamt = customSubString(21 , 25, pLine);
            }



            // I-type instruction
        } else if (opCodeStruct->formatType == ITYPE){

            rs = customSubString(6 , 10, pLine);
            rt = customSubString(11 , 15, pLine);
            sixteenImmediate = customSubString(16 , 31, pLine);



            // J-type instruction
        } else {

            twoSixImmediate = customSubString(6 , 31, pLine);

        }


    }

}


void parseDataSegment(FILE* inputFile, FILE* outputFile){

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