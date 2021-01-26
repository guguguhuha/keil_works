#include <reg52.h>

#define uchar unsigned char
	
#define uint unsigned int
	//000 001 010 011 100 101 110 111
	
sbit qw1 = P2^2;
sbit qw2 = P2^3;
sbit qw3 = P2^4;
	
void delay(uint a)
{
	while(a--);
}
unsigned int smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//ÏÔÊ¾0~FµÄÖµ
void main()
{
	int i =0;
	for (i =0;i<16;i++)
	{
		qw1=1;
		qw2=0;
		qw3=0;
		P0=smgduan[i];
		delay(50000);
	}
}
