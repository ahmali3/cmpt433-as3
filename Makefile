# Makefile for building beatbox embedded application.
# Modified from Brian Fraser's Makefile for CMPT433.

TARGET= beatbox
SOURCES= mainDriver.c audioMixer_template.c threadManager.c audioGen.c joystick.c accelerometer.c utility.c udp_srv.c periodTimer.c

PUBDIR = $(HOME)/cmpt433/public/myApps/
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
	rm -rf $(PUBDIR)/beatbox-wav-files/
	rm -rf $(PUBDIR)/beatbox-server-copy/

# # Copy the sound files, and the nodeJS server to the public directory.
wav_files::
	mkdir -p $(PUBDIR)/beatbox-wav-files/ 
	cp -R beatbox-wav-files/* $(PUBDIR)/beatbox-wav-files/

server_node:
	mkdir -p $(PUBDIR)/beatbox-server-copy/
	cp -R as3-server/* $(PUBDIR)/beatbox-server-copy/
	cd $(PUBDIR)/beatbox-server-copy/ && npm install
	