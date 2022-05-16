#include "5410reg.h"
#include "stdio.h"

#define fc_clock port2000
#define LowPass 0
#define HighPass 1
#define BandPass 2
ioport unsigned fc_clock;
ioport unsigned temp;

//McBSP2��ʼ����
const unsigned short init_tblx[][2]=
{
{0,0x0000},
{1,0x0200},
//����ĿʹMcBSP1���ڸ�λ״̬
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
//����ĿʹMcBSP ��ʼ����
{0,0x0001},
{1,0x0043}

};

short *init_tbl=(short*)init_tblx;
int mtmp;
int Type;
//��ʱ����
void Delay()
{
    int temp,ft;
    for(ft=0;ft<100;ft++)
    	for (temp=0;temp<1000;temp++) ;
}

//����ʱ����
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

//��ʼ��MCBSP
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
//��ʼ��DMA
void initDMA()
{
	
	IMR=0X1000;        //DMA  4ͨ���ж�ʹ��
	
	asm("	rsbx intm");  //  �������п������ж�
	
	DMSA=0x0014;         // ѡ��DMA4ͨ��
	DMSRC1=0x0031;      //  ���ô���1���ն�ΪDMA�¼���Դ��ַ
	DMDST1=0x2000;      //   ����DMA�¼���Ŀ�ĵ�ַ
	DMCTR1=0x3000;       //����ֱ�Ӵ������ݸ���
	DMSFC1=0x5000;     //  ����DMAΪ��֡ģʽ��Դ��ַ������Ŀ�ĵ�ַ��57h��ֵ����
	
    DMSA=0x0020;
    DMIDX0=0x0001;     //����Ŀ�ĵ�ַΪ�Զ���1����
    DMPERC=0x1090;     // ����ͨ��4Ϊ�����ȼ���ʹ��ͨ��4

}

//д����
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
    DXR10=Data;   //��TLC320AD50C�ļĴ������
    SPSA0=0x0001;  //
    while(  (MCBSP0&0x0002)==0);  //�����Ƿ�TLC320AD50C����
    asm (" nop");
    asm (" nop");
    ShortDelay();
    asm (" nop");
}
//��ʼ��AD50
void initAD50()
{
	//int tmp;
	WriteAD50(0x0180);   //��TLC320AD50C�ļĴ���1��̣�ʹ�临λ
	ShortDelay();
	asm (" nop");
	WriteAD50(0x0101);    //TLC320AD50C���븴λ�������üĴ���1��ʹINP��INMΪ����
	asm (" nop");
	WriteAD50(0x0210);    //����TLC320AD50C�Ĵ���2��ʹ�绰ģʽ��Ч
	asm (" nop");

/*-*-*-*-*-*-*-*-*-*-*-*-* Located:User Modified *-*-*-*-*-*-*-*-*-*-*-*-*/
	WriteAD50(0x0420);     //����TLC320AD50C�Ĵ���4
/*-*-*-*-*-*-*-*-*-*-*-*-* Located:User Modified *-*-*-*-*-*-*-*-*-*-*-*-*/

	asm (" nop");
	asm (" nop");
	WriteAD50(0x0312);      //����TLC320AD50C�Ĵ���3��ʹ��0���ӻ�
	asm("	nop");	 	
}

//��ʼ��DSP
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
	Type=BandPass;//�˲�������ѡ��
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
    	mtmp=DRR10;	//��������
   		FIR321();//�����˲�
    	DXR10=mtmp;//��������
    }
	
}     	
