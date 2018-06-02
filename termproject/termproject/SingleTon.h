#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#pragma once

#include "screen.h"
#include "Bar.h"
#include "input.h"
#include "Note.h"
#include "play.h"
#include "collision.h"
#include "score.h"
#include "scene.h"
#include "music.h"

#define LCD_HEIGHT	272
#define LCD_WIDTH	480

extern unsigned char buffer[LCD_WIDTH * LCD_HEIGHT];

typedef struct {

	ScreenManager				SM;
	InputManager				IM;
	NoteManager					NM;
	BarManager  				BM;
	CollisionManager			COLM;
	ScoreManager				SCOREM;
	SceneManager				SCENEM;
	MusicManager				MM;
}SingleTon;

static SingleTon st;

void Init();
SingleTon* getSingleTon();

#endif /* _SINGLETON_H_ */
