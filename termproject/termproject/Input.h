#ifndef _INPUT_H_
#define _INPUT_H_
#pragma once
#include "cortex_m4.h"

enum ITYPE {

	KEY1 = 0,
	KEY2,
	KEY3,
	KEY4,
	ENUM_MAX
};

typedef struct {

	bool input[ENUM_MAX];
	bool keyboard, push;
} InputManager;

#include "SingleTon.h"

void InputUpdate();

#endif /* _INPUT_H_ */