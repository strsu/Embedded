#ifndef _NOTE_H_
#define _NOTE_H_

#include "SingleTon.h"

#define NOTEIMAGE		0x130000
#define NOTEMAX			8
#define NOTEWIDTH		52
#define NOTEHEIGHT		16

extern uint32_t g_ui32SysClock;

typedef struct {
	int  x, y;
	int  height;
	bool active;
	int  image;
}NOTE;

typedef struct {
	
	int  speed;
	NOTE note[NOTEMAX];
}NoteManager;


void NoteInit();
void NoteUpdate();

void AddNote(int _x, int _y);

int CheckCollision(int y);

void NoteDraw(unsigned char *buffer, int x1, int y1, int x2, int y2, int image);

#endif /* _NOTE_H_ */