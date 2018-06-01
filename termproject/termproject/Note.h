#ifndef _NOTE_H_
#define _NOTE_H_
#pragma once

#define BACKGROUND		0x80000
#define NOTEIMAGE		0x130000
#define NOTEMAX			12
#define NOTEWIDTH		52
#define NOTEHEIGHT		16

#include "MyLib.h"

static int xPosition[] = {14, 88, 162, 236};

typedef struct {
	int  x, y;				// Note ��ġ����
	bool active;			// Note Ȱ������
	int activeCnt;		// Note Ȱ�����±��� Delay
}NOTE;

typedef struct {
	
	int  speed;
	NOTE note[NOTEMAX];
}NoteManager;

void NoteInit();
void NoteUpdate();
void AddNote(int index);
void NoteAction();
void NoteDraw();

#endif /* _NOTE_H_ */
