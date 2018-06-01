#ifndef _INPUT_H_
#define _INPUT_H_

#include "SingleTon.h"

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

void InputUpdate();

#endif _INPUT_H_