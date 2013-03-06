
#include<avr/interrupt.h>
#include "timer1.h"
#include "timer0.h"
#include "keyboard_scan.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

//#include <string.h>

 #include <avr/wdt.h> 

 #include <avr/sleep.h> // здесь описаны режимы сна
#include "pt/pt.h"
//#include "uart.h"



volatile struct pt  pt2;//,pt_key,pt_blink;


void Port_Init(void);

//extern unsigned char key_code;
//-----------------------------------------------
int main(void)
{
Timer0_Init();
Timer1_Init();
Port_Init();
PT_INIT(&pt2);
	ACSR |= (1<<ACD); //AnaComp Disable
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	

//	sleep_enable();
//	sleep_cpu();	//Усыпляем до следующего включения питания

//	sleep_disable(); //Будим МК по прерыванию
sei();




	while(1)
	{
		Delay_Key_Process(&pt2);
	//	wdt_reset();
	}
}
//-----------------------------------------------
void Port_Init(void)
{
	PCMSK0=0xFF;//разрешаем прерывание по изменеию уровня на портах PC0-PC3
	PCICR|=(1<<PCIE0);
	PCIFR=0;
	
	DDRB=0x00;//PB вход
	PORTB=0xFF;	//подтянут к 1

	DDRD|=_BV(3);//ногодрыг
	PORTD&=!_BV(3);

}
//-----------------------------------------------
ISR(TIMER0_OVF_vect) //обработчик прерывания таймера0 
{
	pt2.pt_time++;

	TCNT0=130;
	TIFR0&=0b11111110;//TIFR0&=!(1<<TOV0);

}
//-----------------------------------------------
/*ISR(PCINT0_vect)//прерывание от портов 
{	
	PCICR&=!(1<<PCIE0);
	PCIFR&=!(1<<PCIF0);

//	TIMSK1^=(1<<TOIE1);
	key_code=KEY_1;//PINB;	
}*/

