#ifndef _RBC_LED_
#define _RBC_LED_

#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"


enum{BLINK_ON,BLINK_OFF};
/*
LED �� ���� Ÿ�̸�2 �ʱ�ȭ
*/

void Timer2_init(); 

void Timer2_Kill();

SIGNAL(SIG_OVERFLOW2);

  
#endif
