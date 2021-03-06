/*
 * play.h
 *
 *  Created on: 2018. 5. 22.
 *      Author: Home
 */

#ifndef _PLAY_H_
#define _PLAY_H_

#include "cortex_m4.h"
#include "myLib.h"

#define IMAGE0			0x00000
#define IMAGE1			0x40000
#define IMAGE2			0x80000
#define IMAGE3			0xC0000
#define IMAGE5			0x170000

#define DLY_4 	16
#define DLY_8	8
#define DLY_16	4
#define C1 		61068
#define C1S 	57624
#define D1 		54421
#define D1S 	51366
#define E1 		48484
#define F1 		45844
#define F1S 	43270
#define G1 		40815
#define G1S 	38524
#define A1 		36363
#define A1S 	34322
#define B1 		32388
#define C2 		30592

#define imageX 		52
#define imageY 		16

static const int stay_with_me_code[107] = { F1, F1, A1, D1 / 2, D1 / 2, E1 / 2, C1 / 2, C1 / 2, A1, C1 / 2, C1 / 2, G1,
						F1, F1, A1, D1 / 2, D1 / 2, E1 / 2, C1 / 2, C1 / 2, A1, A1 * 2, F1, G1,
						G1, A1, A1, A1, A1, A1S, A1 * 2, A1, A1S, C1 / 2, C1 / 2, C1 / 2, A1S, A1, G1, G1 * 2, F1, G1,
						A1, A1, A1, A1, C1 / 2, B1, F1 / 2, E1 / 2, C1 / 2, C1 / 2, C1 / 2, D1 / 2, C1 / 2, 0, A1,
						F1 / 2, A1, A1, 0, A1, C1 / 2, D1 / 2, E1 / 2, D1 / 2, C1 / 2, C1 / 2, D1 / 2, C1 / 2, 0, A1,
						F1 / 2, A1, A1, 0, A1, C1 / 2, D1 / 2, E1 / 2, D1 / 2, C1 / 2, C1 / 2, A1, G1, F1, E1, D1,
						0, 0, C1, F1, F1,F1,F1,F1,F1, D1, C1, F1, F1, F1, F1, F1, F1, D1, 0
};
static const int stay_with_me_delay[107] = { DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16,
						 DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_8, DLY_16, DLY_8, DLY_16 - 2, DLY_16 - 2,
						 DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2,DLY_16, DLY_16 - 2, DLY_16 - 2,
						 DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16, DLY_16, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16, DLY_16,
						 DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16 - 2, DLY_8, DLY_16 - 2, DLY_8, DLY_16, DLY_16,
						 DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16, DLY_16, DLY_16, DLY_16 - 2, DLY_8, DLY_16, DLY_8, DLY_16, DLY_16 - 2, DLY_16,
						 DLY_16, DLY_16, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16 - 2, DLY_16
};

static int stay_with_me_velocity[107] = {
		5, 15, 7, 20, 10, 20, 32, 12, 44, 21, 45, 12, 5 , 4, 7, 32, 53, 12, 12, 34,
		5, 15, 7, 20, 10, 20, 32, 12, 44, 21, 45, 12, 5 , 4, 7, 32, 53, 12, 12, 34,
		5, 15, 7, 20, 10, 20, 32, 12, 44, 21, 45, 12, 5 , 4, 7, 32, 53, 12, 12, 34,
		5, 15, 7, 20, 10, 20, 32, 12, 44, 21, 45, 12, 5 , 4, 7, 32, 53, 12, 12, 34,
		5, 15, 7, 20, 10, 20, 32, 12, 44, 21, 45, 12, 5 , 4, 7, 32, 53, 12, 12, 34,
		5, 15, 7, 20, 10, 20, 32
};

static int stay_with_me_cnt = 0;
static int delay_cnt = 8;

static int velocity = 6;

void noteView();

void ScoreProcessing(int score);
void KeyboardProcessing(unsigned char *buffer, uint8_t code);
void StayWithMe(int *doing);

#endif _PLAY_H_
