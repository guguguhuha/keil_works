#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

unsigned int i=0;
unsigned int count=0;

void init_time0()
{
	EA=1;
	TMOD=1;
	ET0=1;
	TR0=1;
	TH0=0xdb;
	TL0=0xff;
}

void time0() interrupt 1
{
	TH0=0xdb;
	TL0=0xff;
	i++;
}

void main()
{
	init_time0();
	LSA=0;
	LSB=0;
	LSC=0;
	while(1)
	{
		if(i==50)
		{
			if(count==16)
			{
				count=0;
			}
			P2=0x00;
			switch(count)
			{
				case 0:
					P0=0x3f;break;//0
				case 1:
					P0=0x06;break;//1
				case 2:
					P0=0x5b;break;//2
				case 3:
					P0=0x4f;break;//3
				case 4:
					P0=0x66;break;//4
				case 5:
					P0=0x6d;break;//5
				case 6:
					P0=0x7d;break;//6
				case 7:
					P0=0x07;break;//7
				case 8:
					P0=0x7f;break;//8
				case 9:
					P0=0x6f;break;//9
				case 10:
					P0=0x77;break;//a
				case 11:
					P0=0x7c;break;//b
				case 12:
					P0=0x39;break;//c
				case 13:
					P0=0x5e;break;//d
				case 14:
					P0=0x79;break;//e
				case 15:
					P0=0x71;break;//f
				default:
					count=0;break;
			}
			count++;
			i=0;

		}
	}
}