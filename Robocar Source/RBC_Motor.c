#include"RBC_Motor.h"

extern unsigned char LED_status;

void Timer1_init()
{
	TCCR1A |= 0xA3;  //comb
    TCCR1B |= 0x02;  // (***0 0010) Phase correct PWM 10bit, Non-inverting, 8 prescaler
                     // f=7.3728MHz/(2*N*0x3FF), N=8 prescaler factor
                     // f= 450Hz, T=2.222msec
				     // PWM�� �ֱ�� 2msec�� �ȴ�.
    TCCR1C=0x00;     // FOC1A=0
    
    TCNT1=0x0000;    // T/C1 value=0

    OCR1A=0x0000;
	OCR1B=0x0000;
}

void PWM_change(char OCR1x, unsigned int value)
{
	switch(OCR1x)
	{
		case 'R':
			OCR1A=value;			
			break;
		
		case 'L':
			OCR1B=value;
			break;
		
		case 'A':			
			OCR1A=value;			
			OCR1B=value;
			break;
		default:
			break;

	}
	
}

void Motor_mode(unsigned char mode){
	PORTA &= 0x70; //�����ʱ�ȭ	
 	
	LED_status = mode; //���⿡ ���� LED��ȯ
	
	PORTA |= mode;	//���� ������ȯ
}

void Stop_mode(unsigned char mode){
	PORTA &= 0x70; //�����ʱ�ȭ	
 	
	LED_status = mode; //���⿡ ���� LED��ȯ
	
	PORTA |= mode;	//���� ������ȯ

	ms_delay(1000);
}

void Right_mode() {
	DDRA = 0x0F;
	DDRB = 0xff;

	PORTA = 0x00;
	PORTB = 0x00;

	PORTB = LEFT | RIGHT | FRONT;
	PORTA = FRONT;

	ms_delay(50);
}

