#ifndef _RBC_MOTOR_
#define _RBC_MOTOR_

#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"

#define ONE_ROTATE	655 //����ȸ����

#define DIR_CNT	1 //����ȸ����

void Motor_mode(unsigned char mode); //���� ������ȯ �Լ�

//void Right_mode();

void Stop_mode(unsigned char mode);

void Timer1_init(); //phase PWM 2ms �ֱ� �� ����

void PWM_change(char OCR1x, unsigned int value); 
//���� ���� �Լ� 
//char OCR1x �� A �� OCR1A�� value ���� ����.
// 'X'�� OCR1A,B �Ѵ� ����.

#endif
