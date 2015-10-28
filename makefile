OBJECTS =  main.c data.c iFormat.c lineDestruct.c registers.c rFormat.c symbols.c fileProcessing.c
CC = gcc
CFLAGS = -std=c99 

# Full program
 disassembler: $(OBJECTS) 
	 $(CC) $(CFLAGS) -g -o disassem $(OBJECTS)
