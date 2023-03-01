// Initializes and reads the joystick input on the beaglebone.
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "audioMixer_template.h"
#include "audioGen.h"
#include <pthread.h>
void initJoystick(void);
void controlAudio(void);
void startJoystickThread(pthread_t *thread);

#endif
