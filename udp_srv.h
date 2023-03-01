// Runs the UDP server for the BeagleBone to connect to the user web page that controls the drum playback.
#ifndef _UDP_SRV_H_
#define _UDP_SRV_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "audioGen.h"
#include "audioMixer_template.h"

#define BUFSIZE 2048
#define LISTEN_PORT 12345

enum cmds
{
	CMD_CHECK,
	CMD_STOP,
	CMD_PLAY_BASE,
	CMD_PLAY_SNARE,
	CMD_PLAY_HIHAT,
	CMD_BEAT_STOP,
	CMD_BEAT_ROCK,
	CMD_BEAT_CST1,
	CMD_BEAT_CST2,
	CMD_TEMP_INC,
	CMD_TEMP_DEC,
	CMD_VOL_INC,
	CMD_VOL_DEC
};

// Starts the UDP server.
void start_udp();

#endif
