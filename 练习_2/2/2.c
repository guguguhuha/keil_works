#include <reg52.h>
/**************************************************************
*** 8个发光管由上至下间隔1s流动，其中每个管亮500ms,灭500ms, ***
*** 亮时蜂鸣器响，灭时关闭蜂鸣器，一直重复下去。            ***
**************************************************************/
#include <intrins.h>
#define uint unsigned int 
#define uchar unsigned char
	
sbit beep = P1^5;

void delay(uint a)
{
	uint b = a;
	while(b--);
	while(a--);
}

void beepp()
{
	beep=0;
	delay(50);
	beep=1;
}

void main()
{
	uchar temp = 0xfe;
	P2 = temp;
	while(1)
	{
		beepp();
		delay(55700);
		P2=0xff;
		delay(55700);
		temp=_crol_(temp,1);
		P2 = temp;
	}
}
