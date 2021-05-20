CC = gcc
CFLAGS = -g -Wall -Wextra -std=c18
BIN = clox
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
DEP = $(patsubst %.c, %.d, $(SRC))

.PHONY : all tags clean

# (Default) all target
all : $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $^

# Build header dependency info w/ object files
-include $(DEP)
%.o : %.c %.d
	$(CC) $(CFLAGS) -c -o $@ $<

%.d : %.c
	$(CC) -MM -MF $@ $?

# tags target
tags : $(SRC) $(wildcard *.h)
	ctags -R .

# clean target
clean :
	rm -rf $(BIN) $(OBJ) $(DEP)
