#include<reg52.h>
/**************************************************************
***        8个发光管来回流动，没个管亮100ms, 				  	  	***
***        流动时让蜂鸣器发出“滴滴”声     				        	***
**************************************************************/
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
	
sbit beep=P1^5;

void delay(uint a)
{
	while(a--);
}

void main()
{
	int n=8;
	int i;
	P2=0xfe;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			beep=~beep;
			delay(24000);
			P2=_crol_(P2,1);
		}
		for(i=0;i<8;i++)
		{
			beep=~beep;
			P2=_cror_(P2,1);
			delay(24000);
		}
	}
}