# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGET= beatbox
SOURCES= mainDriver.c audioMixer_template.c threadManager.c audioGen.c joystick.c

PUBDIR = $(HOME)/cmpt433/public/myApps
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow


# Asound Library
# - See the AudioGuide for steps to copy library from target to host.
LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB

# -pg for supporting gprof profiling.
#CFLAGS += -pg


# all: wav node
# 	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

all: wav
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

clean:
	rm -f $(OUTDIR)/$(TARGET)

# # Copy the sound files, and the nodeJS server to the public directory.
wav:
	mkdir -p $(PUBDIR)/assets/ 
	cp -R assets/* $(PUBDIR)/assets/ 
# node:
# 	mkdir -p $(PUBDIR)/beatbox-server-copy/ 
# 	cp -R as3-server/* $(PUBDIR)/beatbox-server-copy/ 
# 	cd $(PUBDIR)/beatbox-server-copy/ && npm install
	