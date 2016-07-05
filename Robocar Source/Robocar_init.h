#ifndef _ROBOCAR_INIT_
#define _ROBOCAR_INIT_

#include<avr/io.h>
#include"avr_lib.h"

#define FRONT	0x06 	// ���� + �ո� LED ����
#define BACK	0x09  	// ���� + �ĸ� LED ����
#define LEFT	0x20	// ��ȸ������ (?? 0x02)
#define RIGHT	0x40 	// ��ȸ������ (?? 0x04)
#define STOP    0x00 	// ����
#define LEFT_U	0x0A	//��ȸ��
#define RIGHT_U	0x05	//��ȸ��
#define B_LEFT	0x08	//���ʸ��� ����
#define B_RIGHT	0x01	//�������� ���� 

#define F_LED	0x04	//���� LED
#define B_LED 	0x08	//�ĸ� LED

#define F_LED_ON()	(PORTB |= F_LED)	//PORTB�� ����LED�� enable���ش�.
#define F_LED_OFF()	(PORTB &= ~F_LED)	//PORTB�� ����LED�� disable���ش�.

#define B_LED_ON()	(PORTB |= B_LED)	//PORTB�� �ĸ�LED�� enable���ش�.
#define B_LED_OFF()	(PORTB &= ~B_LED)	//PORTB�� �ĸ�LED�� disable���ش�.

#define CLK		0x02
#define Din		0x04
#define SYNC	0x01

#define DAC_PORT	PORTG
#define DAC_DDR		DDRG

void PORT_init();//��Ʈ �ʱ�ȭ	

void Convert_sDAC(u08 tmp);

#endif
