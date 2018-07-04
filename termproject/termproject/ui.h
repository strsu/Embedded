/*
 * ui.h
 *
 *  Created on: 2018. 6. 24.
 *      Author: Home
 */

#ifndef UI_H_
#define UI_H_

#include "cortex_m4.h"

typedef struct {
	int nextSceneNumber;
	int MusicID;
	bool active;
} UIgameoption;

void UIgameOptionInit();
void UIgameOptionInit2();
void UIgameOptionUpdate();

void UIgameGiveUp();

void MusicOptionDraw();

void PauseYesDraw();
void PauseNoDraw();

#endif /* UI_H_ */
