# I have no idea what I'm doing, but it sort of works

# Plugin name
NAME=SeaTraffic
# Version number
PLUGINVERSION=2.0
# Build target
TARGET=lin.xpl
# Build directory
BUILDDIR=$(CURDIR)/build
# Source directory
SOURCEDIR=$(CURDIR)/src
# Location of the SDK directory
XPSDK=$(CURDIR)/SDK
# Path to SDK headers and widgets
INCL=-I$(XPSDK)/CHeaders/XPLM -I$(XPSDK)/CHeaders/Widgets
# List of C flags
CFLAGS=-m64 -Wno-missing-braces -static-libgcc -shared -fPIC -fvisibility=hidden -Wall -O2 -DVERSION=$(PLUGINVERSION) -DXPLM200=1 -DXPLM210=1 -DAPL=0 -DIBM=0 -DLIN=1 -DXPLM300=1 -DXPLM301=1 -DXP11=1 -lGLU -lGL -lm
# List of source files
SRC= \
	$(SOURCEDIR)/models.c \
	$(SOURCEDIR)/routes.c \
	$(SOURCEDIR)/seatraffic.c

.PHONY: all build clean

# Make all
all:
	mkdir -p $(BUILDDIR)
	gcc $(CFLAGS) $(INCL) $(SRC) -o $(BUILDDIR)/$(TARGET)
	
# Make install
install:	
	mv $(BUILDDIR)/$(TARGET) $(CURDIR)/$(NAME)/64/$(TARGET)

# Make clean
clean:	
	rm -f $(BUILDDIR)/$(TARGET)
	rm -f $(CURDIR)/$(NAME)/64/$(TARGET)
