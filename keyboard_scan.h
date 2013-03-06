#ifndef KEYBOARD_SCAN_H
#define KEYBOARD_SCAN_H

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include<avr/interrupt.h>

#include "pt/pt.h"

#define led_port PORTD
#define led_ddr DDRD
#define led_pin (1<<6);
//#define nop() asm("nop")
//#define  led_pulse {led_port |= led_pin;  nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); led_port &= ~led_pin; nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();nop(); nop(); nop(); nop(); nop(); nop(); nop(); } //50 us

//--------------key_kodes-----------------
#define KEY_1 		0b11111110
#define KEY_2		0b11111101
#define KEY_3		0b11111011
#define KEY_4		0b11110111
#define KEY_5		0b11101111	
#define KEY_6		0b11011111
#define KEY_7		0b10111111
#define KEY_8		0b01111111
//----------------------------------------
#define KEY_CODE_1		250//253
#define KEY_CODE_2		255//250
#define KEY_CODE_3		249//255
#define KEY_CODE_4		254//254
#define KEY_CODE_5		247//249
#define KEY_CODE_6		30//247
#define KEY_CODE_7		252//252
#define KEY_CODE_8		253//30
//----------------------------------------

//PT_THREAD(Keyboard_Scan_Process(struct pt *pt));
PT_THREAD(Delay_Key_Process(struct pt *pt));

#endif
