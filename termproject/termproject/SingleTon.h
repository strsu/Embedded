#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#pragma once

#include "screen.h"
#include "Bar.h"
#include "Input.h"
#include "Note.h"
#include "play.h"
#include "collision.h"

#define LCD_HEIGHT	272
#define LCD_WIDTH	480

extern unsigned char buffer[LCD_WIDTH * LCD_HEIGHT];

typedef struct {

	ScreenManager				SM;
	InputManager					IM;
	NoteManager					NM;
	BarManager  					BM;
	CollisionManager				COLM;
}SingleTon;

static SingleTon st;

void Init();

#endif /* _SINGLETON_H_ */
