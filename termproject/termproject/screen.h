#ifndef _SCREEN_H_
#define _SCREEN_H_
#pragma once

#include "MyLib.h"

enum BTYPE {
	SELECT = 0,
	OPTION,
	HELP,
	BTYPE_MAX
};

typedef struct {

	int  x, y; // 현재 위치
	int  width, height;
	int  iSize;
	int  ID;
	int  image;
	bool active;
} Screen;

typedef struct {
	Screen	screen[BTYPE_MAX];
	int		nowID;
} ScreenManager;

void ScreenUpdate(int _X, int _Y);

#endif /*_SCREEN_H_*/
