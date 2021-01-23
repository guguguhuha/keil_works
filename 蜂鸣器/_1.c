#include <reg52.h>
#define uint unsigned int
sbit beep=P1^5;

void delay(uint a)
{
	while(a--);
}

void main()
{
	while(1)
	{
		beep=0;
		delay(500);
		beep=1;
		delay(500);

	}
}