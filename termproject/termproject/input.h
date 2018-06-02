#ifndef _INPUT_H_
#define _INPUT_H_
#pragma once

#include "cortex_m4.h"

#define KEYMAX		4

typedef struct {

	bool input[KEYMAX];
	bool keyboard, push;
} InputManager;

void InputInit();
void InputUpdate();
void InputAction();

#endif /* _INPUT_H_ */
