#include "LCDTEST.h"
#define NULL -1;

char NumTab[]={
 //李(0) 锦(1) 川(2)

	0x00,0x00,0x00,0x02,0x06,0x06,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x03,0x1F,0x3F,0x03,0x03,0x03,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,
	0x00,0x00,0x02,0x02,0x03,0x07,0x06,0x06,0x0C,0x0D,0x1B,0x31,0x61,0x81,0x01,0xFD,0xFF,0x01,0x81,0xC1,0x61,0x31,0x19,0x0D,0x06,0x02,0x01,0x01,0x00,0x00,0x00,0x00,
	0x00,0x00,0x02,0x06,0x06,0x02,0x02,0x02,0x82,0x82,0x82,0xC2,0x42,0x22,0x1A,0x1F,0x22,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x82,0x82,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x0E,0x0C,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"李",0*/
/* (32 X 32 , 宋体 )*/
	0x00,0x00,0x00,0x00,0x03,0x03,0x02,0x02,0x02,0x02,0x12,0x3A,0x1E,0x02,0x02,0x02,0x03,0x04,0x00,0x01,0x03,0x01,0x01,0x11,0x19,0x3F,0x03,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xFE,0xFF,0x22,0x22,0x22,0x22,0x23,0x23,0x22,0x22,0x22,0x22,0xFF,0x00,0x00,0x00,0x08,0x18,0x08,0x08,0x0F,0x0F,0xC8,0x78,0x0C,0x02,0x00,0x00,
	0x00,0x00,0x00,0x1F,0x1F,0x10,0x10,0x10,0x10,0x10,0xFF,0xFF,0x10,0x10,0x10,0x10,0x10,0x9F,0x3F,0x20,0x60,0x60,0x20,0x20,0xFF,0xFF,0x20,0x20,0x20,0x20,0x00,0x00,
	0x00,0x00,0x00,0xF0,0xF8,0x18,0x10,0x10,0x00,0x00,0xFC,0xFE,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0xC0,0x60,0x30,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,/*"锦",1*/
/* (32 X 32 , 宋体 )*/
	0x00,0x00,0x00,0x00,0x10,0x1F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x1F,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFE,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xFC,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x60,0x18,0x04,0x02,0x00,0x00/*"川",2*/
/* (32 X 32 , 宋体 )*/

};

void InitDSP()
{
	int i;
	*CLKMD = 0x0;
	while(*CLKMD & 0x0001){};
	*CLKMD = 0xf7e0;
	for(i=0;i<1000;i++);
	*PMST = 0x00E3;
	*SWWSR = 0x7000;
	*SWCR = 0x1;			
}
//延时函数
void delay(void)
{
	int i;
	for(i=0;i<10000;i++);
}
//将指令送给LCD的右半屏
void OTUI1(char data)
{
//	for(;;)
	noporti1 = data; //5002   LCD_E = 0
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " ); 
	inport1 = data; //5012   LCD_E = 1
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " ); 
	noporti1 = data;//5002   LCD_E = 0  形成LCD_E的下跳沿！！！
}
//将指令送给LCD的左半屏
void OTUI2(char data)
{
	noporti2 = data;//5001   LCD_E = 0
	asm( " nop " ); 
	asm( " nop " );
	asm( " nop " ); 
	asm( " nop " ); 
	inport2 = data;//5011   LCD_E = 1
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " ); 
	noporti2 = data;//5001   LCD_E = 0  形成LCD_E的下跳沿！！
}
//将数据送给LCD的右半屏
void OUTD1(char data)
{
	noportd1 = data;//5005   LCD_E = 0
	asm( " nop " ); 
	asm( " nop " );
	asm( " nop " ); 
	asm( " nop " ); 
	dataport1 = data;//5015   LCD_E = 1
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " );
	asm( " nop " ); 
	noportd1 = data;//5005   LCD_E = 0   形成LCD_E的下跳沿！！！
}
//将数据送给LCD的左半屏
void OUTD2(char data)
{
	noportd2 = data;//5006   LCD_E = 0
	asm( " nop " ); 
	asm( " nop " );
	asm( " nop " );  
	asm( " nop " ); 
	dataport2 = data;//5016   LCD_E = 1
	asm( " nop " ); 
	asm( " nop " ); 
	asm( " nop " );  
	asm( " nop " ); 
	noportd2 = data;//5006   LCD_E = 0   形成LCD_E的下跳沿！！！
}
//清右半屏
void display_cs0(void)
{
	int i,j;
	OTUI1(0xc0);						//起始行对应行
	for(j=0;j<8;j++)
	{
		OTUI1(0xbf-j);						//确定初始页
		OTUI1(0x40);						//确定初始列
		for(i=0;i<65;i++)
			OUTD1(0x00);
	}		
}

