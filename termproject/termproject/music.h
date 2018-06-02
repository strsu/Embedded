/*
 * music.h
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include "myLib.h"

typedef struct {
	int seq[10];
}MP3;

typedef struct {
	int seq[10];
	int delayCnt;
}Buzzer;

typedef struct {
	int nowIndex;
	MP3 mp3;
	Buzzer buzzer;
}MusicManager;

void MusicInit();
void ScollBell();

#endif /* MUSIC_H_ */
