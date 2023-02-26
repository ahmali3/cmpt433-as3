#include "audioMixer_template.h"

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


