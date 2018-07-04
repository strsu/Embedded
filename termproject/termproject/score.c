/*
 * score.c
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#ifndef SCORE_C_
#define SCORE_C_

#include "score.h"

#include "SingleTon.h"
#include "cortex_m4.h"

SingleTon *sts;

void ScoreInit() {
	sts = getSingleTon();
	sts->SCOREM.buzzerCnt = 2;
	sts->SCOREM.score = 0;
	sts->SCOREM.combo = 0;
	sts->SCOREM.maxCombo = 0;
	sts->SCOREM.hp = 100;
}

void ScoreInit2() {
	sts->SCOREM.buzzerCnt = 2;
	sts->SCOREM.score = 0;
	sts->SCOREM.combo = 0;
	sts->SCOREM.maxCombo = 0;
	sts->SCOREM.hp = 100;
}

void ScoreUpdate() {
	ScoreAction();
	ScoreProcess();
}

void ScoreAction() {	// combo 처리도 함계 해줌
	int i;
	for (i = 0; i < KEYMAX; i++) {
		if (sts->COLM.CLIS_Y[i] >= BARHEIGHT / 2) {	// cool
			strcpy(sts->SCENEM.musiclist, "cool 1111111111111");
			AlphaDraw(340, 240);
			strcpy(sts->SCENEM.musiclist, "                  ");
			AlphaDraw(340, 240);
			sts->SCOREM.score += 10 + sts->SCOREM.combo % 30;
			sts->SCOREM.combo += 1;
		} else
		if (sts->COLM.CLIS_Y[i] >= BARHEIGHT / 8) {	// great
			strcpy(sts->SCENEM.musiclist, "great1111111111111");
			AlphaDraw(340, 240);
			strcpy(sts->SCENEM.musiclist, "              ");
			AlphaDraw(340, 240);
			sts->SCOREM.score += 20 + sts->SCOREM.combo % 50;
			sts->SCOREM.combo += 1;
		}
		sts->COLM.CLIS_Y[i] = -1;	// 충돌값 비활성
	}
	if (sts->SCOREM.maxCombo <= sts->SCOREM.combo) {
		sts->SCOREM.maxCombo = sts->SCOREM.combo;
	}
}

void ScoreProcess() {
	int score = sts->SCOREM.score;
	int lo = 6;
	while (score != 0) {
		WRITE_FND(lo, score % 10);
		score = score / 10;
		lo--;
	}
}

#endif /* SCORE_C_ */
