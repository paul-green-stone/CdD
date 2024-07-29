# C compiler
CC := gcc

# Debugging included `-g`
CFLAGS := -g

# Extra layer of protection
ALL_CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic-errors -O2

# Executable file name
SAVE := save.out

# Executable file name
LOAD := load.out

# ================================================================ #

# Building the executable with a static library
save: save.c
	$(CC) $(ALL_CFLAGS) -o $(SAVE) $^ ../../libCDict.a
    

# Building the executable with a static library
load: load.c
	$(CC) $(ALL_CFLAGS) -o $(LOAD) $^ ../../libCDict.a

# ================================================================ #

# Executing the commands regardless of whether a file named clean exists or not
.PHONY: clean

clean:
	rm -rf ./*.a ./*.o ./*.out
