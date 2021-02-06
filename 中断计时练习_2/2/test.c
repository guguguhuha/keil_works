#include <reg52.h>

typedef unsigned int uint;
typedef unsigned char uchar;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

uchar code smg[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,};
uint sec = 0;
uint min = 0;
uint hour = 0;


void delay(uint a)
{
	while(a--);
}


void init()
{
	EA=1;
	TMOD=1;
	ET0=1;
	TH0=0xdb;
	TL0=0xff;
	TR0=1;
}

void time0() interrupt 1
{
	TH0=0xdb;
	TL0=0xff;
	sec++;
	if (sec==100)
	{
		min++;
		sec=0;
	}
	if(min==60)
	{
		hour++;
		min=0;
	}
	if(hour==100)
	{
		hour=0;
	}
}

void display()
{
	uint i=0;
	uint sec_1=sec/10;
	uint sec_2=sec%10;
	uint min_1=min/10;
	uint min_2=min%10;
	uint hour_1=hour/10;
	uint hour_2=hour%10;
	
/*
	smg[0]=c;
	smg[1]=sec_2;
	smg[2]=0x40;
	smg[3]=min_1;
	smg[4]=min_2;
	smg[5]=0x40;
	smg[6]=hour_1;
	smg[7]=hour_2;
*/	
	
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:
				LSA=0;LSB=0;LSC=0;P0=smg[sec_2];break;
			case 1:
				LSA=1;LSB=0;LSC=0;P0=smg[sec_1];break;
			case 2:
				LSA=0;LSB=1;LSC=0;P0=0x40;break;
			case 3:
				LSA=1;LSB=1;LSC=0;P0=smg[min_2];break;
			case 4:
				LSA=0;LSB=0;LSC=1;P0=smg[min_1];break;
			case 5:
				LSA=1;LSB=0;LSC=1;P0=0x40;break;
			case 6:
				LSA=0;LSB=1;LSC=1;P0=smg[hour_2];break;
			case 7:
				LSA=1;LSB=1;LSC=1;P0=smg[hour_1];break;
		}
		delay(100);
		P0=0x00;
	}
}

void main()
{
	init();
	while(1)
	{
		display();
	}
}