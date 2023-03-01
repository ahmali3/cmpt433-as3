#define _DEFAULT_SOURCE
#include "threadManager.h"
#include "audioMixer_template.h"
#include "joystick.h"
#include "accelerometer.h"
#include "udp_srv.h"
#include "periodTimer.h"
bool allThreadsRunning = true;

// Runs all of the threads that the program requires.
void runProgram(void)
{
    Period_init();
	pthread_t audio_thread, joystick_thread, udp_thread;

    startAudioThread(&audio_thread);
    startJoystickThread(&joystick_thread);
    start_udp(&udp_thread);
 
    pthread_join(audio_thread, NULL);
    pthread_join(joystick_thread, NULL);
    pthread_join(udp_thread, NULL);

	return;
}
