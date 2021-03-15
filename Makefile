CC = gcc
CFLAGS = -g -Wall -Wextra -std=c18
BIN = clox
OBJS = main.o chunk.o debug.o memory.o value.o
DEPS = $(OBJS:%.o=%.d)

# Default all target
.PHONY : all
all : $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $?

# Build header dependency info w/ object files
-include $(DEPS)
%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $<

# Clean target
.PHONY : clean
clean :
	rm -rf $(BIN) $(OBJS) $(DEPS)
