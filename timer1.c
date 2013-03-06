#include "timer1.h"
#define FCPU 8000000

//--------------------------------------------------
void Timer1_Init(void)//������������� timer1
{	
	//TIMSK1|=(1<<TOIE1);//overflow interrupt enable

	TCNT1=0xFFB3;
	TCCR1B|=((0<<CS12)|(0<<CS11)|(1<<CS10));//FTMR_CLK=FCLK
	return;
}
//----------------------------------------------------
ISR(TIMER1_OVF_vect) //���������� ���������� �������0 
{
	PORTD^=_BV(3);
	TCNT1=0xFFB3;
}
//---------------------------------------------------
