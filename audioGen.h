// Generates audio
#ifndef _AUDIO_GEN_H_
#define _AUDIO_GEN_H_
#include <pthread.h>

enum audioMode {
    ROCK,
    ALTERNATE,
    NONE
};

void startAudioThread(pthread_t *thread);
int getBpm(void);
void setBpm(int newBpm);

void setAudioMode(enum audioMode newMode);
enum audioMode getAudioMode(void);

#endif
