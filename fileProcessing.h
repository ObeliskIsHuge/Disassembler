//
// Created by brandon on 10/28/15.
//

#ifndef DISSASEMBLER_FILEPROCESSING_H
#define DISSASEMBLER_FILEPROCESSING_H

#include <stdio.h>


/**
 * Processes the text segment of the object file
 */
void parseTextSegment(FILE* inputFile, FILE* outputFile);


/**
* Processes the data segment of the object file
*/
void parseDataSegment(FILE* inputFile, FILE* outputFile);

#endif //DISSASEMBLER_FILEPROCESSING_H
