#define _DEFAULT_SOURCE
#include "threadManager.h"
#include "audioMixer_template.h"

bool allThreadsRunning = true;

// Runs all of the threads that the program requires.
void runProgram(void)
{
	pthread_t audio_thread;

    startAudioThread(&audio_thread);
 
    pthread_join(audio_thread, NULL);

	return;
}
