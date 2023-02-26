#define _DEFAULT_SOURCE
#include "threadManager.h"
#include "audioMixer_template.h"
#include "joyStick.h"

bool allThreadsRunning = true;

// Runs all of the threads that the program requires.
void runProgram(void)
{
	pthread_t audio_thread, joystick_thread;

    startAudioThread(&audio_thread);
    startJoystickThread(&joystick_thread);
 
    pthread_join(audio_thread, NULL);
    pthread_join(joystick_thread, NULL);

	return;
}
