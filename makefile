OBJECTS =  main.c fileProcessing.c miscFunctions.c opCodeData.c registerData.c symbolTable.c labelStruct.c labelTable.c
CC = gcc
CFLAGS = -std=c99 -g -o

# Full program
 disassembler: $(OBJECTS) 
	 $(CC) $(CFLAGS) disassem $(OBJECTS)
