//
// Created by brandon on 10/28/15.
//

#ifndef DISSASEMBLER_MISCFUNCTIONS_H
#define DISSASEMBLER_MISCFUNCTIONS_H

#include <inttypes.h>

/***
 * Takes a binary string and returns the integer value
 */
int16_t stringBinaryToInt(char* string);

/***
 * Function returns the strings between the start and end indexes
 */
char* customSubString(unsigned short start, unsigned short end, char* inputString);

#endif //DISSASEMBLER_MISCFUNCTIONS_H
