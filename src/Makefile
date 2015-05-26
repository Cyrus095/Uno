### SRC MAKEFILE ###

# -------------------------------------------------------------
# Bash Commands

MKDIR:= mkdir -p

# -------------------------------------------------------------
# Directories

BINDIR:= ../bin
SRCDIR:= .
INCDIR:= ../include
OBJDIR:= ../obj
LIBDIR:= ../lib

# -------------------------------------------------------------
# Compiler

CC:= g++
CFLAGS:= -Wall -O3 -std=c++11 -pedantic -Wno-unused-result
LIBS:= -L$(LIBDIR) -lsfml-network -lsfml-system
INC:= -I$(INCDIR)

# -------------------------------------------------------------
# Files

BIN:= Uno
SRC:= $(wildcard $(SRCDIR)/*.cpp)
OBJ:= $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

SRC_NOMAIN:= $(filter-out $(SRCDIR)/main.cpp, $(wildcard $(SRCDIR)/*.cpp))
OBJ_NOMAIN:= $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC_NOMAIN))

# =============================================================

.PHONY: all object

all: $(BINDIR)/$(BIN)

object: $(OBJ_NOMAIN)

$(BINDIR)/$(BIN): $(OBJ) | $(BINDIR)
	$(CC) $^ $(LIBS) -o $@
	@echo "Generating C++ binary \033[1;32m"$@"\033[0m"

$(OBJ): | $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR) $(BINDIR):
	$(MKDIR) $@
