#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "cortex_m4.h"
#include "myLib.h"
#include "Module.h"

#include "button.h"
#include "Bar.h"
#include "Input.h"
#include "Note.h"
#include "play.h"


typedef struct {

	ButtonManager	BTM;
	InputManager	IM;
	NoteManager		NM;
	BarManager  	BM;
}SingleTon;

SingleTon st;

void Init();

#endif /* _SINGLETON_H_ */
