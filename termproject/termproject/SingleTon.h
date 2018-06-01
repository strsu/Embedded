#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#pragma once

#include "cortex_m4.h"
#include "Module.h"
#include "myLib.h"
#include "math.h"
#include "time.h"

#include "button.h"
#include "Bar.h"
#include "Input.h"
#include "Note.h"
#include "play.h"

#define LCD_HEIGHT	272
#define LCD_WIDTH	480

extern unsigned char buffer[LCD_WIDTH * LCD_HEIGHT];

typedef struct {

	ButtonManager	BTM;
	InputManager	IM;
	NoteManager		NM;
	BarManager  	BM;
}SingleTon;

static SingleTon st;

void Init();

#endif /* _SINGLETON_H_ */
