OBJECTS =  main.c fileProcessing.c miscFunctions.c opCodeData.c registerData.c
CC = gcc
CFLAGS = -std=c99 

# Full program
 disassembler: $(OBJECTS) 
	 $(CC) $(CFLAGS) -g -o disassem $(OBJECTS)
