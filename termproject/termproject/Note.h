#ifndef _NOTE_H_
#define _NOTE_H_
#pragma once
#include "cortex_m4.h"

#define BACKGROUND		0x80000
#define NOTEIMAGE		0x130000
#define NOTEMAX			12
#define NOTEWIDTH		52
#define NOTEHEIGHT		16


uint32_t g_ui32SysClock;
static int xPosition[] = {14, 88, 162, 236};

typedef struct {
	int  x, y;
	bool active;
	int activeCnt;
}NOTE;

typedef struct {
	
	int  speed;
	NOTE note[NOTEMAX];
}NoteManager;

#include "SingleTon.h"

void NoteInit();
void NoteUpdate();
void AddNote(int index);
void NoteDraw();

int CheckCollision(int y);

#endif /* _NOTE_H_ */
