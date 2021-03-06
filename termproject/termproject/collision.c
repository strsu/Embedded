/*
 * collision.c
 *
 *  Created on: 2018. 6. 1.
 *      Author: 502
 */

#include "collision.h"
#include "SingleTon.h"

SingleTon *stc;

void CollisionInit() {
	int i;
	stc = getSingleTon();
	for (i = 0; i < KEYMAX; i++) {
		stc->COLM.CLIS_Y[i] = -1;
	}
}

void CollisionInit2() {
	int i;
	for (i = 0; i < KEYMAX; i++) {
		stc->COLM.CLIS_Y[i] = -1;
	}
}

void CollisionUpdate() {
	CollisionUrteil();
}

void CollisionUrteil() {
	int i, j;
	for (i = 0; i < KEYMAX; i++) {
		for (j = 0; j < NOTEMAX; j++) {
			if (stc->IM.input[i] && stc->NM.note[j].active && (stc->NM.note[j].y <= BARHEIGHT) && stc->NM.note[j].x == xPosition[i]) {
				stc->COLM.CLIS_Y[i] = stc->NM.note[j].y;
				UART_printf("NOTE_Y : %d \n\r", stc->COLM.CLIS_Y[i]);
			}
		}
		
	}
}
