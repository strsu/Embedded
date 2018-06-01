/*
 * Module.h
 *
 *  Created on: 2018. 4. 23.
 *      Author: 502
 */

#ifndef TERM_PROJECT_MODULE_H_
#define TERM_PROJECT_MODULE_H_

#include "cortex_m4.h"
#include "MyLib.h"
#include "play.h"

int WhatNote(int note);
void FND_CLOCK(int push_data);
void FND_Calcurator(int push_data, int dip_data);
void Buzzer_play(int *cnt, int *doing);
void Siren();
int LED_swap(int dip);
void Chattering_NoFlag(int push_data, int *cnt);
void Chattering_Flag(int push_data, int *cnt, int *flag);
int isHit(uint8_t code, int *y);

#endif TERM_PROJECT_MODULE_H_
