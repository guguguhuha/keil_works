#include <reg52.h>
/**************************************************************
***        ��8���������ʾ��8λ���������ۼӹ��̡�		  	  	***
**************************************************************/
#define uint unsigned int
#define uchar unsigned char

void delay(uint a)
{
	while(a--);
}

void main()
{
	int i = 0;
	while(1)
	{
		P2=0xff;
		for(i=0;i<256;i++)//1~2**8  �˸��ƣ�ÿһ��Ϊ����״̬
		{
			delay(50000);
			P2-=0x01;
		}
	}
}