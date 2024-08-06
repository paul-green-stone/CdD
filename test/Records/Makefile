# ================================================================ #
# ========================== VARIABLES =========================== #
# ================================================================ #

# Object files location. Object files will be placed in this directory during compilation
OBJDIR := objects

# Executable files location
BINS := bin

# Full names of object files
OBJECTS	:= $(addprefix $(OBJDIR)/, Record.o)

# C compiler
CC := gcc

# Debugging included `-g`
CFLAGS := -g

# Extra layer of protection
ALL_CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic-errors -O2

# ================================================================ #
# ============================ SOURCE ============================ #
# ================================================================ #

# Setting the value of the variable COUNTRY to the path of the `country.c`
COUNTRY := $(addprefix source/, Record.c)
    
# ================================================================ #
# =========================== TARGETS ============================ #
# ================================================================ #

# Create an object file by default
all: $(OBJECTS)

test: $(OBJECTS)

radd: $(OBJECTS)

rload: $(OBJECTS)

rsrh: $(OBJECTS)

rrm: $(OBJECTS)

# ================================================================ #
# ========================== BUILDING ============================ #
# ================================================================ #

# Building the `country.o` object file from the COUNTRY
$(OBJDIR)/Record.o: $(COUNTRY)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -c $< -o $@
    
test: $(OBJECTS) main.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $(BINS)/$@.out $^ ../../libCDict.a
    
radd: $(OBJECTS) radd.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $(BINS)/$@.out $^ ../../libCDict.a

rload: $(OBJECTS) rload.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $(BINS)/$@.out $^ ../../libCDict.a

rsrh: $(OBJECTS) rsrh.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $(BINS)/$@.out $^ ../../libCDict.a

rrm: $(OBJECTS) rrm.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $(BINS)/$@.out $^ ../../libCDict.a

# ================================================================ #
    
# Creating a directory if it does not exist. *nix
$(shell mkdir -p $(OBJDIR))

# Creating a directory if it does not exist. *nix
$(shell mkdir -p $(BINS))

# ================================================================ #
# ================================================================ #
# ================================================================ #

# Executing the commands regardless of whether a file named clean exists or not
.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out
