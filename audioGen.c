#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "audioMixer_template.h"
#include "threadManager.h"

// Generate audio in real-time from a C program using the ALSA API1
// and play that 
// audio through the Zen cape's head-phone output.
// Audio playback must be smooth, consistent, and with low latency (low delay between 
// asking to play a sound and the sound playing).
// At times, multiple sounds will need to be played simultaneously. The program must add 
// together PCM values to generate the sound.
// Generate at least the following three different drum beats (“modes”). You may optionally 
// generate more.
// 1. No drum beat (i.e., beat turned off)
// 2. Standard rock drum beat, as described in section 1. .
// 3. Some other drum beat of your choosing (must be at least noticeably different). This beat 
// need not be a well-known beat (you can make it up). It may (if you want) use timing other 
// than eighth notes.
// You may add additional drum beats if you like! Have fun with it!
// Must use at least three different drum/percussion sounds (need not use the ones 
// provided, but should use reasonably well known percussion sounds like a drum, bell, 
// cymbal, …). For example, a rock beat using the base drum, hi-hat, and snare.
// Control the beat's tempo (in beats-per-minute) in range [40, 300] BPM (inclusive); default 
// 120 BPM. See next section for how to control each of these.
// Control the output volume in range [0, 100] (inclusive), default 80.
// Play additional drum sounds when needed (i.e., have functions that other modules can call 
// to playback drum sounds when needed).
// Audio playback must be smooth, consistent, and with low latency (low delay between 
// asking to play a sound and the sound playing).
// At times, multiple sounds will need to be played simultaneously. The program must add 
// together PCM wave values to generate the sound.
// Hints
// Follow the audio guide on the course website for getting a C program to generate sound.
// Look at the audioMixer_template.h/.c for suggested code on how to go about 
// creating the real-time PCM audio playback of sounds.
// You don't need to use this code, and you may change any of it you like. 
// For the drum-beat audio clips, you may want to use:
// base drum: 100051__menegass__gui-drum-bd-hard.wav
// hi-hat: 100053__menegass__gui-drum-cc.wav
// snare: 100059__menegass__gui-drum-snare-soft.wav

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

void initAudio(void) {
    AudioMixer_readWaveFileIntoMemory(dirBaseDrum1, &baseDrum1);
    AudioMixer_readWaveFileIntoMemory(dirHiHat1, &hiHat1);
    AudioMixer_readWaveFileIntoMemory(dirSnare1, &snare1);
    AudioMixer_readWaveFileIntoMemory(dirBaseDrum2, &baseDrum2);
    AudioMixer_readWaveFileIntoMemory(dirHiHat2, &hiHat2);
    AudioMixer_readWaveFileIntoMemory(dirSnare2, &snare2);
}

//Your task is to create an application that plays a drum-beat. For this, you'll need a basic 
// understanding of what goes into a drum-beat and music.
// Music is played at a certain speed, called the tempo. This tempo is usually in beats per minute 
// (BPM), and often ranges between ~60 (slow) and ~200 (fast) BPM. The beat is the time of a 
// single standard note (called a quarter note). 
// The “notes” in a drum-beat correspond to the drummer striking different drums (or in our case, 
// playing back recordings of those drums). Often, the music calls for hitting a drum faster than just 
// on the full beats, and hence often notes are played on half-beat increments (called an eight note).
// For our standard rock drum beat, we'll be using three drum sounds: the base drum (lowest sound),
// the snare (the sharp, middle sound), and the hi-hat (high metallic “ting”). 
// Music is often laid out in measures of 4 beats (hence the “quarter note”). A standard rock beat, 
// laid out in terms of beats, is:
// Beat 
// (count from 1)
// Action(s) 
// at this time
// 1 Hi-hat, Base
// 1.5 Hi-hat
// 2 Hi-hat, Snare
// 2.5 Hi-hat
// 3 Hi-hat, Base
// 3.5 Hi-hat
// 4 Hi-hat, Snare
// 4.5 Hi-hat
// If you were coding this, you might have a loop that continuously repeats. Each pass through the 
// loop corresponds to a ½ beat (which is an eighth note, and one row in the above table). The loop 
// first plays any needed sound(s) and then waits for the duration of half a beat time.
// The amount of time to wait for half a beat is:
// Time For Half Beat [sec] = 60 [sec/min] / BPM / 2 [half-beats per beat]
// If you want the delay in milliseconds, multiply by 1,000.

// Function for sleeping for the drum beat. Use the AudioMizer_getBPM() function to get the BPM
// and then use the above formula to calculate the time to sleep.
void sleepForHalfBeat(void) {
    long time = (60.0 / 60 / 2.0) * 1000000;
    usleep(time);
}

// Function to play the first pattern of drum beats
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

// Function to play the second pattern of drum beats
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
    playDrumBeat1();
    playDrumBeat2();
    }
    return NULL;
}

void startAudioThread(pthread_t *thread) {
    pthread_create(thread, NULL, audioGenThread, NULL);
}
