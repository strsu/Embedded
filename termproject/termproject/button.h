#ifndef _BUTTON_H_
#define _BUTTON_H_
#pragma once
#include "cortex_m4.h"

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
} Button;

typedef struct {
	Button	button[BTYPE_MAX];
	int		nowID;
} ButtonManager;

#include "SingleTon.h"

void ButtonUpdate(int _X, int _Y);

int BTNCheckCollision(Button B, int _x, int _y);

#endif /*_BUTTON_H_*/
