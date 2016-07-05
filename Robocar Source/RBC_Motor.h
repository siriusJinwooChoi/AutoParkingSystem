#ifndef _RBC_MOTOR_
#define _RBC_MOTOR_

#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"

#define ONE_ROTATE	655 //바퀴회전수

#define DIR_CNT	1 //바퀴회전수

void Motor_mode(unsigned char mode); //모터 방향전환 함수

//void Right_mode();

void Stop_mode(unsigned char mode);

void Timer1_init(); //phase PWM 2ms 주기 로 설정

void PWM_change(char OCR1x, unsigned int value); 
//모터 제어 함수 
//char OCR1x 가 A 면 OCR1A에 value 값이 들어간다.
// 'X'면 OCR1A,B 둘다 들어간다.

#endif
