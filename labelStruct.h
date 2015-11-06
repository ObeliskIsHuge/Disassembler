//
// Created by brandon on 11/6/15.
//

#ifndef DISASSEMBLER_LABELSTRUCT_H
#define DISASSEMBLER_LABELSTRUCT_H


struct _labelData{

    char* labelName;
    int address;
};

typedef struct _labelData LabelData;

/***
 * Creates a valid LabelData struct
 */
void labelDataInit(LabelData* labelData);

/***
 * Frees the data in a LabelData struct
 */
void labelDataFree(LabelData* labelData);
#endif //DISASSEMBLER_LABELSTRUCT_H
