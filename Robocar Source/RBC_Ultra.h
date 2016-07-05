#ifndef _RBC_ULTRA_
#define _RBC_ULTRA_

#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"
#include"RBC_Motor.h"

enum{SEND,CNT,RECV};

enum{ON,OFF};

void Timer0_init(); //Ä«¿îÆÃ
void US_Recv_Setting();

SIGNAL(SIG_OVERFLOW0);
SIGNAL(SIG_INTERRUPT0);
SIGNAL(SIG_INTERRUPT1);

void ultraSend_F();
void ultraSend_B();

u08 US_Fire_F();
u08 US_Fire_B();

#endif
