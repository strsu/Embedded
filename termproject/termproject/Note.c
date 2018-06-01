/*
 * Note.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "Note.h"

void NoteInit() {
	int i;
	st.NM.speed = 5;
	st.NM.note[0].x = st.NM.note[4].x = 14;
	st.NM.note[1].x = st.NM.note[5].x = 88;
	st.NM.note[2].x = st.NM.note[6].x = 162;
	st.NM.note[3].x = st.NM.note[7].x = 236;

	for (i = 0; i < 8; i++) {
		st.NM.note[i].y = 260;
		st.NM.note[i].height = NOTEHEIGHT;
		st.NM.note[i].active = false;
		st.NM.note[i].image = NOTEIMAGE;
	}
}

void NoteUpdate() {
	int i;
	for (i = 0; i < NOTEMAX; i++) {

		if (!st.NM.note[i].active) { continue; }

		st.NM.note[i].y -= st.NM.speed;

		// miss의 경우...
		if (st.NM.note[i].y <= 0) {

			st.NM.note[i].active = false;
		}
	}
}

void AddNote(int _x, int _y) {
	int i;
	for (i = 0; i < NOTEMAX; i++) {

		if (st.NM.note[i].active) continue;

		st.NM.note[i].active	= true;
		st.NM.note[i].x			= _x;
		st.NM.note[i].y			= _y;
		break;
	}
}

int CheckCollision(int y) {
	int i;
	for (i = 0; i < NOTEMAX; i++) {

		if (!st.NM.note[i].active) { continue; }

		int result = (st.NM.note[i].y - y > 0) ? st.NM.note[i].y - y : y - st.NM.note[i].y;

		if (result <= st.NM.note[i].height) { return result; }

		break;
	}
}

void NoteDraw(unsigned char *buffer, int x1, int y1, int x2, int y2, int image){
	int i;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	// 이 코드는 모니터의 어느 위치에 이미지를 뿌려줄지 결정하는 코드이다.

	WriteCommand(LCD_X_RAM_ADDR_REG);		// Set X
	WriteData(x1 >> 8);
	WriteData(x1 & 0xFF);
	WriteData(x2-1 >> 8);
	WriteData(x2-1 & 0xff);

	WriteCommand(LCD_Y_RAM_ADDR_REG);		// Set Y
	WriteData(y1 >> 8);
	WriteData(y1 & 0xFF);
	WriteData(y2-1 >> 8);
	WriteData(y2-1 & 0xff);

	WriteCommand(LCD_RAM_DATA_REG);
	///// 여기까지

	for(i = 0; i <= NOTEHEIGHT; ++i){
		MX66L51235FRead(image + (i*(NOTEWIDTH)*2), buffer, (NOTEWIDTH)*2);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (NOTEWIDTH)/2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);

		SysCtlDelay(ulClockMS /DIV_MS);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(NOTEWIDTH)], (void *)0x44050018, (NOTEWIDTH)/2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);
		SysCtlDelay(ulClockMS /DIV_MS);
	}

	SetFullFrame();
}
