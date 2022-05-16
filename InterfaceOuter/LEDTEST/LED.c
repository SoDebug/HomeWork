//////////////////////////////////////////////////////////
//ʵ�����ƣ�2812ʵ�����߶�����ܻ���ʵ��---OK!              
//                                                      
//ʱ�䣺2011��07��29�� 
// v2.0                                
//////////////////////////////////////////////////////////

#define  CPLDport2000  port2000//����CPLDָ���ַ
ioport unsigned CPLDport2000;

#define  LED1 port3000//LED1�ĵ�ַ
ioport unsigned LED1;

#define  LED2 port3001//LED2�ĵ�ַ
ioport unsigned LED2;

#define  LED3 port3002//LED3�ĵ�ַ
ioport unsigned LED3;

#define  LED4 port3003//LED4�ĵ�ַ
ioport unsigned LED4;

#define  LED5 port3004//LED5�ĵ�ַ
ioport unsigned LED5;

#define  LED6 port3005//LED6�ĵ�ַ
ioport unsigned LED6;

#define  LED7 port3006//LED7�ĵ�ַ
ioport unsigned LED7;

#define  LED8 port3007//LED8�ĵ�ַ
ioport unsigned LED8;

void delay(unsigned int k);

#define IMR (volatile unsigned int *) 0x0000 //Interrupt mask register
#define IFR (volatile unsigned int *) 0x0001 //1 Interrupt flag register
#define PMST (volatile unsigned int *) 0x001D //��PMST�Ĵ�����ֵ
#define CLKMD (volatile unsigned int *) 0x0058//��CLKMD�Ĵ�����ֵ 
#define SWCR  (volatile unsigned int *) 0x002B//��SWCR�Ĵ�����ֵ
#define SWWSR (volatile unsigned int *) 0x0028//��SWWSR�Ĵ�����ֵ
#define BSCR  (volatile unsigned int *) 0x0029//��BSCR�Ĵ�����ֵ

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
/*-*-*-*-*-*-*-*-��������ܶ��ձ�*-*-*-*-*-*-*-*-
0x0111 0111=0x77 "0"	0x0001 0100=0x14 "1"
0x1011 0011=0xb3 "2"	0x1011 0110=0xb6 "3"
0x1101 0100=0xd4 "4"	0x1110 0110=0xe6 "5"
0x1110 0111=0xe7 "6"	0x0011 0100=0x34 "7"
0x1111 0111=0xf7 "8"	0x1111 0110=0xf6 "9"
0x1111 0101=0xf5 "A"	0x1100 0111=0xc7 "b"
0x0110 0011=0x63 "c"	0x1001 0111=0x97 "d"
0x1110 0011=0xe3 "E"	0x1110 0001=0xe1 "F"
*-*-*-*-*-*-*-*-��������ܶ��ձ�*-*-*-*-*-*-*-*-*/
  asm(" SSBX INTM ");  /// Disable all interrupt*/
    InitDSP();
   CPLDport2000=0x0;//����CPLD��ַ����
   LED1=0x0;//���¶�8��LED�Ƶ�ַ����
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
	    LED1=0x1c;//��һ������ܸ�����1
	    delay(60000);
	    LED2=0xbb;//�ڶ�������ܸ�����2
	    delay(60000);
	    LED3=0xbe;//����������ܸ�����3
	    delay(60000);
	    LED4=0xdc;//���ĸ�����ܸ�����4
	    delay(60000);
	    LED5=0xee;//���������ܸ�����5
	    delay(60000);
	    LED6=0xef;//����������ܸ�����6
	    delay(60000);
	    LED7=0x3c;//���߸�����ܸ�����7
	    delay(60000);
	    LED8=0xff;//�ڰ˸�����ܸ�����8
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
//��ʱ����  
void delay(unsigned int k)
{
 unsigned int i;
 for(i=0;i<k;i++) ;
}

