
#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int 
	
//ͬʱ��������ʱ�����Ʒ�������������ʱ��0����Ƶ�ʣ���ʱ��1����ͬ��Ƶ�ʳ�����ʱ�䣬
//���300ms�������1��10��50,100��200,400,800,1k��hz���ķ�����

sbit beep=P1^5;

uint code yanshi[]={50000,10000,5000,2500,1250,625,500};

uchar t,bp,pd;

void time0() interrupt 1 //��ʱ��0����Ƶ��
{
	TH0=(65536-yanshi[pd])/256;
	TL0=(65536-yanshi[pd])%256;
	bp++;
}

void time1() interrupt 3 //��ʱ��1���Ƽ��
{
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	t++;
}

void init()
{
	EA=1;
	ET0=1;
	ET1=1;
	TMOD=0x11;
	TH0=(65536-yanshi[pd])/256;
	TL0=(65536-yanshi[pd])%256;	
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	TR0=1;TR1=1;
}


void main()
{
	bp=0;
	pd=0;
	beep=0;
	t=0;
	
	init();
	
	while(1)
	{
		if(bp>0)
		{
			TR0=0;
			bp=0;
			beep=~beep;
			if(t==6)//����300ms
			{
				pd++;
				t=0;
			}
			if(pd==7)//����yanshi[pd]��ֵ
			{
				pd=0;
			}
			TR0=1;
		}
	}
}

/*
void main()
{
	bp=0;
	pd=0;
	beep=0;
	t=0;
	init();
	while(1)
	{
		while(t<6)
		{
			if(bp>0)
			{
				TR0=0;
				bp=0;
				beep=~beep;
				TR0=1;
			}
		}
		t=0;
		pd++;
		if(pd>6)
		{
			pd=0;
		}
	}
}
*/
