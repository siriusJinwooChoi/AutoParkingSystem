#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"

unsigned char LED_status; 

extern u08 m_Rotation;
extern u16 US_F_tmp;
extern u16 US_B_tmp;

u16 PSD_val[15]={954,745,512,397,331,283,255,224,200,188,171,164,151,116,110};
u08 PSD_cm[]={5,10,15,20,25,30,35,45,50,55,60,65,70,75,80};

int main(){
	
	u08 tmp=0;
	u08	lineValue = 0;
	u08 loop=1;
	u08 m_State =0;

	u16 Dist=0;
	u08 j;
	u16 tmp_val;
	u08 tmp_cm;
	//u08 tmp;
	u08 US_flag=0;

	DDRB = 0xff;
	PORTB = 0x00;

	DDRA = 0x0F;
	PORTA = 0x00;

	u16 infr[4]={0};
	
	PORT_init();//포트 초기화	

	Timer1_init(); //phase PWM 2ms 주기 로 설정
	Timer2_init(); 
	Timer0_init();
	US_Recv_Setting();

	PWM_change('A',0x280);

	Convert_sDAC(0);
	Convert_sDAC(0);
	
	infr[0]=ADC_Convert(4);	
	
	infr[1]=ADC_Convert(5);			
	
	infr[2]=ADC_Convert(6);			
	
	infr[3]=ADC_Convert(7);			
	
	u08 i;
	u16 ADC_max =infr[0];
	u16 ADC_min =infr[0];
	u16 V_ref = 0;
	
	for(i=1;i<4;i++){
		if(infr[i]>=ADC_max)
			ADC_max = infr[i];
		if(infr[i]<=ADC_min)
			ADC_min = infr[i];
	}
	
	ADC_max = (ADC_max+ADC_min)/1.3;
	
	V_ref = ADC_max*2.56/20.0;
	
	
	Convert_sDAC(V_ref);	
	Convert_sDAC(V_ref);

	DDRC = 0x00;
	
	sei();

	while(1){
		lineValue=PINC;
		tmp = FRONT;

		if(lineValue&0xF0) {
			Motor_mode(FRONT);
		}

		if(lineValue&0x0F) {
			Motor_mode(FRONT);
		}
		
		ms_delay(500);
		
		if(lineValue&0x00) {
			Stop_mode(STOP);
		}

		switch(lineValue){
			case 0xE7: // 1110 0111
			case 0xEF: // 1110 1111
			case 0xF7: // 1111 0111
			case 0xF3: //1111 0011
			case 0xFB: //1111 1011 
			case 0xF9: //1111 1001
			case 0xFC: // 1111 1100
			case 0xFD: // 1111 1101
			case 0xFE: // 1111 1110

			case 0xCF: // 1100 1111
			case 0xDF: // 1101 1111
			case 0x9F: // 1001 1111
			case 0x3F: //0011 1111
			case 0xBF: //1011 1111
			case 0x7F: //0111 1111
			case 0xFF:

			tmp = FRONT;
			break;
			case 0x00:
			tmp = STOP;
			//PORTB = LEFT | RIGHT | BACK;
			//PORTA = STOP;
			//ms_delay(3000);
			break;
		}

		if(m_State != tmp){ //같은 명령을 2번이상 쓰지 않도록 하기 위한 조건문
			m_State = tmp;
			Motor_mode(m_State);
		}
		ms_delay(100);

		if(m_State != tmp){ //같은 명령을 2번이상 쓰지 않도록 하기 위한 조건문
			m_State = tmp;
			Motor_mode(m_State);
		}
		ms_delay(500);	
		
		if(lineValue&0x00) {
			F_LED_OFF();
			B_LED_OFF();
			Motor_mode(STOP);
		}
		
		if(lineValue&0xF0)	//흰색일때 B랑 F둘다 켜져있음.
			B_LED_ON();
			//Motor_mode(FRONT);
		if(lineValue&0x0F)
			F_LED_ON();
			//Motor_mode(FRONT);

		Dist = ADC_Convert(0x00);
		// 원래 정확한 데이타를 구하려면은 다음공식을 적용해야한다.
		// 거리 =  25818 x (측정값 의 -1.203 제곱)

		for(i=0,j=0; i<15; i++){
			if(Dist<PSD_val[i])
				j=i;
			else
				break;							
		}
		
		tmp_cm = PSD_cm[i]-PSD_cm[j];
		tmp_val = PSD_val[j]-PSD_val[i];
		
		tmp = tmp_val/tmp_cm;
		Dist = ((PSD_val[j]-Dist)/tmp)+PSD_cm[j];
		if(Dist < 30) {		//장애물 발견 시 (30cm)
			//Stop_mode(STOP);
			//Motor_mode(RIGHT_U);
			PORTB = LEFT | RIGHT | BACK;
			PORTA = STOP;

			ms_delay(30);

			PORTB = LEFT | RIGHT | BACK;
			PORTA = RIGHT_U;

			_delay_ms(670);
			//나중에 필요하면 여기에 STOP 넣기.
			if(Dist < 5) {
				PORTB = LEFT | RIGHT | BACK;
				PORTA = RIGHT_U;

				_delay_ms(670);
			}
		}
		else
			Motor_mode(FRONT);
		ms_delay(100);
	}
	while(1);
	return 0;
}

