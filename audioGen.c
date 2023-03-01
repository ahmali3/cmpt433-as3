#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "audioMixer_template.h"
#include "threadManager.h"
#include "joystick.h"
#include "accelerometer.h"
#include "audioGen.h"
#include "periodTimer.h"
#include "utility.h"

wavedata_t baseDrum1;
wavedata_t hiHat1;
wavedata_t snare1;
wavedata_t baseDrum2;
wavedata_t hiHat2;
wavedata_t snare2;

static int bpm = 120;

enum audioMode currentMode = ROCK;

Period_statistics_t stat;

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
    AudioMixer_freeWaveFileData(&baseDrum1);
    AudioMixer_freeWaveFileData(&hiHat1);
    AudioMixer_freeWaveFileData(&snare1);
    AudioMixer_freeWaveFileData(&baseDrum2);
    AudioMixer_freeWaveFileData(&hiHat2);
    AudioMixer_freeWaveFileData(&snare2);
}

int getBpm(void)
{
    return bpm;
}

void setBpm(int newBpm)
{
    if (newBpm < 40 || newBpm > 300)
    {
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

void playDrumBeat3(void)
{
    AudioMixer_queueSound(&baseDrum2);
    AudioMixer_queueSound(&hiHat2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&baseDrum2);
    AudioMixer_queueSound(&snare2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    AudioMixer_queueSound(&baseDrum2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    AudioMixer_queueSound(&baseDrum2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&baseDrum2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&hiHat2);
    AudioMixer_queueSound(&hiHat2);
    sleepForHalfBeat();

    AudioMixer_queueSound(&baseDrum2);
    sleepForHalfBeat();
}

void AudioMixer_Queue(enum music_inst ins)
{
    switch (ins)
    {
    case BASE:
        AudioMixer_queueSound(&baseDrum1);
        sleepForHalfBeat();
        break;
    case HIHAT:
        AudioMixer_queueSound(&hiHat1);
        sleepForHalfBeat();
        break;
    case SNARE:
        AudioMixer_queueSound(&snare1);
        sleepForHalfBeat();
        break;
    }
}

// Text Display
// Once per second, print to the console
void printData(void)
{
    printf("M%d %dbpm, vol:%d  ", getAudioMode(), getBpm(), AudioMixer_getVolume());

    Period_getStatisticsAndClear(PERIOD_EVENT_SAMPLE_AUDIO, &stat);
    printf("Audio[%.3lf, %.3lf] avg %.3f/%d  ", stat.minPeriodInMs, stat.maxPeriodInMs, stat.avgPeriodInMs, stat.numSamples);
   
    Period_getStatisticsAndClear(PERIOD_EVENT_SAMPLE_ACCEL, &stat);
    printf("Accel[%.3lf, %.3lf] avg %.3f/%d\n", stat.minPeriodInMs, stat.maxPeriodInMs, stat.avgPeriodInMs, stat.numSamples);
}


void *audioGenThread(void *arg)
{
    initAccelerometer();
    AudioMixer_init();
    initAudio();
    usleep(330000);

    long long timeElapsedInMs = 0;
	long long start = getTimeInMs();
	long long end = getTimeInMs();

    while (1)
    {
        end = getTimeInMs();
        timeElapsedInMs = end - start;
        if (timeElapsedInMs >= 1000)
        {
            printData();
            start = getTimeInMs();
            timeElapsedInMs = 0;
        }

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
        else if (getAudioMode() == CUSTOM2)
        {
            playDrumBeat3();
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

void stopAudioMixer()
{
    freeAudio();
    AudioMixer_cleanup();
}

int AudioMixer_getTempo()
{
    return bpm;
}
