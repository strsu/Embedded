#ifndef _NOTE_H_
#define _NOTE_H_
#pragma once

#define NOTEIMAGE		0x130000
#define NOTEMAX			12
#define NOTEWIDTH		52
#define NOTEHEIGHT		16

#include "MyLib.h"

static int xPosition[] = {14, 88, 162, 236};

typedef struct {
	int  x, y;				// Note 위치정보
	bool active;			// Note 활성상태
	int activeCnt;		// Note 활성상태까지 Delay
}NOTE;

typedef struct {
	
	int  speed;
	NOTE note[NOTEMAX];
}NoteManager;

void NoteInit();
void NoteInit2();
void NoteUpdate();
void AddNote(int index);
void NoteAction();
void NoteDraw();


#endif /* _NOTE_H_ */
