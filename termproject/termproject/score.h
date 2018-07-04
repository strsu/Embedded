/*
 * score.h
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#ifndef SCORE_H_
#define SCORE_H_

#pragma once

#define KEYMAX			4
#define BARHEIGHT		32

typedef struct {
	int buzzerCnt;
	int score;
	int hp;
	int combo;
	int maxCombo;
} ScoreManager;

void ScoreInit();
void ScoreInit2();
void ScoreUpdate();
void ScoreAction();
void ScoreProcess();

#endif /* SCORE_H_ */
