//
// Created by brandon on 10/28/15.
//

#ifndef DISSASEMBLER_MISCFUNCTIONS_H
#define DISSASEMBLER_MISCFUNCTIONS_H

#include <stdbool.h>
/***
 * Takes a binary string and returns the integer value
 */
int stringBinaryToInt(char* string, bool halfValue);

/***
 * Function returns the strings between the start and end indexes
 */
char* customSubString(unsigned short start, unsigned short end, char* inputString);

/***
 * Converts a Binary String to a decimal string
 */
char* convertBinToDecString(char* binaryString, bool halfValue);

#endif //DISSASEMBLER_MISCFUNCTIONS_H
