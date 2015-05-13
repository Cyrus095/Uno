### ROOT MAKEFILE ###

# -------------------------------------------------------------
# Bash Commands

MKDIR:= mkdir -p
RMDIR:= rm -rf

# -------------------------------------------------------------
# Directories

BINDIR:= bin
SRCDIR:= src
INCDIR:= include
OBJDIR:= obj

# -------------------------------------------------------------
# Files

BIN:= Uno

# =============================================================

.PHONY: all main count clean distclean

all: main

main:
	@make -C $(SRCDIR)

count:
	@wc -l $(SRCDIR)/*.cpp $(INCDIR)/*.hpp

clean:
	$(RMDIR) $(OBJDIR)

distclean: clean
	$(RMDIR) $(BINDIR)
