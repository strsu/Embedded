/*
 * Note.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "Note.h"
#include "SingleTon.h"
#include "myLib.h"

uint32_t g_ui32SysClock;
SingleTon *stn;

void NoteInit() {
	int i;
	stn = getSingleTon();
	stn->NM.speed = 8;
	for (i = 0; i < NOTEMAX; i++) {
		stn->NM.note[i].active       = false;
		stn->NM.note[i].activeCnt  = 25 + ((i + 1) * 129) % 40;
	}
}

void NoteInit2() {
	int i;
	stn->NM.speed = 8;
	for (i = 0; i < NOTEMAX; i++) {
		stn->NM.note[i].active       = false;
		stn->NM.note[i].activeCnt  	 = stn->random % 40;
	}
}

void NoteUpdate() {

	NoteAction();
	NoteDraw();
}

void AddNote(int index) {
	int i;

	for (i = 0; i < NOTEMAX; i++) {
		if (stn->NM.note[i].active) continue;

		stn->NM.note[i].active	= true;
		stn->NM.note[i].x		= xPosition[index];
		stn->NM.note[i].y		= 256;

		break;
	}
}

void NoteAction() {
	int i, index;

	for (i = 0; i < NOTEMAX; i++) {
		stn->random = rand();
		if (!stn->NM.note[i].active) {					// Note 가 비활성 이면
			stn->NM.note[i].activeCnt--;
			if (stn->NM.note[i].activeCnt < 0) {		// Note 생성 Delay 끝
				index						=  stn->random % 4;	// g_ui32SysClock % 4;
				stn->NM.note[i].activeCnt	= stn->random % 40;
				AddNote(index);
			}
			continue;
		}
		stn->NM.note[i].y -= stn->NM.speed;
		// miss의 경우...
		if (stn->NM.note[i].y <= 0) {
			stn->NM.note[i].active = false;
			//strcpy(stn->SCENEM.musiclist, "miss 1111111111111");
			//AlphaDraw(340, 240);
		}
	}
}

void NoteDraw() {
	int i, j, x1, x2, y1, y2;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	for (j = 0; j < NOTEMAX; j++) {

		if (!stn->NM.note[j].active) continue;
		/* Note 이미지를 그려주는 코드 start */

		WriteCommand(LCD_X_RAM_ADDR_REG);		// Set X
		WriteData(stn->NM.note[j].x >> 8);
		WriteData(stn->NM.note[j].x & 0xFF);
		WriteData(stn->NM.note[j].x + NOTEWIDTH - 1 >> 8);
		WriteData(stn->NM.note[j].x + NOTEWIDTH - 1 & 0xff);

		WriteCommand(LCD_Y_RAM_ADDR_REG);		// Set Y
		WriteData(stn->NM.note[j].y >> 8);
		WriteData(stn->NM.note[j].y & 0xFF);
		WriteData(stn->NM.note[j].y + NOTEHEIGHT - 1 >> 8);
		WriteData(stn->NM.note[j].y + NOTEHEIGHT - 1 & 0xff);

		WriteCommand(LCD_RAM_DATA_REG);
		///// 여기까지

		for (i = 0; i <= NOTEHEIGHT; ++i) {
			MX66L51235FRead(NOTEIMAGE + (i*(NOTEWIDTH) * 2), buffer, (NOTEWIDTH) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (NOTEWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);

			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(NOTEWIDTH)], (void *)0x44050018, (NOTEWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();

		/* Note 이미지를 그려주는 코드 end */

		/* 배경 이미지를 복원해주는 코드 start */

		x1 = stn->NM.note[j].x;
		x2 = stn->NM.note[j].x + NOTEWIDTH;
		y1 = stn->NM.note[j].y + NOTEHEIGHT;
		y2 = stn->NM.note[j].y + NOTEHEIGHT + stn->NM.speed;

		WriteCommand(LCD_X_RAM_ADDR_REG);		// Set X
		WriteData(x1 >> 8);
		WriteData(x1 & 0xFF);
		WriteData(x2 - 1 >> 8);
		WriteData(x2 - 1 & 0xff);

		WriteCommand(LCD_Y_RAM_ADDR_REG);		// Set Y
		WriteData(y1 >> 8);
		WriteData(y1 & 0xFF);
		WriteData(y2 - 1 >> 8);
		WriteData(y2 - 1 & 0xff);

		WriteCommand(LCD_RAM_DATA_REG);

		for (i = y1; i <= y2; ++i) {
			MX66L51235FRead(BACKGROUND + (i * 480 * 2 + x1 * 2), buffer, (x2 - x1) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (x2 - x1) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(x2 - x1)], (void *)0x44050018, (x2 - x1) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();

		/* 배경 이미지를 복원해주는 코드 end */
	}
}
