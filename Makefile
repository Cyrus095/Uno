### ROOT MAKEFILE ###

# -------------------------------------------------------------
# Bash Commands

MKDIR:= mkdir -p
RMDIR:= rm -rf
CPDIR:= cp -rf

# -------------------------------------------------------------
# Directories

BINDIR:= bin
SRCDIR:= src
INCDIR:= include
OBJDIR:= obj
LIBDIR:= lib

# -------------------------------------------------------------
# Files

BIN:= Uno

# =============================================================

.PHONY: all main install count clean distclean libclean

all: main

main:
	@make -C $(SRCDIR)

install:
	@echo "Downloading SFML..."
	@wget 'www.sfml-dev.org/files/SFML-2.2-linux-gcc-64-bit.tar.gz'
	@tar -zxvf SFML-2.2-linux-gcc-64-bit.tar.gz > /dev/null
	@$(CPDIR) SFML-2.2/include/SFML $(INCDIR)
	@$(CPDIR) SFML-2.2/lib $(LIBDIR)
	@$(RMDIR) SFML-2.2* > /dev/null
	@echo "Done!"

count:
	@wc -l $(SRCDIR)/*.cpp $(INCDIR)/*.hpp

clean:
	$(RMDIR) $(OBJDIR)

distclean: clean
	$(RMDIR) $(BINDIR)

libclean:
	$(RMDIR) SFML* $(INCDIR)/SFML $(LIBDIR)
