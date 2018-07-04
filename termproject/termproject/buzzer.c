/*
 * buzzer.c
 *
 *  Created on: 2018. 6. 25.
 *      Author: Home
 */

#include "buzzer.h"
#include "SingleTon.h"

SingleTon *stb;

void BuzzerMusicInit() {
	stb = getSingleTon();
	stb->BUZZERM.stayWithMeCnt = 107;
	stb->BUZZERM.schoolBellCnt = 24;
	stb->BUZZERM.underworldCnt = 56;
	stb->BUZZERM.travelCnt = 119;
	int song[107] = { F1, F1, A1, D1 / 2, D1 / 2, E1 / 2, C1 / 2, C1 / 2, A1, C1 / 2, C1 / 2, G1,
			F1, F1, A1, D1 / 2, D1 / 2, E1 / 2, C1 / 2, C1 / 2, A1, A1 * 2, F1, G1,
			G1, A1, A1, A1, A1, A1S, A1 * 2, A1, A1S, C1 / 2, C1 / 2, C1 / 2, A1S, A1, G1, G1 * 2, F1, G1,
			A1, A1, A1, A1, C1 / 2, B1, F1 / 2, E1 / 2, C1 / 2, C1 / 2, C1 / 2, D1 / 2, C1 / 2, 0, A1,
			F1 / 2, A1, A1, 0, A1, C1 / 2, D1 / 2, E1 / 2, D1 / 2, C1 / 2, C1 / 2, D1 / 2, C1 / 2, 0, A1,
			F1 / 2, A1, A1, 0, A1, C1 / 2, D1 / 2, E1 / 2, D1 / 2, C1 / 2, C1 / 2, A1, G1, F1, E1, D1,
			0, 0, C1, F1, F1,F1,F1,F1,F1, D1, C1, F1, F1, F1, F1, F1, F1, D1, 0
	};
	int delay[107] = { DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16,
							 DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_16 - 2, DLY_16 - 2,
							 DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2,DLY_16, DLY_16 - 2, DLY_16 - 2,
							 DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16, DLY_16, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16, DLY_16,
							 DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16 - 2, DLY_8, DLY_16 - 2, DLY_8, DLY_16, DLY_16,
							 DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16 - 2, DLY_8, DLY_16, DLY_8, DLY_16, DLY_16 - 2, DLY_16,
							 DLY_16, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16
	};

	int schoolBellSong[24] = { G1,G1,A1,A1,G1,G1,E1,G1,G1,E1,E1,D1,G1,G1,A1,A1,G1,G1,E1,G1,G1,D1,E1,C1 };
	int schoolBellSongDelay[24] = { DLY_8,DLY_8,DLY_8,DLY_8,DLY_8,DLY_8,DLY_4,DLY_8,
		DLY_8,DLY_8,DLY_8,20,DLY_8,DLY_8,DLY_8,DLY_8,
		DLY_8,DLY_8,DLY_4,DLY_8,DLY_8,DLY_8,DLY_8,20 };
	int underworld_melody[56] = {
		C1, C1 / 2, A1*2, A1,
		A1S*2, A1S, 0,
		0,
		C1, C1 / 2, A1*2, A1,
		A1S*2, A1S, 0,
		0,
		F1*2, F1, D1*2, D1,
		D1S*2, D1S, 0,
		0,
		F1*2, F1, D1*2, D1,
		D1S*2, D1S, 0,
		0, D1S, C1S, D1,
		C1S, D1S,
		D1S, G1S*2,
		G1*2, C1S,
		C1, F1S, F1, E1, A1S, A1,
		G1S, D1S, B1*2,
		A1*2, A1*2, G1S*2,
		0, 0, 0
	};
	//Underwolrd tempo
	int underworld_tempo[56] = {
		12, 12, 12, 12,
		12, 12, 6,
		3,
		12, 12, 12, 12,
		12, 12, 6,
		3,
		12, 12, 12, 12,
		12, 12, 6,
		3,
		12, 12, 12, 12,
		12, 12, 6,
		6, 18, 18, 18,
		6, 6,
		6, 6,
		6, 6,
		18, 18, 18, 18, 18, 18,
		10, 10, 10,
		10, 10, 10,
		3, 3, 3
	};

	int travel_melody[200] = {
			G1/2, C1/2, C1/2, C1/2, C1/2, G1/2, C1/2, C1/2, C1/2, G1, G1, C1/2, C1/2, C1/2,	// 14
			C1/2, C1/2, G1/2, C1/2, C1/2, C1/2, F1/2, E1/2, C1/2, C1/2, C1/2, A1, E1/2, D1/2, // 14
			D1/2, D1/2, E1/2, D1/2, E1/2, D1/2, F1/2, E1/2, E1/2, C1/2, C1/2, C1/2, D1/2, E1/2,	//14
			C1/2, C1/2, C1/2, C1/2, C1/2, G1, F1/2, E1/2, 0, C1/2, C1/2, C1/2, D1/2, D1/2, C1/2, C1/2, D1/2, D1/2, C1/2, C1/2, D1/2, D1/2, C1/2, C1/2, //25
			C1/2, D1/2, D1/2, C1/2, C1/2, D1/2, D1/2, C1/2, G1/2, E1/2, C1/2, C1/2, C1/2, A1, C1/2, C1/2, G1, C1/2, C1/2, A1, C1/2, G1, G1, C1/2, D1/2, // 25
			F1/2, E1/2, C1/2, F1/2, E1/2, C1/2, F1/2, E1/2, E1/2, 0, G1/2, A1/2, C1/4, C1/4, A1/2, E1/2, E1/2, E1/2, E1/2, D1/2, C1/2, D1/2, E1/2, 0, G1/2, A1/2, C1/4, // 27
	};

	int travel_delay[200] = {
			8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 8, //14
			8,8,16,8,8,16,8,8,8,8,8,8,8,8,	//14
			8,8,8,8,8,8,8,8,8,8,16,8,8,16,	//14
			8,8,8,8,8,8,16,8,20,16,8,8,8,8,8,8,8,8,8,8,8,8,32,8,8, // 25
			8,8,8,8,8,8,8,8,8,8,32,8,8,16,8,8,16,8,8,16,8,8,16,8,8,	// 25
			8,8,8,8,8,8,8,8,32,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8, // 27
	};

	int i;
	for(i=0;i<stb->BUZZERM.stayWithMeCnt;i++) {
		stb->BUZZERM.stayWithMe[i] = song[i];
		stb->BUZZERM.stayWithMEDLY[i] = delay[i];
	}
	for (i = 0; i<stb->BUZZERM.schoolBellCnt; i++) {
		stb->BUZZERM.schoolBell[i] = schoolBellSong[i];
		stb->BUZZERM.schoolBellDLY[i] = schoolBellSongDelay[i];
	}
	for (i = 0; i<stb->BUZZERM.underworldCnt; i++) {
		stb->BUZZERM.underworld[i] = underworld_melody[i];
		stb->BUZZERM.underworldDLY[i] = underworld_tempo[i];
	}
	for (i = 0; i<stb->BUZZERM.travelCnt; i++) {
			stb->BUZZERM.travel[i] = travel_melody[i];
			stb->BUZZERM.travelDLY[i] = travel_delay[i];
		}
}


