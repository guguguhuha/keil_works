#include <reg52.h>
/**************************************************************
*** 8��������������¼��1s����������ÿ������500ms,��500ms, ***
*** ��ʱ�������죬��ʱ�رշ�������һֱ�ظ���ȥ��            ***
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
