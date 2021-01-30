#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

#define uint unsigned int 
#define uchar unsigned char
	
uchar code table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
							0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//œ‘ æ0~Fµƒ÷µ
	
void delay(uint a)
{
	while(a--);
}

void main()
{
	while(1)
	{
		int j=0,i=0;
		for(j=0;j<16;j++)
		{
			P0=table[j];
			for(i=0;i<8;i++)
			{
				switch(i)         
				{
					case(0):
									LSA=0;LSB=0;LSC=0; break;
					case(1):
									LSA=1;LSB=0;LSC=0; break;
					case(2):
									LSA=0;LSB=1;LSC=0; break;
					case(3):
									LSA=1;LSB=1;LSC=0; break;
					case(4):
									LSA=0;LSB=0;LSC=1; break;
					case(5):
									LSA=1;LSB=0;LSC=1; break;
					case(6):
									LSA=0;LSB=1;LSC=1; break;
					case(7):
									LSA=1;LSB=1;LSC=1; break;
			}
				delay(10000);
		}
	}

	}
}
