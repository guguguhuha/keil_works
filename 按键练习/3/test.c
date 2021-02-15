#include <reg52.h>

#define uint unsigned int 
#define uchar unsigned char
	
code uchar table[]={0x3f,0x06,0x5b,0x4f,
					0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,
					0x39,0x5e,0x79,0x71};//显示0~F的值

uchar smg[8];
					
sbit k1=P3^1;
						
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
						
sbit led=P2^0;						

uint num=0;
						
void delay(uint a)
{
	while(a--);
}

void check()//按下时蜂鸣器工作
{
	P1=0x0f;
	if(P1!=0x0f)
	{
		delay(1000);
		if(P1!=0x0f)
		{
			P1=0x0f;//列
			switch(P1)
			{
				case 0x07:
					num=0;break;
				case 0x0b:
					num=1;break;
				case 0x0d:
					num=2;break;
				case 0x0e:
					num=3;break;
			}
			P1=0xf0;//行
			switch(P1)
			{
				case 0x70:
					num=num+0;break;
				case 0xb0:
					num=num+4;break;
				case 0xd0:
					num=num+8;break;
				case 0xe0:
					num=num+12;break;
			}
			while(P1!=0xf0);
		}
	}
}


void smginit()
{
	uint temp=num*num;
	smg[0]=table[temp%10];
	smg[1]=table[temp/10%10];
	smg[2]=table[temp/100];
	smg[3]=table[0];
	smg[4]=table[0];
	smg[5]=table[0];
	smg[6]=table[0];
	smg[7]=table[0];
}

void display()
{
	uint i=0;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:
				LSA=0;LSB=0;LSC=0;break;
			case 1:
				LSA=1;LSB=0;LSC=0;break;
			case 2:
				LSA=0;LSB=1;LSC=0;break;
			case 3:
				LSA=1;LSB=1;LSC=0;break;
			case 4:
				LSA=0;LSB=0;LSC=1;break;
			case 5:
				LSA=1;LSB=0;LSC=1;break;
			case 6:
				LSA=0;LSB=1;LSC=1;break;
			case 7:
				LSA=1;LSB=1;LSC=1;break;
		}
		P0=smg[i];
		delay(100);
		P0=0x00;
	}
}


void main()
{
	LSA=1;
	LSB=1;
	LSC=1;
	while(1)
	{
		smginit();
		display();
		check();
		
	}
}