#include <reg52.h>

#define uint unsigned int 
#define uchar unsigned char
	
code uchar table[]={0x3f,0x06,0x5b,0x4f,
					0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,
					0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ
	
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


void check()
{
	uint i=0;
	uchar temp,key;
	if(k1==0)//�ж��Ƿ���
	{
		delay(1000);//���з���
		if(k1==0)//�ٴ��ж��Ƿ���
		{
			led=~led;
			num++;
			if(num==16)
				num=0;
			while(!k1);//�������ΰ���
		}
	}
}


void main()
{
	LSA=1;
	LSB=1;
	LSC=1;
	while(1)
	{
		P0=table[num];
		check();
		
	}
}