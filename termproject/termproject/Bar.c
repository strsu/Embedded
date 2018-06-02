/*
 * Bar.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "Bar.h"
#include "SingleTon.h"
#include "myLib.h"

uint32_t g_ui32SysClock;

SingleTon *stb;

void BarInit() {
	int i;
	stb = getSingleTon();
	stb->BM.bar[0].x = 4;
	stb->BM.bar[1].x = 78;
	stb->BM.bar[2].x = 152;
	stb->BM.bar[3].x = 226;
	for (i = 0; i < BAR_LMAX; i++) {
		stb->BM.bar[i].active = false;
	}
}

void BarUpdate() {
	BarAction();
	BarDraw();
}

void BarAction() {
	int i;

	for (i = 0; i < BAR_LMAX; i++) {
		stb->BM.bar[i].active = stb->IM.input[i];
	}
}

void BarDraw(){
	int i, j, x1, x2, y1, y2;
	int BarImage;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	// 이 코드는 모니터의 어느 위치에 이미지를 뿌려줄지 결정하는 코드이다.
	
	for (j = 0; j < BAR_LMAX; j++) {
		x1 = stb->BM.bar[j].x;
		x2 = stb->BM.bar[j].x + BARWEITHD;
		y1 = 0;
		y2 = BARHEIGHT;

		BarImage = stb->BM.bar[j].active ? 0x1F0000 : 0x1B0000;
		stb->BM.bar[j].active = false;

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
		///// 여기까지

		for (i = 0; i <= BARHEIGHT; ++i) {
			MX66L51235FRead(BarImage + (i*(BARWEITHD) * 2), buffer, (BARWEITHD) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (BARWEITHD) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);

			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(72)], (void *)0x44050018, (BARWEITHD) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();
	}
}

