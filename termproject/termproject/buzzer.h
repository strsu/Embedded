/*
 * buzzer.h
 *
 *  Created on: 2018. 6. 25.
 *      Author: Home
 */

#ifndef BUZZER_H_
#define BUZZER_H_


typedef struct {
	int stayWithMe[200];
	int stayWithMEDLY[200];
	int stayWithMeCnt;

	int schoolBell[50];
	int schoolBellDLY[50];
	int schoolBellCnt;

	int underworld[60];
	int underworldDLY[60];
	int underworldCnt;

	int travel[200];
	int travelDLY[200];
	int travelCnt;
} BuzzerManager;

void BuzzerMusicInit();

#endif /* BUZZER_H_ */
