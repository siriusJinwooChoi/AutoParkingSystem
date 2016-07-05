#include"Robocar_init.h"

void PORT_init()//포트 초기화, 나중에 설정을 다시해야함
{
	
	DDRA = 0x0F; // 모터
    PORTA = 0x00; 

	DDRB = 0xff;  
    PORTB =	0x01; 
	 
	DDRC = 0x00; //수광센서 
	PORTC = 0x00; 
	
	DDRE |= 0x18; //초음파
	PORTE |= 0x18;
		
	DDRD |= 0xc0;
	PORTD |= 0xc0;

	DDRF = 0x00;
	PORTF = 0x00;
}


void Convert_sDAC(u08 tmp){
	u16 data = 0, mask;
	u08 i;

	mask = 0x8000;
	
	data |= tmp << 4; 	//	xx mode	tmp xxxx
						//	  2bit+ 8bit	
						// mode(00) -> power down mode(normal mode)
						// write sequence
	DAC_PORT	|=	SYNC;
	asm("nop");
	DAC_PORT	|=	(CLK);
	asm("nop");
	DAC_PORT	&=	~(CLK);
	asm("nop");
	DAC_PORT	&=	~SYNC;
	asm("nop");
	
	for(i=0; i<16; i++){	//data 전송	
		DAC_PORT |= (CLK);
		asm("nop");
	
		if(data & mask) 
			DAC_PORT |= Din;
		
		else			
			DAC_PORT &= ~(Din);
				
		asm("nop");
		DAC_PORT &= ~(CLK);
		asm("nop");
		data<<=1;

	}//end for
	

}//end func

