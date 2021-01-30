#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

#define uint unsigned int 
#define uchar unsigned char
	
void delay(uint a)
{
	while(a--);
}

void main()
{
	int j=0,i=0;
	while(1)
	{
		for(i=0;i<8;i++)//此效果为数码管按位显示 520-1314
		{
			P0=0x00;//消影
			switch(i)         
			{
				case(0):
								LSA=0;LSB=0;LSC=0; P0=0x66; break;
				case(1):
								LSA=1;LSB=0;LSC=0; P0=0x06; break;
				case(2):
								LSA=0;LSB=1;LSC=0; P0=0x4f; break;
				case(3):
								LSA=1;LSB=1;LSC=0; P0=0x06; break;
				case(4):
								LSA=0;LSB=0;LSC=1; P0=0x40; break;
				case(5):
								LSA=1;LSB=0;LSC=1; P0=0x3f; break;
				case(6):
								LSA=0;LSB=1;LSC=1; P0=0x5b; break;
				case(7):
								LSA=1;LSB=1;LSC=1; P0=0x6d; break;
			}
			delay(100);
		}
	}
}