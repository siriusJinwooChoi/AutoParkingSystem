#include"RBC_Ultra.h"

u08 US_flag_F=SEND;
u08 US_flag_B=SEND;

u08 US_F_cnt=0;
u08 US_F_c10=0;
u08 US_F_c100=0;
u08 US_F_c1000=0;

u08 US_B_cnt=0;
u08 US_B_c10=0;
u08 US_B_c100=0;
u08 US_B_c1000=0;

u16 US_F_Data = 0;
u16 US_B_Data = 0;

u16 US_F_tmp = 0;
u16 US_B_tmp = 0;

//엔코더 관련
u16 Motor_cnt=0;
u08 m_Rotation = 0;
u08 cnt_tmp = 0;
u08 flag=ON;

void Timer0_init() //초음파 카운팅
{
	TCCR0	=	0x02;	
	TCNT0	=	0xff - 10;		
	
	TIMSK	|=	1 << TOIE0;	
	TIFR	|=	1 << TOV0;
}

void US_Recv_Setting(){
	EICRA	|=0x0a;  
	EIMSK	|=0x03;   // INT0,1 개별 인터럽트 인에이블
	EIFR	|=0x03;  
}


SIGNAL(SIG_OVERFLOW0) //led는 타이머2를 쓰던가해야지...
{
	cli();

 	TCNT0 = 0xff - 10;	 //10us
	
	if(Motor_cnt >= ONE_ROTATE/2) {
		/*
			상황에 따라 여기의 소스는 달라진다.
		*/		
		++m_Rotation;
		Motor_cnt=0;
	}//end if

	if(PINA & 0x10){ //우측모터
		if(flag==ON){
			Motor_cnt++;
			flag=OFF;
		}
	}//end if

	else
		flag=ON;

	if(US_flag_F==CNT){
		US_F_cnt++;	
		if(US_F_cnt==10){
			US_F_c10++;
			US_F_cnt=0;
		}

		if(US_F_c10==10){
			US_F_c100++;
			US_F_c10=0;
		}

		if(US_F_c100==10){
			US_F_c1000++;
			US_F_c100=0;
		}

		if(US_F_c1000>=9){
		
			US_F_cnt=US_F_c10=US_F_c100=US_F_c1000=0;
		}				
	} //end if

	else {
		US_F_cnt=US_F_c10=0,US_F_c100=0,US_F_c1000=0;
	}
	
	if(US_flag_B==CNT){
		US_B_cnt++;	
		if(US_B_cnt==10){
			US_B_c10++;
			US_B_cnt=0;
		}

		if(US_B_c10==10){
			US_B_c100++;US_B_c10=0;
		}

		if(US_B_c100==10){
			US_B_c1000++;US_B_c100=0;
		}

		if(US_B_c1000>=9){
			//US_flag_F2=RECV;
			US_B_cnt=US_B_c10=0,US_B_c100=0,US_B_c1000=0;
		}				
	} //end if
	else {
		US_B_cnt=US_B_c10=0,US_B_c100=0,US_B_c1000=0;
	//	US_F_Data=0;
	}
	sei();
}

SIGNAL(SIG_INTERRUPT0){
	cli();
	if(US_flag_F==CNT){
		US_F_Data = ((US_F_c1000*1000) + (US_F_c100*100) + (US_F_c10*10) + US_F_cnt);
		
		US_F_Data/=3;
		US_F_Data=US_F_Data-(US_F_Data/5);

		US_F_tmp = US_F_Data;
		US_flag_F=RECV;
		}
	sei();
}


SIGNAL(SIG_INTERRUPT1){
	cli();
	if(US_flag_B==CNT){
		US_B_Data = ((US_B_c1000*1000) + (US_B_c100*100) + (US_B_c10*10)+US_B_cnt);
		US_B_Data /= 3;
		US_B_Data=US_B_Data-(US_B_Data/5);
		US_B_tmp = US_B_Data;
		US_flag_B=RECV;
		}
	sei();
}

void print_data(u08 mode){	
	putch_u1('z');
	
	if(mode!=0){		
		putch_u1(( US_F_Data/1000 )+'0');	
		putch_u1(( (US_F_Data/100)%10 )+'0');	
		putch_u1(( (US_F_Data/10)%10 )+'0');	
		putch_u1(( US_F_Data%10 )+'0');	
	}
	else{
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
	}
	US_F_Data=0;
	US_flag_F=RECV;
}

void print_data2(u08 mode){
	putch_u1('x');
	
	if(mode!=0){
		putch_u1(( US_B_Data/1000 )+'0');	
		putch_u1(( (US_B_Data/100)%10 )+'0');	
		putch_u1(( (US_B_Data/10)%10 )+'0');	
		putch_u1(( US_B_Data%10 )+'0');	
	}

	else{
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
	}
	US_B_Data=0;
	US_flag_B=RECV;
	
}

void ultraSend_F(){
	u08 i;
	u08 tmp;
	
	PORTD &= ~(0x40);
	
	tmp = PORTE & ~0x18;
		
	for(i=0; i<9; i++){
		PORTE &= ~0x18;	
		PORTE |=0x08 ;
		
		_delay_us(11);
		
		PORTE &= ~0x18;	
		PORTE |=0x10 ;
		
		_delay_us(11);	
	}
	PORTD |= (0x40);
	
	US_flag_F=CNT;
}

void ultraSend_B(){
	u08 i;
	
	//tmp = PORTE & ~0x18;
	
	PORTD	&=	~(0x80);
	for(i=0; i<9; i++){
		PORTE &= ~0x18;	
		PORTE	|=0x08;
		_delay_us(11);
		PORTE &= ~0x18;	
		PORTE	|=0x10;
		_delay_us(11);	
	}
	PORTD |= (0x80);	

	US_flag_B=CNT;	
	
}


u08 US_Fire_F(){
		u08 U_cnt = 0;
		
		while(1){
			cli();
				ultraSend_F();						  				
			sei();
					
			ms_delay(10);
		
			if(US_flag_F==RECV){

			 	print_data(1);
				return 1;
			 }
				
			U_cnt++;

			if(U_cnt==10){

				print_data(0);
				return 0;
			}

		}		
}



u08 US_Fire_B(){
		u08 U_cnt = 0;
		
		while(1){
			cli();
				ultraSend_B();						  				
			sei();
		
			ms_delay(10);
		
			if(US_flag_B==RECV){
		
			 	print_data2(1);
				return 1;
			 }
				
			U_cnt++;

			if(U_cnt==10){
		
				print_data2(0);
				return 0;
			}

		}
}
