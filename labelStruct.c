//
// Created by brandon on 11/6/15.
//

#include <stdlib.h>
#include "labelStruct.h"

/***
 * Creates a valid LabelData struct
 */
void labelDataInit(LabelData* labelData){

    labelData->labelName = (char *)calloc(100, sizeof(char *));
    labelData->address = -1;
}

/***
 * Frees the data in a LabelData struct
 */
void labelDataFree(LabelData* labelData){

    free(labelData->labelName);
}
