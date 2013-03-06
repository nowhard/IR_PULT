#include "keyboard_scan.h"
//#include "timer1.h"
 #include <avr/sleep.h> // здесь описаны режимы сна
#include <avr/delay.h>

#define DEV_ADDR 32
uint8_t key_code=0xFF;

#define TIME_START 	5445//9000
#define TIME_START_2 4800
#define TIME_0		341//1000
#define TIME_1		963//2000

#define	TIME_0_DOWN	562
#define	TIME_1_DOWN	1500
#define LED_PORT_0	PORTD&=!_BV(3)

//------------------------------------
ISR(PCINT0_vect)//прерывание от портов 
{	
//	PCICR&=!(1<<PCIE0);
	PCIFR&=!(1<<PCIF0);
//	if(PINB!=0xFF)
	{
		key_code=PINB;
	}
//	else
//	{
//		sleep_cpu();
//	}
}
//--------------------------------------
PT_THREAD(Delay_Key_Process(struct pt *pt))
{	
static unsigned char i=0,j=0;
static unsigned char packet[4]={0,0,0,0};
   PT_BEGIN(pt);
	
   while(1) 
   {
	
	PT_DELAY(pt,20);
	if((key_code!=0xFF) &&(key_code==PINB) )
	{
		packet[0]=DEV_ADDR;
		packet[1]=~DEV_ADDR;
		//-----------------------------------

		switch(key_code)
		{
			case(KEY_1):
			{
				packet[3]=KEY_CODE_1;
				packet[2]=~packet[3];
			}
			break;

			case(KEY_2):
			{
				packet[3]=KEY_CODE_2;
				packet[2]=~packet[3];
			}
			break;

			case(KEY_3):
			{
				packet[3]=KEY_CODE_3;
				packet[2]=~packet[3];
			}
			break;

			case(KEY_4):
			{
				packet[3]=KEY_CODE_4;
				packet[2]=~packet[3];
			}
			break;
			//---------------------------------					
			case(KEY_5):
			{
				packet[3]=KEY_CODE_5;
				packet[2]=~packet[3];
			}
			break;

			case(KEY_6):
			{
				packet[3]=KEY_CODE_6;
				packet[2]=~packet[3];
			}
			break;

			case(KEY_7):
			{
				packet[3]=KEY_CODE_7;
				packet[2]=~packet[3];
			}
			break;

			case(KEY_8):
			{
				packet[3]=KEY_CODE_8;
				packet[2]=~packet[3];
			}
			break;
			//---------------------------------	
			default:
			{
			}	
		}
		
		TIMSK0&=!(1<<TOIE0);
				
		TIMSK1|=(1<<TOIE1);//включим старт
		_delay_us(TIME_START);
		TIMSK1&=!(1<<TOIE1);
		LED_PORT_0;
		_delay_us(TIME_START_2);
		for(i=0;i<4;i++)
		{
			for(j=0;j<8;j++)
			{
				if((packet[i]&(1<<j))!=0)
				{
					TIMSK1|=(1<<TOIE1);//включим старт
					_delay_us(TIME_0);
					TIMSK1&=!(1<<TOIE1);
					LED_PORT_0;
					_delay_us(TIME_1_DOWN);	
				}
				else
				{
					TIMSK1|=(1<<TOIE1);//включим старт
					_delay_us(TIME_0);
					TIMSK1&=!(1<<TOIE1);
					LED_PORT_0;
					_delay_us(TIME_0_DOWN);
				}
				
			}
		}
		TIMSK1|=(1<<TOIE1);//включим старт
		_delay_us(TIME_0);
		TIMSK1&=!(1<<TOIE1);
		LED_PORT_0;		
		
		//-----------------------------------

		TIMSK0|=(1<<TOIE0);
		key_code=0xFF;
	
		PT_DELAY(pt,800);

	}
	
	PCIFR&=!(1<<PCIF0);
	PCICR|=(1<<PCIE0);
//	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
	sleep_enable();

	sleep_cpu();	//Усыпляем до следующего включения питания

	sleep_disable(); //Будим МК по прерыванию	//Усыпляем до следующего включения питания*/
//	sleep_mode();
	
   }
   PT_END(pt);
}
