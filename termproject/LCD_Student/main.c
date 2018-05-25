#include "cortex_m4.h"
#include "Module.h"
#include "myLib.h"
#include "math.h"
#include "time.h"
#include "rhyrhm.h"

#define COLOR_BLUE		0x001f
#define COLOR_GREEN		0x07E0
#define COLOR_RED		0xF800
#define COLOR_WHITE		0xFFFF
#define COLOR_BLACK		0x0000

uint32_t g_ui32SysClock;

void _user_interrupt_handler_1(void);
void _user_interrupt_handler_2(void);
void _user_interrupt_handler_3(void);
void _user_interrupt_handler_4(void);

int cnt = 0;
unsigned char buffer[LCD_WIDTH * LCD_HEIGHT];

int main(void) {
	g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);


		int x, y[7] = {0,0,0,0,0,0,0};

		int scrollLR = 5;
		int scrollUN = 3;
		int color = 0xFFCC33;

		int locationX1[7] = {10, 70, 130, 190, 270, 330, 390};
		int locationX2[7] = {50, 110, 170, 250, 310, 370, 430};
		int score_Flag[7] = {0, 0, 0, 0, 0, 0, 0};
		int location;
		int score = 0;
		int doing = 0;
		int i,j, temp;
		int schoolBell_Code[24] = { G1,G1,A1,A1,G1,G1,E1,G1,G1,E1,E1,D1,G1,G1,A1,A1,G1,G1,E1,G1,G1,D1,E1,C1 };
		// note relative variable
		int noteX, noteY;
		int noteX_Location[8] = {15, 90, 165, 240, 15, 90, 165, 240};
		int noteY_Location[8] = {260, 260, 260, 260, 260, 260, 260, 260};
		int push_data;
		// UART 관련 함수
		uint8_t code;

		float BRD;
		int   BRDI;
		int   BRDF;

		//uart baud rate(p.1339)
		BRD = (float)g_ui32SysClock / (16 * 115200);
		BRDI = (int)BRD;
		BRDF = (int)(((BRD - (int)BRD)*64) + 0.5);

		UART_init(BRD, BRDI, BRDF);

		UART_printf("//**************************************//\n\r");
		UART_printf("//***********  Initialize  *************//\n\r");
		UART_printf("//***********      OK      *************//\n\r");
		UART_printf("//**************************************//\n\r");


		// Interupt init
		//Interrupt_init();

		// LED 관련 함수
		LED_init();
		LED_clear();

		//DIP SWITCH 관련 함수
		//DIP_init();


		// PUSH 관련 함수
		PUSH_init();

		// 7-SEGMENT 관련 함수
		FND_init();
		FND_clear();

		// BUZZER 관런 함수
		BUZZER_init();
		TIMER_init();
		WDTinitISR();

		LCD_Init(g_ui32SysClock);
		//DrawImage(buffer, 0, 0, 480, 272, IMAGE0);


		GPIO_WRITE(GPIO_PORTD, 0x10, 0x10);  // buzzer ON
		GPTMCTL = GPTMCTL | 0x41;   		 // timer enable

		BUZZER_clear();
		delay(1000000);

		DrawImage(buffer, 0, 0, 480, 272, IMAGE2);
		//RestoreBackground(buffer, 0, 0, 50, 16, IMAGE5);
		noteX = 15;
		noteY = 260;
		//NoteDraw(buffer,0,1,imageX,imageY+1,NOTE);
		while(1) {
			noteView(buffer, noteX_Location, noteY_Location);
			StayWithMe(&doing);
			doing--;
		}
		cnt = 0;

		//while(1);
 	while(1){
		//push_data =  (~GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & (~GPIO_READ(GPIO_PORTN, (0x01 << 3)) >> 2) & \
					 (~GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & (~GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4);
		//DrawLine(24, 24, 240, 240, 0x3333CC);
		/*code = UART_getkey();
		KeyboardProcessing(buffer, code);
		//Buzzer_play(&cnt, &doing);
		doing--;
		StayWithMe(&cnt, &doing);
		for(location = 0;location<7;location++) {
			DrawRect(locationX1[location], 240 - y[location], locationX2[location], 260 - y[location], color);
			RestoreBackground(buffer,locationX1[location],250 - y[location],locationX2[location]+4,260 - y[location]+1,IMAGE2);
			score += isHit(code, y);
			ScoreProcessing(score);
		}
		y[0] += 10;		y[1] += 5;		y[2] += 8;
		y[3] += 10;		y[4] += 5;		y[5] += 10;		y[6] += 5;

		for(location = 0;location<7;location++) {
			if(y[location] >= 230) {
				y[location] = 0;
				//y[location] = schoolBell_Code[cnt]%24;
				RestoreBackground(buffer,0,0,474,31,IMAGE2);
			}
			ScoreProcessing(score);
		}
		RestoreBackground(buffer,10,30,50+4,32+1,0x80000);*/
 		//CharacterDraw(buffer,0,0,115,122,IMAGE3);
		//score++;
	} // end while

}

 void _user_interrupt_handler_1(void) {
 	GPIO_PORTP_IM = GPIO_PORTP_IM & (~(0x01 << 1));

 	// ******* Your Code ******* //
 	cnt = 0;

 	// *********  FIN ********** //

 	GPIO_PORTP_IM = GPIO_PORTP_IM | (0x01 << 1);
 	//interrupt set pending/clear pending(p.168~169)
 	INTUNPEND2 = INTPEND2;
 }

 void _user_interrupt_handler_2(void){
 	GPIO_PORTN_IM = GPIO_PORTN_IM & (~(0x01 << 3));

 	// ******* Your Code ******* //



 	// *********  FIN ********** //

 	GPIO_PORTN_IM = GPIO_PORTN_IM | (0x01 << 3);
 	//interrupt set pending/clear pending(p.168~169)
 	INTUNPEND2 = INTPEND2;
 }

 void _user_interrupt_handler_3(void){
 	GPIO_PORTE_IM = GPIO_PORTE_IM & (~(0x01 << 5));

 	// ******* Your Code ******* //



 	// *********  FIN ********** //

 	GPIO_PORTE_IM = GPIO_PORTE_IM | (0x01 << 5);
 	//interrupt set pending/clear pending(p.168~169)
 	INTUNPEND2 = INTPEND2;
 }

 void _user_interrupt_handler_4(void){
 	GPIO_PORTK_IM = GPIO_PORTK_IM & (~(0x01 << 7));

 	// ******* Your Code ******* //

 	GPIO_WRITE(GPIO_PORTL, 0x0f, 2);
 	delay(50000000);
 	GPIO_WRITE(GPIO_PORTL, 0x0f, 0);

 	// *********  FIN ********** //

 	GPIO_PORTK_IM = GPIO_PORTK_IM | (0x01 << 7);
 	//interrupt set pending/clear pending(p.168~169)
 	INTUNPEND2 = INTPEND2;
 }


