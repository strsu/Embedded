/*
 * Bar.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "Bar.h"

void BarInit() {
	int i;
	st.BM.bar[0].x = 4;
	st.BM.bar[1].x = 78;
	st.BM.bar[2].x = 152;
	st.BM.bar[3].x = 226;

	for (i = 0; i < BAR_LMAX; i++) {
		st.BM.bar[i].y = 0;
		st.BM.bar[i].active = false;
	}
}

void BarUpdate() {

	if (!st.BM.bar[0].active) return;

	if (st.IM.input[KEY1]) {

		// effect 삽입
		TouchBar(st.BM.bar[KEY1]);
	}
	if (st.IM.input[KEY2]) {

	}
	if (st.IM.input[KEY3]) {

	}
	if (st.IM.input[KEY4]) {

	}
}

void TouchBar(Bar C) {

	int result;
	result = CheckCollision(C.y);

	if (result <= C.height) {

		// result의 범위에 따라 perfect, great, good
		// 열심히 하시게
	}
}

void BarDraw(unsigned char *buffer, int x1, int y1, int x2, int y2, int image){
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

	for(i = 0; i <= 32; ++i){
		MX66L51235FRead(image + (i*(72)*2 + (i)*0), buffer, (72)*2);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (72)/2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);

		SysCtlDelay(ulClockMS /DIV_MS);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(72)], (void *)0x44050018, (72)/2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);
		SysCtlDelay(ulClockMS /DIV_MS);
	}

	SetFullFrame();
}

