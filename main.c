#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



int main(int argc , char* argv[]){


    // Checks to see a file has been passed to the program
    if(argc < 3 || argc > 4){
        perror("A file must be passed into this program for correct operation");
        return -1;
    }

    char*inputFileName = "";
    char*outputFileName = "";
    char*switchOption = "";
    bool executeSwitch = false;
    // Opens the passed in file

    // Checks to see if we're performing the normal operations
    if(argc == 3){

        inputFileName = argv[1];
        outputFileName = argv[2];
        switchOption = "-1";
    }
        // Prepare to print the symbol table
    else {

        switchOption = argv[1];
        inputFileName = argv[2];
        outputFileName = argv[3];
    }

    // Checks to see if we want to execute symbols instead
    if(strcmp(switchOption, "-symbols") == 0){
        executeSwitch = true;
    }


    FILE* inputFile = fopen(inputFileName , "r+");

    // Holds the file that will contain all the binary data
    FILE* outputFile = fopen(outputFileName, "w+");

    // Creates a file that is easier to parse
    FILE* cleanFile = createCleanedFile(inputFile);

    // Executes the commands from the cleaned file
    parseCleanedFile(cleanFile , outputFile, executeSwitch);

    // Close all opened files
    fclose(inputFile);
    fclose(cleanFile);
    fclose(outputFile);

    return 1;
}