//////////////////////////////////////////////////////////
//实验名称：2812实验箱七段数码管基本实验---OK!              
//                                                      
//时间：2011年07月29日 
// v2.0                                
//////////////////////////////////////////////////////////

#define  CPLDport2000  port2000//定义CPLD指向地址
ioport unsigned CPLDport2000;

#define  LED1 port3000//LED1的地址
ioport unsigned LED1;

#define  LED2 port3001//LED2的地址
ioport unsigned LED2;

#define  LED3 port3002//LED3的地址
ioport unsigned LED3;

#define  LED4 port3003//LED4的地址
ioport unsigned LED4;

#define  LED5 port3004//LED5的地址
ioport unsigned LED5;

#define  LED6 port3005//LED6的地址
ioport unsigned LED6;

#define  LED7 port3006//LED7的地址
ioport unsigned LED7;

#define  LED8 port3007//LED8的地址
ioport unsigned LED8;

void delay(unsigned int k);

#define IMR (volatile unsigned int *) 0x0000 //Interrupt mask register
#define IFR (volatile unsigned int *) 0x0001 //1 Interrupt flag register
#define PMST (volatile unsigned int *) 0x001D //给PMST寄存器赋值
#define CLKMD (volatile unsigned int *) 0x0058//给CLKMD寄存器赋值 
#define SWCR  (volatile unsigned int *) 0x002B//给SWCR寄存器赋值
#define SWWSR (volatile unsigned int *) 0x0028//给SWWSR寄存器赋值
#define BSCR  (volatile unsigned int *) 0x0029//给BSCR寄存器赋值

void InitDSP()
{
	int i;
	*CLKMD = 0x0;
	while(*CLKMD & 0x0001){};
	*CLKMD = 0xf3ef;//0xf7e7
	for(i=0;i<1000;i++);
	*PMST = 0x00E3;
	*SWWSR = 0x7000;
	*SWCR = 0x1;			
}

void main(void)
{
	unsigned char DELED_SEG[16]={0x77,0x14,0xb3,0xb6,0xd4,0xe6,0xe7,0x34,0xf7,0xf6,0xf5,0xc7,0x63,0x97,0xe3,0xe1};
	int i;
/*-*-*-*-*-*-*-*-共阳数码管对照表*-*-*-*-*-*-*-*-
0x0111 0111=0x77 "0"	0x0001 0100=0x14 "1"
0x1011 0011=0xb3 "2"	0x1011 0110=0xb6 "3"
0x1101 0100=0xd4 "4"	0x1110 0110=0xe6 "5"
0x1110 0111=0xe7 "6"	0x0011 0100=0x34 "7"
0x1111 0111=0xf7 "8"	0x1111 0110=0xf6 "9"
0x1111 0101=0xf5 "A"	0x1100 0111=0xc7 "b"
0x0110 0011=0x63 "c"	0x1001 0111=0x97 "d"
0x1110 0011=0xe3 "E"	0x1110 0001=0xe1 "F"
*-*-*-*-*-*-*-*-共阳数码管对照表*-*-*-*-*-*-*-*-*/
  asm(" SSBX INTM ");  /// Disable all interrupt*/
    InitDSP();
   CPLDport2000=0x0;//定义CPLD地址清零
   LED1=0x0;//以下对8个LED灯地址清零
   LED2=0x0;
   LED3=0x0;
   LED4=0x0;
   LED5=0x0;
   LED6=0x0;
   LED7=0x0;
   LED8=0x0;
   
	for(;;)
	{
		for(i=0;i<16;i++) {
			LED1=DELED_SEG[i];
			LED2=DELED_SEG[i];
			LED3=DELED_SEG[i];
			LED4=DELED_SEG[i];
			LED5=DELED_SEG[i];
			LED6=DELED_SEG[i];
			LED7=DELED_SEG[i];
			LED8=DELED_SEG[i];
			delay(60000);
			delay(60000);
			delay(60000);
			delay(60000);
			delay(60000);
			delay(60000);
			delay(60000);
			delay(60000);
			LED1=0x0;
	   		LED2=0x0;
	    	LED3=0x0;
	    	LED4=0x0;
	   		LED5=0x0;
	    	LED6=0x0;
	    	LED7=0x0;
	    	LED8=0x0;
			delay(8000);
		}
		/*
	    LED1=0x1c;//第一个数码管给数据1
	    delay(60000);
	    LED2=0xbb;//第二个数码管给数据2
	    delay(60000);
	    LED3=0xbe;//第三个数码管给数据3
	    delay(60000);
	    LED4=0xdc;//第四个数码管给数据4
	    delay(60000);
	    LED5=0xee;//第五个数码管给数据5
	    delay(60000);
	    LED6=0xef;//第六个数码管给数据6
	    delay(60000);
	    LED7=0x3c;//第七个数码管给数据7
	    delay(60000);
	    LED8=0xff;//第八个数码管给数据8
	    delay(60000);
	    LED1=0x0;
	    LED2=0x0;
	    LED3=0x0;
	    LED4=0x0;
	    LED5=0x0;
	    LED6=0x0;
	    LED7=0x0;
	    LED8=0x0;
	    delay(8000);
		*/
	}

}
//延时函数  
void delay(unsigned int k)
{
 unsigned int i;
 for(i=0;i<k;i++) ;
}

