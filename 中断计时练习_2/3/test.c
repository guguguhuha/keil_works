#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char 
	
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

uint count_1=0,count_0=0,l=0,count_1_1=0;
uint num=432;
uint smg[8]={0};
uchar temp=0xff;
uchar tmp=0xfe;
code uint smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

void init_0_1()
{
	EA=1;
	
	TMOD|=0x11;
	
	ET0=1;
	TR0=0;
	
	ET1=1;
	TR1=1;
	
	TH0=0xdb;
	TL0=0xff;
	TH1=0xdb;
	TL1=0xff;
}

void time0() interrupt 1
{
	TH0=0xdb;
	TL0=0xff;
	count_0++;
}

void time1() interrupt 3
{
	TH1=0xdb;
	TL1=0xff;
	count_1++;
	count_1_1++;
	if (num>=398&&count_1==10)
	{
		count_1=0;
		num--;
	}
	if(num<=398)
	{
		l++;
	}
}

void smginit()
{
	smg[0]=0x40;
	smg[1]=0x07;
	smg[2]=0x7d;
	smg[3]=0x6d;
	smg[4]=smgduan[num/100];
	smg[5]=smgduan[(num/10)%10];
	smg[6]=smgduan[num%10];
	smg[7]=0x40;	
}

void delay(uint a)
{
	while(a--);
}

void display()
{
	uint i=0;
	uint j=0;
	if (count_1_1==50)
	{
		P2=tmp;
		tmp=_crol_(tmp,1);
		j++;
		if (j==7)
		{
			tmp=0xfe;
			j=0;
		}
		count_1_1=0;
	}
	smginit();
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
		P0=0x00;//消影
	}
}

void led_smg()
{
	uint i=0;
	TR0=1;
	if(l==30)
	{
		P2=temp;
		temp=~temp;
		l=0;
	}
	if(count_0>=300)
	{
		while(1)
		{
			for(i=0;i<8;i++)
			{
				switch(i)
				{
					case 0:
						LSA=1;LSB=1;LSC=1;P0=0x40;break;
					case 1:
						LSA=0;LSB=1;LSC=1;P0=0x76;break;
					case 2:
						LSA=1;LSB=0;LSC=1;P0=0x79;break;
					case 3:
						LSA=0;LSB=0;LSC=1;P0=0x38;break;
					case 4:
						LSA=1;LSB=1;LSC=0;P0=0x38;break;
					case 5:
						LSA=0;LSB=1;LSC=0;P0=0x3f;break;
					case 6:
						LSA=1;LSB=0;LSC=0;P0=0x86;break;
					case 7:
						LSA=0;LSB=0;LSC=0;P0=0x40;break;
				}
				delay(100);
				P0=0x00;//消影
			}
		}
	}
}

void main()
{
	init_0_1();
	while(1)
	{
		if(num>=398)
		{
			display();
		}
		else
		{
			led_smg();
		}
	}
}