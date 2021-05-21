
# Declare variables

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
DEP = $(patsubst %.c, %.d, $(SRC))

.PHONY : all clean

# Default target

all : $(OBJ)

-include $(DEP)
%.o : %.c %.d
	$(CC) $(CFLAGS) -c -o $@ $<

%.d : %.c
	$(CC) -MM -MF $@ $?

# Remove object and dependency files

clean :
	rm -rf $(OBJ) $(DEP)
