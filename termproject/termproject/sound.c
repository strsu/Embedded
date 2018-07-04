/*
 * sound.c
 *
 *  Created on: 2018. 6. 25.
 *      Author: Home
 */

#include "sound.h"
#include "SingleTon.h"

SingleTon *stsound;

void SoundInit() {
	stsound = getSingleTon();
	BuzzerMusicInit();
	stsound->SOUNDM.delayDnt = 0;
}

void SoundUpdate() {
	if( stsound->SCENEM.sceneID >= 1 && stsound->SCENEM.sceneID != 7 && stsound->MM.BGM ) {
		WDT1LOAD = stsound->BUZZERM.underworldDLY[stsound->SOUNDM.delayDnt] * 500000;
		BUZZER_clear();
		delay(20000);
		if (stsound->MM.BGM == true) {
			Play(stsound->BUZZERM.underworld[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTL, 0xf, 0xf & stsound->BUZZERM.underworld[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTM, 0xf, 0xf & stsound->BUZZERM.underworld[stsound->SOUNDM.delayDnt]);
		}
		stsound->SOUNDM.delayDnt += 1;
		if (stsound->SOUNDM.delayDnt >= stsound->BUZZERM.underworldCnt) {
			stsound->SOUNDM.delayDnt = 0;
			BUZZER_clear();
		}
	} else
	if (stsound->SCENEM.sceneID == 7 && stsound->UI.MusicID == 3 && stsound->UI.active == false) {	// schoolBell
		WDT1LOAD = stsound->BUZZERM.schoolBellDLY[stsound->SOUNDM.delayDnt] * 1800000;
		BUZZER_clear();
		delay(20000);
		if (stsound->MM.EFM == true) {
			Play(stsound->BUZZERM.schoolBell[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTL, 0xf, 0xf & stsound->BUZZERM.schoolBell[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTM, 0xf, 0xf & stsound->BUZZERM.schoolBell[stsound->SOUNDM.delayDnt]);
		}
		stsound->SOUNDM.delayDnt += 1;
		if (stsound->SOUNDM.delayDnt >= stsound->BUZZERM.schoolBellCnt) {
			//WDT1CTL = 0x0;
			BUZZER_clear();
		}
	} else
	if (stsound->SCENEM.sceneID == 7 && stsound->UI.MusicID == 2 && stsound->UI.active == false ) {	// stayWithMe
		WDT1LOAD = stsound->BUZZERM.stayWithMEDLY[stsound->SOUNDM.delayDnt] * 1800000;
		BUZZER_clear();
		delay(20000);
		if(stsound->MM.EFM == true) {
			Play(stsound->BUZZERM.stayWithMe[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTL, 0xf, 0xf & stsound->BUZZERM.stayWithMe[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTM, 0xf, 0xf & stsound->BUZZERM.stayWithMe[stsound->SOUNDM.delayDnt]);
		}
		stsound->SOUNDM.delayDnt += 1;
		if(stsound->SOUNDM.delayDnt >= stsound->BUZZERM.stayWithMeCnt) {
			//WDT1CTL = 0x0;
			BUZZER_clear();
		}
	} else
	if (stsound->SCENEM.sceneID == 7 && stsound->UI.MusicID == 1 && stsound->UI.active == false) {	// stayWithMe
		WDT1LOAD = stsound->BUZZERM.travelDLY[stsound->SOUNDM.delayDnt] * 1000000;
		BUZZER_clear();
		delay(20000);
		if (stsound->MM.EFM == true) {
			Play(stsound->BUZZERM.travel[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTL, 0xf, 0xf & stsound->BUZZERM.travel[stsound->SOUNDM.delayDnt]);
			GPIO_WRITE(GPIO_PORTM, 0xf, 0xf & stsound->BUZZERM.travel[stsound->SOUNDM.delayDnt]);
		}
		stsound->SOUNDM.delayDnt += 1;
		if (stsound->SOUNDM.delayDnt >= stsound->BUZZERM.travelCnt) {
			//WDT1CTL = 0x0;
			BUZZER_clear();
		}
	}
}
