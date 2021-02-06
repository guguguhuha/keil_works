#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
	
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

uchar code smg[]={0x40,0x7d,0x6d,0x66,0x4f,0x5b,0x06,0x40};
uchar i=0;

void delay(uint a)
{
	while(a--);
}

void main()
{
	while(1)
	{
		for(i=0;i<8;i++)
		{
			switch(i)
			{
				case 0:
					LSA=1;LSB=1;LSC=1;break;
				case 1:
					LSA=0;LSB=1;LSC=1;break;
				case 2:
					LSA=1;LSB=0;LSC=1;break;
				case 3:
					LSA=0;LSB=0;LSC=1;break;
				case 4:
					LSA=1;LSB=1;LSC=0;break;
				case 5:
					LSA=0;LSB=1;LSC=0;break;
				case 6:
					LSA=1;LSB=0;LSC=0;break;
				case 7:
					LSA=0;LSB=0;LSC=0;break;
			}
			P0=smg[i];
			delay(100);
			P0=0x00;//ÏûÓ°
		}
	}
}