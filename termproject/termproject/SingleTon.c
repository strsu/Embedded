/*
 * SingleTon.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "SingleTon.h"

void Init() {
	NoteInit();
	BarInit();
	InputInit();
	CollisionInit();
	ScoreInit();
	MusicInit();
}

SingleTon* getSingleTon() {
	return &st;
}