void display_cs1(void)
{
	int i,j;
	OTUI2(0xc0);						//起始行对应行
	for(j=0;j<8;j++)
	{
		OTUI2(0xbf-j);						//确定初始页
		OTUI2(0x40);						//确定初始列
		for(i=0;i<65;i++)
			OUTD2(0x00);
	}		
}

// 初始化LCD
void LCDinit(void)
{	
	OTUI1(0x3e);  //关右半屏显示
	OTUI2(0x3e);  //关左半屏显示
	OTUI1(0x3F);  //开右半屏显示
	OTUI2(0x3F);  //开左半屏显示
	display_cs0();//clear right LCD 
	display_cs1();//clear left LCD 
}

//将要显示的数据在右半屏显示
void Display4(char data,int Row)
{
	int i,j,PageNum;
	int *TabDatap;
	data *= 128;
	TabDatap = (int *)&NumTab[0]; 
	TabDatap += data;
	PageNum = 0xBD;
	for(j=0;j<4;j++)
	 {
		OTUI1(Row);  //确定显示的行
		OTUI1(PageNum);  //确定显示的页
		OTUI1(0xc0);    //确定显示的列
		for(i=0;i<32;i++)
		 {
			OUTD1(*(TabDatap+j*32+i));  //将字模送到右半屏显示
		 }
		PageNum--;
	 }
}

//将要显示的数据在左半屏显示
void Display5(char data,int Row)
{
	int i,j,PageNum;
	int *TabDatap;
	data *= 128;
	TabDatap = (int *)&NumTab[0];
	TabDatap += data;
	PageNum = 0xBD;
	for(j=0;j<4;j++)
	 {
		OTUI2(Row);    //确定显示的行
		OTUI2(PageNum);  //确定显示的页
		OTUI2(0xc0);    //确定显示的列
		for(i=0;i<32;i++)
		{
			OUTD2(*(TabDatap+j*32+i)); //将字模送到左半屏显示
		}
		PageNum--;
	 }
}
void Display(void)
{
	int i;
	
	Display5(0,0x60);  //左半屏显示"百"
	  for(i=0;i<10;i++)
		delay();
	Display5(1,0x40);  //左半屏显示"科"
	  for(i=0;i<10;i++)
		delay();
	Display4(2,0x60);  //右半屏显示"融"
	  for(i=0;i<10;i++)
		delay();
	Display4(3,0x40);  //右半屏显示"创"
	  for(i=0;i<10;i++)
		delay();

	display_cs1();  //清屏
 	display_cs0();
	
	Display5(1,0x60);   //左半屏显示"科"
	  for(i=0;i<10;i++)
		delay();
	Display5(2,0x40);   //左半屏显示"融"
	  for(i=0;i<10;i++)
		delay();
	Display4(3,0x60);   //右半屏显示"创"
	  for(i=0;i<10;i++)
		delay();
	
	display_cs0();   //清屏
	display_cs1();
	
	Display5(2,0x60);   //左半屏显示"融"
	  for(i=0;i<10;i++)
		delay();
	Display5(3,0x40);   //左半屏显示"创"
	  for(i=0;i<10;i++)
		delay();
	
	display_cs0();  //清屏
	display_cs1();
	
	Display5(3,0x60); //左半屏显示"创"
	  for(i=0;i<10;i++)
		delay();
	
	display_cs0(); //清屏
	display_cs1();
}
/*****************************************************************************/
/* main																		 */
/*****************************************************************************/
void main(void)
{
  	asm(" SSBX INTM ");  /// Disable all interrupt*/
 	InitDSP();
    commandport = 0x0;
    asm( " nop " ); 
	asm( " nop " ); 
//    for(;;)
//		inport1 = 0x3f;
    LCDinit(); //初始化液晶屏
    for(;;)
    {
		Display();//显示
	}
	
}


