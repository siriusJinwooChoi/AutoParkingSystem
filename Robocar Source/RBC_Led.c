#include"RBC_Led.h"

unsigned char timer2Cnt=0;
unsigned char LED_value=0;
unsigned char LED_mode=0;
unsigned char Blink=0;

extern unsigned char LED_status;

void Timer2_init(){
	TCCR2	=	0x05;	
	TCNT2	=	0xff - 80;		
	
	TIMSK	|=	1 << TOIE2;	
	TIFR	|=	1 << TOV2;
}

void Timer2_Kill(){	//인터럽트부분. lock을 걸어주는 소스이다.
	cli();
	TCCR2	=	0x00;	
	TCNT2	=	0;		
	
	TIMSK	&=	~(1 << TOIE2);	
	TIFR	&=	~(1 << TOV2);
	sei();
}



SIGNAL(SIG_OVERFLOW2) //led 1 초 타이머
{
	cli();
	TCNT2 =	0xff - 80;		 
		 
	timer2Cnt++;
			
	if(timer2Cnt == 45){ //0.5s
		timer2Cnt = 0;
				
		switch(LED_status){
			case FRONT:
			case LEFT:
			case RIGHT:
				LED_value=0x04;
				Blink = BLINK_OFF;
				break;
			
			case BACK:
			case B_LEFT	:
			case B_RIGHT :
				LED_value=0x08;
				Blink = BLINK_ON;
				break;
			
			case LEFT_U:
			case RIGHT_U:
				LED_value=0x0c;
				Blink = BLINK_ON;
				break;
			
			default:
				PORTB &= ~0x0C;
				LED_value = 0x00;
				Blink = BLINK_OFF;
				break;
		}//end switch

		if(LED_mode==0) {
			if(Blink == BLINK_ON)
				PORTB&= ~0x0C;
			
				LED_mode=1;
		}
		else {						
			PORTB |= LED_value;
			LED_mode=0;	
		}	 
 	}//end if 0.5s
	sei();
}
