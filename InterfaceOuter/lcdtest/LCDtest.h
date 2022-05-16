#define IMR (volatile unsigned int *) 0x0000 //Interrupt mask register
#define IFR (volatile unsigned int *) 0x0001 //1 Interrupt flag register
#define PMST (volatile unsigned int *) 0x001D 
#define CLKMD (volatile unsigned int *) 0x0058 
#define SWCR  (volatile unsigned int *) 0x002B
#define SWWSR (volatile unsigned int *) 0x0028
#define BSCR  (volatile unsigned int *) 0x0029
#define commandport port2000
ioport unsigned commandport;
#define noporti1 port5002
ioport unsigned noporti1;
#define noporti2 port5001
ioport unsigned noporti2;
#define noportd2 port5005
ioport unsigned noportd2;
#define noportd1 port5006
ioport unsigned noportd1;


#define inport2 port5011
ioport unsigned inport2;
#define inport1 port5012
ioport unsigned inport1;
#define dataport1 port5016
ioport unsigned dataport1;
#define dataport2 port5015
ioport unsigned dataport2;
#define keyscanport port5040
ioport unsigned keyscanport;

