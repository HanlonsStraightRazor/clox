
# Define and export variables

CC           = gcc
DIST_FLAGS   = -g0 -O2
DEBUG_FLAGS  = -ggdb -Og
COMMON_FLAGS = -march=native -pipe -std=c17 -Wall -Wextra
CFLAGS       = $(COMMON_FLAGS) $(DEBUG_FLAGS)

export CC
export CFLAGS

BIN      = clox
SRCDIR   = src
BINDIR   = /usr/local/bin
DISTFILE = $(BIN).tar.gz

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

.PHONY : all clean clobber dist install install-strip tags uninstall

# Default target

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(MAKE) -C $(SRCDIR) -f src.mk

# Remove binaries and object and dependency files

clean :
	$(MAKE) -C $(SRCDIR) -f src.mk clean
	rm -rf $(BIN)

# Remove dist tarball and tags

clobber : clean
	rm -f $(DISTFILE) tags

# Pack source and makefile into tarball

dist :
	rm -f $(DEP)
	tar -czvf $(DISTFILE) $(SRCDIR) Makefile

# Install binar(y|ies)

install : all
	cp $(BIN) $(BINDIR)

# Install and strip binar(y|ies)

install-strip : install
	strip $(BINDIR)/$(BIN)

# Generate tags for source and tests

tags :
	ctags -R $(SRCDIR)

# Uninstall binar(y|ies)

uninstall :
	rm -f $(BINDIR)/$(BIN)
