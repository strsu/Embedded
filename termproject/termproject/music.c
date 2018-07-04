/*
 * music.c
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#include "music.h"
#include "SingleTon.h"

SingleTon *stm;

int schoolBell_Codes[24] = { G1,G1,A1,A1,G1,G1,E1,G1,G1,E1,E1,D1,G1,G1,A1,A1,G1,G1,E1,G1,G1,D1,E1,C1 };
int schoolBell_Delays[24] = { DLY_8,DLY_8,DLY_8,DLY_8,DLY_8,DLY_8,DLY_4,DLY_8,
DLY_8,DLY_8,DLY_8,20,DLY_8,DLY_8,DLY_8,DLY_8,
DLY_8,DLY_8,DLY_4,DLY_8,DLY_8,DLY_8,DLY_8,20 };

void MusicInit() {
	stm = getSingleTon();
	stm->MM.buzzer.delayCnt = 0;
	stm->MM.nowIndex = 0;
	stm->MM.BGM = true;
	stm->MM.EFM = true;
}

void ScollBell() {
	if (stm->MM.buzzer.delayCnt == 1) {
		BUZZER_clear();
	}

	if (stm->MM.buzzer.delayCnt == 0) {
		Play(schoolBell_Codes[stm->MM.nowIndex]);
		stm->MM.buzzer.delayCnt = schoolBell_Delays[stm->MM.nowIndex]*2;
		stm->MM.nowIndex++;
	}
	else {
		stm->MM.buzzer.delayCnt--;
	}

}
