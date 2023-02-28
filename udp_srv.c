#include "udp_srv.h"

static float get_uptime()
{
    float uptime;
    FILE* uptimeFile = fopen("/proc/uptime", "r");
    fscanf(uptimeFile, "%f", &uptime);
	fclose(uptimeFile);
    return uptime;
}

#define MAKE_RESPONSE(resp)	\
	sprintf(resp, "bbgdata, %f, %d, %d, %d", get_uptime(), AudioMixer_getVolume(), AudioMixer_getTempo(), getAudioMode());

static int map_cmd(char *cmd)
{
	if(strncmp(cmd,"check", strlen(cmd)) == 0)
		return CMD_CHECK;
	else if(strncmp(cmd,"stop", strlen(cmd)) == 0)
		return CMD_STOP;
	else if (strncmp(cmd, "play base", strlen(cmd)) == 0)
		return CMD_PLAY_BASE;
	else if (strncmp(cmd, "play snare", strlen(cmd)) == 0)
		return CMD_PLAY_SNARE;
	else if (strncmp(cmd, "play hihat", strlen(cmd)) == 0)
		return CMD_PLAY_HIHAT;
	else if (strncmp(cmd, "beat stop", strlen(cmd)) == 0)
		return CMD_BEAT_STOP;
	else if (strncmp(cmd, "beat rock", strlen(cmd)) == 0)
		return CMD_BEAT_ROCK;
	else if (strncmp(cmd, "beat custom1", strlen(cmd)) == 0)
		return CMD_BEAT_CST1;
	else if (strncmp(cmd, "beat custom2", strlen(cmd)) == 0)
		return CMD_BEAT_CST2;
	else if (strncmp(cmd, "tempo increase", strlen(cmd)) == 0)
		return CMD_TEMP_INC;
	else if (strncmp(cmd, "tempo decrease", strlen(cmd)) == 0)
		return CMD_TEMP_DEC;
	else if (strncmp(cmd, "volume increase", strlen(cmd)) == 0)
		return CMD_VOL_INC;
	else if (strncmp(cmd, "volume decrease", strlen(cmd)) == 0)
		return CMD_VOL_DEC;
	return -1;
}

static int process_cmds(char *cmd, int cmd_len, char *response)
{
	if(cmd == NULL)
	{
		printf("Invalid command\r\n");
		return 0;
	}
	switch(map_cmd(cmd))
	{
		case CMD_CHECK:
			MAKE_RESPONSE(response)
			break;
		case CMD_TEMP_INC:
			setBpm(getBpm() + 5);
			sprintf(response, "Tempo -> increase.");
			break;
		case CMD_TEMP_DEC:
			setBpm(getBpm() - 5);
			sprintf(response, "Tempo -> decrease.");
			break;

		case CMD_VOL_INC:
			AudioMixer_setVolume(AudioMixer_getVolume() + 5);
			sprintf(response, "Volume -> increase.");
			break;
		case CMD_VOL_DEC:
			AudioMixer_setVolume(AudioMixer_getVolume() - 5);
			sprintf(response, "Volume -> decrease.");
			break;

		case CMD_BEAT_STOP:
			setAudioMode(STOP);
            sprintf(response, "Beat -> none.");
			break;
		case CMD_BEAT_ROCK:
			setAudioMode(ROCK);
			sprintf(response, "Beat ->  Rock.");
			break;
		case CMD_BEAT_CST1:
            setAudioMode(ALTERNATE);
            sprintf(response, "Beat -> custom1.");
			break;
		case CMD_BEAT_CST2:
            setAudioMode(CUSTOM2);
            sprintf(response, "Beat -> custom2.");
			break;

		case CMD_PLAY_BASE:
			AudioMixer_Queue(BASE);
			MAKE_RESPONSE(response)
			break;
		case CMD_PLAY_SNARE:
			AudioMixer_Queue(SNARE);
			MAKE_RESPONSE(response)
			break;
		case CMD_PLAY_HIHAT:
			AudioMixer_Queue(HIHAT);
			MAKE_RESPONSE(response)
			break;
		case CMD_STOP:
			printf("stop cmd\r\n");
			stopAudioMixer();
			MAKE_RESPONSE(response)
			return -1;
			break;
		default:
			printf("invalid cmd\r\n");
			break;
	}

	return 0;
}

void start_udp()
{
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* our socket */
	char buf[BUFSIZE];	/* receive buffer */
	char response[BUFSIZE];

	/* create a UDP socket */

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(LISTEN_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
	}

	/* now loop and process commands */
	for (;;) {

		printf("waiting on port %d\n", LISTEN_PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("received message: \"%s\" (%d bytes)\n", buf, recvlen);
			if(process_cmds(buf, recvlen, response) !=0)
			{
				break;
			}

		printf("sending response: \"%s\"\n", response);
		if (sendto(fd, response, strlen(response), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
		}
	}

	printf("Listener stopped");
	/* never exits */
}
