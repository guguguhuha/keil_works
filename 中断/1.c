#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
	
sbit beep = P1^5;
	
void delay(uint a)
{
	while(a--);
}

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

void exter0() interrupt 0 //�ж�0
{
	beep = ~beep;
	delay(100);
}

void main()
{
	EA = 1; //�����ж�  
	EX0 = 1; //���ⲿ�ж�0
	//IT0 = 0; Ĭ��Ϊ0����Ϊ��ƽ������ʽ P32;
	IT0 = 1;//�����ش�����ʽ
	// TCON = 0x01; // ͨ��λ�������ڴ�����ʽ��Ч��������ͬ
	while(1)
	{
		uint j,i;
		uchar temp=0xfe;
		for(i=0;i<8;i++)
		{
			P2=temp;
			for(j=0;j<8-i;j++)						
			{
				delay(10000);
				P2=_crol_(P2,1);//���ƵƵ��ƶ�
			}
			temp-=pow(2,i+1);//���ƵƵĸ��� 
	  }
  }
}

