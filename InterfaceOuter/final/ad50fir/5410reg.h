
//#define PMST    * (volatile unsigned int *) 0x001D

#define IMR * (volatile unsigned int *) 0x0000 //Interrupt mask register
#define IFR * (volatile unsigned int *) 0x0001 //1 Interrupt flag register
// Reserved for testing
/*
ST0 6 6 Status register 0
ST1 7 7 Status register 1
AL 8 8 Accumulator A low word (15¨C0)
AH 9 9 Accumulator A high word (31¨C16)
AG 10 A Accumulator A guard bits (39¨C32)
BL 11 B Accumulator B low word (15¨C0)
BH 12 C Accumulator B high word (31¨C16)
BG 13 D Accumulator B guard bits (39¨C32)
TREG 14 E Temporary register
TRN 15 F Transition register
AR0 16 10 Auxiliary register 0
AR1 17 11 Auxiliary register 1
AR2 18 12 Auxiliary register 2
AR3 19 13 Auxiliary register 3
AR4 20 14 Auxiliary register 4
AR5 21 15 Auxiliary register 5
AR6 22 16 Auxiliary register 6
AR7 23 17 Auxiliary register 7
SP 24 18 Stack pointer register
BK 25 19 Circular buffer size register
BRC 26 1A Block repeat counter
RSA 27 1B Block repeat start address
REA 28 1C Block repeat end address
*/
#define PMST * (volatile unsigned int *) 0x001D //Processor mode status (PMST) register
//XPC 30 1E Extended program page register
// 31 1F Reserved

//#define IMR    * (volatile unsigned int *) 0x0004 

#define DRR20 * (volatile unsigned int *)	0x0020	//-	McBSP #0	McBSP0 data receive register 2
#define DRR10 * (volatile unsigned int *)	0x0021	//-	McBSP #0	McBSP0 data receive register 1
#define DXR20 * (volatile unsigned int *)	0x0022	//-	McBSP #0	McBSP0 data transmit register 2
#define DXR10 * (volatile unsigned int *)	0x0023	//-	McBSP #0	McBSP0 data transmit register 1
#define SPSA0 * (volatile unsigned int *)	0x0038	//-	McBSP #0	McBSP0 sub-address register

#define MCBSP0 * (volatile unsigned int *)	0x0039	//-	McBSP #0	
/*
#define SPCR12 * (volatile unsigned int *)	0x0035	//00h	Serial port control register 1
#define SPCR22 * (volatile unsigned int *)	0x0035	//01h	Serial port control register 2
#define RCR12 * (volatile unsigned int *)	0x0035	//02h	Receive control register 1
#define RCR22 * (volatile unsigned int *)	0x0035	//03h	Receive control register 2
#define XCR12 * (volatile unsigned int *)	0x0035	//04h	Transmit control register 1
#define XCR22 * (volatile unsigned int *)	0x0035	//05h	Transmit control register 2
#define SRGR12 * (volatile unsigned int *)	0x0035	//06h	Sample rate generator register 1
#define SRGR22 * (volatile unsigned int *)	0x0035	//07h	Sample rate generator register 2
#define MCR12 * (volatile unsigned int *)	0x0035	//08h	Multichannel register 1
#define MCR22 * (volatile unsigned int *)	0x0035	//09h	Multichannel register 2
#define RCERA2 * (volatile unsigned int *)	0x0035	//0Ah	Receive channel enable register partition A
#define RCERB2 * (volatile unsigned int *)	0x0035	//0Bh	Receive channel enable register partition B
#define XCERA2 * (volatile unsigned int *)	0x0035	//0Ch	Transmit channel enable register partition A
#define XCERB2 * (volatile unsigned int *)	0x0035	//0Dh	Transmit channel enable register partition B
#define PCR2 * (volatile unsigned int *)	0x0035	//0Eh	Pin control register

*/
#define DMPREC * (volatile unsigned int *)	0x0054	//-	DMA	DMA channel priority and enable control register
#define DMSA * (volatile unsigned int *)	0x0055	//-	DMA	DMA channel sub-address register

#define DMSRC0 * (volatile unsigned int *)	0x0056///57h†	00h	DMA	DMA channel 0 source address register
#define DMDST0 * (volatile unsigned int *)	0x0056///57h†	01h	DMA	DMA channel 0 destination address register
#define DMCTR0 * (volatile unsigned int *)	0x0056///57h†	02h	DMA	DMA channel 0 element count register
#define DMSFC0 * (volatile unsigned int *)	0x0056///57h†	03h	DMA	DMA channel 0 sync select and frame count register
#define DMMCR0 * (volatile unsigned int *)	0x0056///57h†	04h	DMA	DMA channel 0 transfer mode control register

#define DMSRC1 * (volatile unsigned int *)	0x0056
#define DMDST1 * (volatile unsigned int *)	0x0056
#define DMCTR1 * (volatile unsigned int *)	0x0056
#define DMSFC1 * (volatile unsigned int *)	0x0056
#define DMMCR1 * (volatile unsigned int *)	0x0056

#define DMSRC2 * (volatile unsigned int *)	0x0056
#define DMDST2 * (volatile unsigned int *)	0x0056
#define DMCTR2 * (volatile unsigned int *)	0x0056
#define DMSFC2 * (volatile unsigned int *)	0x0056
#define DMMCR2 * (volatile unsigned int *)	0x0056

#define DMSRC3 * (volatile unsigned int *)	0x0056
#define DMDST3 * (volatile unsigned int *)	0x0056
#define DMCTR3 * (volatile unsigned int *)	0x0056
#define DMSFC3 * (volatile unsigned int *)	0x0056
#define DMMCR3 * (volatile unsigned int *)	0x0056

#define DMSRC4 * (volatile unsigned int *)	0x0056
#define DMDST4 * (volatile unsigned int *)	0x0056
#define DMCTR4 * (volatile unsigned int *)	0x0056
#define DMSFC4 * (volatile unsigned int *)	0x0056
#define DMMCR4 * (volatile unsigned int *)	0x0056
#define DMSRC5 * (volatile unsigned int *)	0x0056
#define DMDST5 * (volatile unsigned int *)	0x0056
#define DMCTR5 * (volatile unsigned int *)	0x0056
#define DMSFC5 * (volatile unsigned int *)	0x0056
#define DMMCR5 * (volatile unsigned int *)	0x0056

#define DMIDX0 * (volatile unsigned int *)  0x0057

#define DMPERC * (volatile unsigned int *)  0x0054

