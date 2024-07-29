# ================================================================ #
# ========================== VARIABLES =========================== #
# ================================================================ #

# Object files location. Object files will be placed in this directory during compilation
OBJDIR := objects

# Full names of object files
OBJECTS	:= $(addprefix $(OBJDIR)/, country.o)

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
COUNTRY := $(addprefix source/, country.c)
    
# ================================================================ #
# =========================== TARGETS ============================ #
# ================================================================ #

# Create an object file by default
all: $(OBJECTS)

test: $(OBJECTS)

load: $(OBJECTS)

# ================================================================ #
# ========================== BUILDING ============================ #
# ================================================================ #

# Building the `country.o` object file from the COUNTRY
$(OBJDIR)/country.o: $(COUNTRY)
	$(CC) $(ALL_CFLAGS) $(CFLAGS) -c $< -o $@
    
test: $(OBJECTS) main.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $@.out $^ ../../libCDict.a
    
load: $(OBJECTS) load.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $@.out $^ ../../libCDict.a

# ================================================================ #
    
# Creating a directory if it does not exist. *nix
$(shell mkdir -p $(OBJDIR))

# ================================================================ #
# ================================================================ #
# ================================================================ #

# Executing the commands regardless of whether a file named clean exists or not
.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out
