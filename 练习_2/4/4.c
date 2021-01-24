#include <reg52.h>
/**************************************************************
***        用8个发光管演示出8位二进制数累加过程。		  	  	***
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
		for(i=0;i<256;i++)//1~2**8  八个灯，每一个为两种状态
		{
			delay(50000);
			P2-=0x01;
		}
	}
}