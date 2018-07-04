/*
 * sound.h
 *
 *  Created on: 2018. 6. 25.
 *      Author: Home
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "cortex_m4.h"

typedef struct {
	int delayDnt;
} SoundManager;

void SoundInit();
void SoundUpdate();
#endif /* SOUND_H_ */
