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
	sts->SCOREM.score = 0;
	sts->SCOREM.combo = 0;
	sts->SCOREM.maxCombo = 0;
	sts->SCOREM.hp = 100;
}

void ScoreUpdate() {
	ScoreAction();
	ScoreProcess();
}

void ScoreAction() {
	int i;
	for (i = 0; i < KEYMAX; i++) {
		if (sts->COLM.CLIS_Y[i] == -2) {
			GPIO_WRITE(GPIO_PORTL, 0xf, 0);
			GPIO_WRITE(GPIO_PORTM, 0xf, 0);
			sts->SCOREM.combo = 0;
			continue;
		}
		if (sts->COLM.CLIS_Y[i] >= BARHEIGHT / 2) {
			sts->SCOREM.score += 10 + sts->SCOREM.combo % 30;
			GPIO_WRITE(GPIO_PORTL, 0xf, 1);
		}
		else if (sts->COLM.CLIS_Y[i] >= BARHEIGHT / 4) {
			sts->SCOREM.score += 20 + sts->SCOREM.combo % 50;
			GPIO_WRITE(GPIO_PORTM, 0xf, 1);
		}
		sts->COLM.CLIS_Y[i] = -1;	// 충돌값 비활성
		sts->SCOREM.combo++;
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
