###############################################################################
#
# File:
#   makefile
#
# Description:
#   Makefile for glitterbomb AI
#
# Author:
#   Grant Broadwater
#
###############################################################################

CC:=g++
SRCDIR:=src
BUILDDIR:=build
TARGETDIR:=bin
TARGET:=bin/glitterbomb

SRCEXT:=cpp
SOURCES:=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS:=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS:=-g
INC:=-I include

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "$(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

run: $(TARGET)
	@echo "$(TARGET) $(PUZZLE)"; $(TARGET) $(PUZZLE)

valgrind: $(TARGET)
	@echo "valgrind $(TARGET)"; valgrind --track-origins=yes --leak-check=full $(TARGET) 
