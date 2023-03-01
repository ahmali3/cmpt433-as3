// Generates drum sounds based on the tempo and mode on the beaglebone.
#ifndef _AUDIO_GEN_H_
#define _AUDIO_GEN_H_
#include <pthread.h>

#define dirBaseDrum1 "beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav"
#define dirHiHat1 "beatbox-wav-files/100053__menegass__gui-drum-cc.wav"
#define dirSnare1 "beatbox-wav-files/100059__menegass__gui-drum-snare-soft.wav"
#define dirBaseDrum2 "beatbox-wav-files/100063__menegass__gui-drum-tom-hi-soft.wav"
#define dirHiHat2 "beatbox-wav-files/100061__menegass__gui-drum-splash-soft.wav"
#define dirSnare2 "beatbox-wav-files/100062__menegass__gui-drum-tom-hi-hard.wav"

enum audioMode
{
    STOP,
    ROCK,
    ALTERNATE,
    CUSTOM2,
    NONE
};

enum music_inst
{
    BASE,
    HIHAT,
    SNARE
};

void startAudioThread(pthread_t *thread);
int getBpm(void);
void setBpm(int newBpm);

void setAudioMode(enum audioMode newMode);
enum audioMode getAudioMode(void);
void AudioMixer_Queue(enum music_inst ins);
void stopAudioMixer();
#endif
int AudioMixer_getTempo();