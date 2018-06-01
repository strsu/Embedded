#ifndef _INPUT_H_
#define _INPUT_H_
#pragma once

#define KEYMAX		4
#define FALSE			0
#define TRUE			1

typedef struct {

	char input[KEYMAX];
	char keyboard, push;
} InputManager;

void InputInit();
void InputUpdate();
void InputAction();

#endif /* _INPUT_H_ */
