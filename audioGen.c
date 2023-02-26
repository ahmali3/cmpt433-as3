#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "audioMixer_template.h"
#include "threadManager.h"

#define dirBaseDrum1 "assets/100051__menegass__gui-drum-bd-hard.wav"
#define dirHiHat1 "assets/100053__menegass__gui-drum-cc.wav"
#define dirSnare1 "assets/100059__menegass__gui-drum-snare-soft.wav"
#define dirBaseDrum2 "assets/100063__menegass__gui-drum-tom-hi-soft.wav"
#define dirHiHat2 "assets/100061__menegass__gui-drum-splash-soft.wav"
#define dirSnare2 "assets/100062__menegass__gui-drum-tom-hi-hard.wav"

wavedata_t baseDrum1;
wavedata_t hiHat1;
wavedata_t snare1;
wavedata_t baseDrum2;
wavedata_t hiHat2;
wavedata_t snare2;

static int bpm = 120;

enum audioMode currentMode = ROCK;

void initAudio(void) {
    AudioMixer_readWaveFileIntoMemory(dirBaseDrum1, &baseDrum1);
    AudioMixer_readWaveFileIntoMemory(dirHiHat1, &hiHat1);
    AudioMixer_readWaveFileIntoMemory(dirSnare1, &snare1);
    AudioMixer_readWaveFileIntoMemory(dirBaseDrum2, &baseDrum2);
    AudioMixer_readWaveFileIntoMemory(dirHiHat2, &hiHat2);
    AudioMixer_readWaveFileIntoMemory(dirSnare2, &snare2);
}

int getBpm(void) {
    return bpm;
}

void setBpm(int newBpm) {
    bpm = newBpm;
}

enum audioMode getAudioMode(void) {
    return currentMode;
}

void setAudioMode(enum audioMode newMode) {
    currentMode = newMode;
}

void sleepForHalfBeat(void) {
    long time = (60.0 / bpm / 2.0) * 1000000;
    usleep(time);
}

void playDrumBeat1(void) {
    AudioMixer_queueSound(&hiHat1);
    AudioMixer_queueSound(&baseDrum1);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat1);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat1);
    AudioMixer_queueSound(&snare1);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat1);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat1);
    AudioMixer_queueSound(&baseDrum1);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat1);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat1);
    AudioMixer_queueSound(&snare1);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat1);
    sleepForHalfBeat();
}

void playDrumBeat2(void) {
    AudioMixer_queueSound(&hiHat2);
    AudioMixer_queueSound(&baseDrum2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    AudioMixer_queueSound(&snare2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    AudioMixer_queueSound(&baseDrum2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    AudioMixer_queueSound(&snare2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    sleepForHalfBeat();
}

void *audioGenThread(void *arg) {
    AudioMixer_init();
    initAudio();

    while (1) {
    if (getAudioMode() == ROCK) {
        playDrumBeat1();
    } else if (getAudioMode() == ALTERNATE) {
        playDrumBeat2();
    }
    return NULL;
}
}

void startAudioThread(pthread_t *thread) {
    pthread_create(thread, NULL, audioGenThread, NULL);
}
