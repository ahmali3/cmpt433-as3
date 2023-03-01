# Makefile for building beatbox embedded application.
# Modified from Brian Fraser's Makefile for CMPT433.

TARGET= beatbox_app
SOURCES= mainDriver.c audioMixer_template.c threadManager.c audioGen.c joystick.c accelerometer.c utility.c udp_srv.c periodTimer.c

PUBDIR = $(HOME)/cmpt433/public/myApps/bb_app
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow


# Asound Library
LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB

# -pg for supporting gprof profiling.
#CFLAGS += -pg


all: app_beatbox wav_files server_node
default: all

app_beatbox: mainDriver.c
	mkdir -p $(PUBDIR)
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(PUBDIR)/$(TARGET)  $(LFLAGS) -lpthread -lasound

clean:
	rm -f $(OUTDIR)/$(TARGET)

# # Copy the sound files, and the nodeJS server to the public directory.
wav_files::
	mkdir -p $(PUBDIR)/assets/ 
	cp -R assets/* $(PUBDIR)/assets/ 

server_node:
	mkdir -p $(PUBDIR)/app_srv/ 
	cp -R as3-server/* $(PUBDIR)/app_srv/ 
	cd $(PUBDIR)/app_srv/ && npm install
	