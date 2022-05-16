#include "5410reg.h"
#include "stdio.h"

#define fc_clock port2000
#define LowPass 0
#define HighPass 1
#define BandPass 2
ioport unsigned fc_clock;
ioport unsigned temp;

//McBSP2初始化表
const unsigned short init_tblx[][2]=
{
{0,0x0000},
{1,0x0200},
//上两目使McBSP1处于复位状态
{2,0x0040},
{3,0x0000},
{4,0x0040},
{5,0x0000},

{6,0x0101},
{7,0x2000},
{8,0x0000},
{9,0x0000},
{10,0x0000},
{11,0x0000},
{12,0x0000},
{13,0x0000},
{14,0x000c},
//下两目使McBSP 开始工作
{0,0x0001},
{1,0x0043}

};

short *init_tbl=(short*)init_tblx;
int mtmp;
int Type;
//延时函数
void Delay()
{
    int temp,ft;
    for(ft=0;ft<100;ft++)
    	for (temp=0;temp<1000;temp++) ;
}

//短延时函数
void ShortDelay()
{
	int tmp;
	for(tmp=0;tmp<100;tmp++) ;
}
void MainDelay(unsigned int count)
{
	int tmp;
	for(tmp=0;tmp<count;tmp++);
}

//初始化MCBSP
void initMCBSP()
{
int i;
	for(i=0;i<17;i++)
	{
		SPSA0=init_tbl[i*2+0];
		MCBSP0  =init_tbl[i*2+1];
	}
	Delay();	
}
//初始化DMA
void initDMA()
{
	
	IMR=0X1000;        //DMA  4通道中断使能
	
	asm("	rsbx intm");  //  开放所有可屏蔽中断
	
	DMSA=0x0014;         // 选择DMA4通道
	DMSRC1=0x0031;      //  设置串口1接收端为DMA事件的源地址
	DMDST1=0x2000;      //   设置DMA事件的目的地址
	DMCTR1=0x3000;       //设置直接传送数据个数
	DMSFC1=0x5000;     //  设置DMA为多帧模式，源地址不调整目的地址按57h的值调整
	
    DMSA=0x0020;
    DMIDX0=0x0001;     //设置目的地址为自动加1调整
    DMPERC=0x1090;     // 设置通道4为高优先级并使能通道4

}

//写数据
void WriteAD50(unsigned int Data)
{
	int tmp;
	
	tmp=fc_clock;    
    while((fc_clock&0x40)==0) ;
    asm (" nop");
    asm (" nop");    
    fc_clock=0x12;           
    asm (" nop");          
    tmp=fc_clock;
    while((tmp&0x40)) tmp=fc_clock;
     //asm (" nop");    
    tmp=fc_clock;
    while((tmp&0x40)==0) tmp=fc_clock;
    fc_clock=0x2;
    asm (" nop");
    asm (" nop");
    DXR10=Data;   //给TLC320AD50C的寄存器编程
    SPSA0=0x0001;  //
    while(  (MCBSP0&0x0002)==0);  //数据是否被TLC320AD50C接收
    asm (" nop");
    asm (" nop");
    ShortDelay();
    asm (" nop");
}
//初始化AD50
void initAD50()
{
	//int tmp;
	WriteAD50(0x0180);   //给TLC320AD50C的寄存器1编程，使其复位
	ShortDelay();
	asm (" nop");
	WriteAD50(0x0101);    //TLC320AD50C脱离复位并且设置寄存器1，使INP，INM为输入
	asm (" nop");
	WriteAD50(0x0210);    //设置TLC320AD50C寄存器2，使电话模式无效
	asm (" nop");

/*-*-*-*-*-*-*-*-*-*-*-*-* Located:User Modified *-*-*-*-*-*-*-*-*-*-*-*-*/
	WriteAD50(0x0420);     //设置TLC320AD50C寄存器4
/*-*-*-*-*-*-*-*-*-*-*-*-* Located:User Modified *-*-*-*-*-*-*-*-*-*-*-*-*/

	asm (" nop");
	asm (" nop");
	WriteAD50(0x0312);      //设置TLC320AD50C寄存器3，使带0个从机
	asm("	nop");	 	
}

//初始化DSP
void initDSP()
{
	volatile unsigned int *CLKMD=(volatile unsigned int*)0x58;
	int i;
	*CLKMD=0;
	while((*CLKMD&1)==1);
	*CLKMD=0x17EF;
	while((*CLKMD&1)==0);
    asm(" ssbx intm");
   fc_clock=0x2;
   asm( " nop " );
   asm( " nop " );
   i = fc_clock;
   asm( " nop " );
   asm( " nop " );
   PMST=0xFFE3;
   IFR=0x3fff;
    
} 
     
void main()
{
	Type=BandPass;//滤波器类型选择
	initDSP();
	initMCBSP();
 	initAD50();
 	initDMA();
    initfir();
	Type*=64;
    
    for(;;)
    {
    	SPSA0=0x0000;
    	while((MCBSP0&0x0002)==0);
    	mtmp=DRR10;	//接收数据
   		FIR321();//经过滤波
    	DXR10=mtmp;//发送数据
    }
	
}     	
