#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "audioMixer_template.h"
#include "threadManager.h"
#include "joystick.h"
#include "accelerometer.h"
#include "audioGen.h"

wavedata_t baseDrum1;
wavedata_t hiHat1;
wavedata_t snare1;
wavedata_t baseDrum2;
wavedata_t hiHat2;
wavedata_t snare2;

static int bpm = 120;

enum audioMode currentMode = ROCK;

void initAudio(void)
{
    AudioMixer_readWaveFileIntoMemory(dirBaseDrum1, &baseDrum1);
    AudioMixer_readWaveFileIntoMemory(dirHiHat1, &hiHat1);
    AudioMixer_readWaveFileIntoMemory(dirSnare1, &snare1);
    AudioMixer_readWaveFileIntoMemory(dirBaseDrum2, &baseDrum2);
    AudioMixer_readWaveFileIntoMemory(dirHiHat2, &hiHat2);
    AudioMixer_readWaveFileIntoMemory(dirSnare2, &snare2);
}

void freeAudio(void)
{
    AudioMixer_freeWaveData(&baseDrum1);
    AudioMixer_freeWaveData(&hiHat1);
    AudioMixer_freeWaveData(&snare1);
    AudioMixer_freeWaveData(&baseDrum2);
    AudioMixer_freeWaveData(&hiHat2);
    AudioMixer_freeWaveData(&snare2);
}

int getBpm(void)
{
    return bpm;
}

void setBpm(int newBpm)
{
    if (newBpm < 40 || newBpm > 300) {
        printf("BPM must be between 40 and 300\n");
        return;
    }
    bpm = newBpm;
}

enum audioMode getAudioMode(void)
{
    return currentMode;
}

void setAudioMode(enum audioMode newMode)
{
    currentMode = newMode;
}

void sleepForHalfBeat(void)
{
    long time = (60.0 / bpm / 2.0) * 1000000;
    usleep(time);
}

void playDrumBeat1(void)
{
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

void playDrumBeat2(void)
{
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

void *audioGenThread(void *arg)
{   
    initAccelerometer();
    AudioMixer_init();
    initAudio();
    usleep(330000);

    while (1)
    {
        int16_t *accelData = readAccelerometer();

        if (accelData[0] == -1 || accelData[0] == 1)
        {
            AudioMixer_queueSound(&hiHat1);
            sleepForHalfBeat();
        }
        else if (accelData[1] == -1 || accelData[1] == 1)
        {
            AudioMixer_queueSound(&snare1);
            sleepForHalfBeat();
        }
        else if (accelData[2] == -1 || accelData[2] == 0)
        {
            AudioMixer_queueSound(&baseDrum1);
            sleepForHalfBeat();
        }
        else if (getAudioMode() == ROCK)
        {
            playDrumBeat1();
        }
        else if (getAudioMode() == ALTERNATE)
        {
            playDrumBeat2();
        }
    }
    freeAudio();
    AudioMixer_cleanup();
    return NULL;
}

void startAudioThread(pthread_t *thread)
{
    pthread_create(thread, NULL, audioGenThread, NULL);
}
