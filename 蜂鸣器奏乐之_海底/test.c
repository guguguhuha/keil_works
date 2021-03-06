/*
	记住：三个数字一组，代表一个音符。
第一个数字是1234567之一，代表音符哆来咪发...；
第二个数字是0123之一，代表低音、中音、高音、超高音；
第三个数字是半拍的个数，代表时间长度。

*/

#include "reg52.h"   			//头文件调用
sbit speaker = P1^5;			//定义蜂鸣器

unsigned char timer0h, timer0l; //音调高低
unsigned char time;             //一个音符的时间
//--------------------------------------
//单片机晶振采用11.0592MHz
// 频率-半周期数据表 高八位 本软件共保存了四个八度的28个频率数据
code unsigned char FREQH[] = {
0xF2, 0xF3, 0xF5, 0xF5, 0xF6, 0xF7, 0xF8,	    //低音1234567
0xF9, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFC, 0xFC, //1,2,3,4,5,6,7,i
0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 			//高音 234567
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF}; 		//超高音 1234567

// 频率-半周期数据表 低八位
code unsigned char FREQL[] = {
0x42, 0xC1, 0x17, 0xB6, 0xD0, 0xD1, 0xB6, 		//低音1234567
0x21, 0xE1, 0x8C, 0xD8, 0x68, 0xE9, 0x5B, 0x8F, //1,2,3,4,5,6,7,i
0xEE, 0x44, 0x6B, 0xB4, 0xF4, 0x2D, 			//高音 234567
0x47, 0x77, 0xA2, 0xB6, 0xDA, 0xFA, 0x16}; 		//超高音 1234567
//--------------------------------------

code unsigned char hd[]={
1,3,4, 6,2,4, 3,2,2, 2,2,2, 3,2,4, 2,2,2, 3,2,2, 5,2,2, 3,2,4, 6,1,2, 5,2,2, 5,2,2,
3,2,1, 2,2,1, 6,1,2, 1,2,2, 1,2,4, 7,1,2, 1,2,2, 2,2,2, 5,1,2, 6,1,2, 6,1,4, 6,1,1, 
1,2,1, 2,2,2, 3,2,2, 2,2,2, 3,2,3, 2,2,2, 3,2,1, 5,2,1, 5,2,2, 3,2,2, 5,1,1, 6,1,3,
6,1,1 ,1,2,1, 2,2,2, 3,2,1, 2,2,1, 2,2,1, 3,2,3, 5,2,2, 3,2,2, 2,2,2, 3,2,1, 3,2,1, 
3,2,4, 1,3,1,7,2,1,5,2,2,3,2,2,5,2,4,1,2,2,2,2,4,1,3,1,7,2,1,5,2,2,3,2,2,5,2,4,2,2,2,3,2,4,
6,1,1,1,2,1,2,2,2,3,2,1,2,1,1,2,2,1,3,2,3,2,2,2,3,2,1,5,2,1,5,2,1,7,1,3,5,1,1,6,1,3,6,1,4,
0,0,0
};

//--------------------------------------

void t0int() interrupt 1 	//T0中断程序，控制发音的音调
{
	TR0 = 0; 			 	//先关闭T0
	speaker = !speaker;  	//输出方波, 发音
	TH0 = timer0h; 		 	//下次的中断时间, 这个时间, 控制音调高低
	TL0 = timer0l;
	TR0 = 1; 			 	//启动T0
}
//--------------------------------------
void delay(unsigned char t) //延时程序，控制发音的时间长度
{
	unsigned char t1;
	unsigned long t2;
	for(t1 = 0; t1 < t; t1++) //双重循环, 共延时t个半拍
	for(t2 = 0; t2 < 4000; t2++); //延时期间, 可进入T0中断去发音 //原来的数值为8000；
	TR0 = 0; 						//关闭T0, 停止发音
}
//--------------------------------------
void song() //演奏一个音符
	{
	TH0 = timer0h; //控制音调
	TL0 = timer0l;
	TR0 = 1; //启动T0, 由T0输出方波去发音
	delay(time); //控制时间长度
	}
//--------------------------------------
void led(unsigned char i)  //驱动LED闪烁
{
	switch(i)
		{
		  case 1:P2 = 0x80;break;
		  case 2:P2 = 0x40;break;
		  case 3:P2 = 0x20;break;
		  case 4:P2 = 0x10;break;
		  case 5:P2 = 0x08;break;
		  case 6:P2 = 0x04;break;
		  case 7:P2 = 0x02;break;
		  default:break;
		}
}
//--------------------------------------
void main(void)
{
	unsigned char k, i;
	TMOD = 1; //置T0定时工作方式1
	ET0 = 1; //开T0中断
	EA = 1; //开CPU中断
	while(1) 
	{
		i = 0;
		time = 1; 
		while(time) 
		{
			k = hd[i] + 7 * hd[i + 1] - 1;
			//第i个是音符, 第i+1个是第几个八度
			led(hd[i]);//点亮对应的灯
			timer0h = FREQH[k]; //从数据表中读出频率数值
			timer0l = FREQL[k]; //实际上, 是定时的时间长度
			time = hd[i + 2]; //读出时间长度数值
			i += 3;
			song(); //发出一个音符
			
		} 
	} 
}