#ifndef _ROBOCAR_INIT_
#define _ROBOCAR_INIT_

#include<avr/io.h>
#include"avr_lib.h"

#define FRONT	0x06 	// 전진 + 앞면 LED 제어
#define BACK	0x09  	// 후진 + 후면 LED 제어
#define LEFT	0x20	// 우회전제어 (?? 0x02)
#define RIGHT	0x40 	// 좌회전제어 (?? 0x04)
#define STOP    0x00 	// 정지
#define LEFT_U	0x0A	//정회전
#define RIGHT_U	0x05	//역회전
#define B_LEFT	0x08	//왼쪽모터 후진
#define B_RIGHT	0x01	//우측모터 후진 

#define F_LED	0x04	//전면 LED
#define B_LED 	0x08	//후면 LED

#define F_LED_ON()	(PORTB |= F_LED)	//PORTB에 전면LED를 enable해준다.
#define F_LED_OFF()	(PORTB &= ~F_LED)	//PORTB에 전면LED를 disable해준다.

#define B_LED_ON()	(PORTB |= B_LED)	//PORTB에 후면LED를 enable해준다.
#define B_LED_OFF()	(PORTB &= ~B_LED)	//PORTB에 후면LED를 disable해준다.

#define CLK		0x02
#define Din		0x04
#define SYNC	0x01

#define DAC_PORT	PORTG
#define DAC_DDR		DDRG

void PORT_init();//포트 초기화	

void Convert_sDAC(u08 tmp);

#endif
