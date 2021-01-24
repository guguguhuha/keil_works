#include<reg52.h>
/**************************************************************
***        8�����������������û������100ms, 				  	  	***
***        ����ʱ�÷������������εΡ���     				        	***
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