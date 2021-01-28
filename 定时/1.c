#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;
sbit LED = P2^7;
sbit beep = P1^5;

uchar tt;
uint num;
uchar code table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
							0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ


void delay(uint a)
{
	while(a--);
}

/*
int pow(int a,int b)
{
	int ret=1;
	int i=0;
	for(i=0;i<b;i++)
	{
		ret*=a;
	}
	return ret;
}
*/

void exter1() interrupt 1 //
{
	TH0 = (65536 - 50000)/256;//��ʱ��0��8λ
	TL0 = (65536 - 50000)%256;//��ʱ��0��8λ
	tt++;
}

/*
void exter0() interrupt 0 //�ж�0
{
	beep = ~beep;
	delay(100);
}
*/

void main()
{
	num = 0;
	tt = 0;
	TMOD = 0x01;//���ö�ʱ��0Ϊ������ʽ1
	TH0 = (65536 - 50000)/256;//��ʱ��0��8λ
	TL0 = (65536 - 50000)%256;//��ʱ��0��8λ
	//TH1 ��ʱ��1��8λ   TL1  ��ʱ��1��8λ
	EA = 1; //�����ж�  
	ET0 = 1; //����ʱ��0�ж�
	TR0 = 1;//������ʱ��0
	//EX0 = 1; //���ⲿ�ж�0
	//IT0 = 0; Ĭ��Ϊ0����Ϊ��ƽ������ʽ P32;
	//IT0 = 1;//�����ش�����ʽ
	//TCON = 0x01; // ͨ��λ�������ڴ�����ʽ��Ч��������ͬ
	while(1)
	{
		if(tt == 4)//һ��tt 50����
		{
			tt = 0;
			LED = 1;
			LSA = 0;
			LSB = 0;
			LSC = 0;
			P0 = table[num];
			num++;
			if (num == 16)
				num = 0;
	  } 
  }
}

