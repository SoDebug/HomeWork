/******************************************************************************/
/* File Name: ledtest.cmd */
/*2003.12.14	REV 1.0 */
/******************************************************************************/    
                     
-o   ledtest.out
-m   ledtest.map
-i dir
                    
MEMORY
{
PAGE 0: /* PROGRAM MEMORY */
	VECS:	origin=0080h, length=0080h
	PROG:    origin =  0100h, length = 0f00h
PAGE 1: /* DATA MEMORY */
	
	DRAM_1 :ORIGIN=1000H , LENGTH=1000H 
	DMA_DATA :ORIGIN=3000h , LENGTH=0C000h 
	 
PAGE 2: /* I/O MEMORY */
	IO_EX :ORIGIN=0000h , LENGTH=0FFF0h /* External I/O mapped peripherals */
	IO_IN :ORIGIN=0FFF0h, LENGTH=0Fh /* On¨Cchip I/O mapped peripherals */
}   

SECTIONS
{
	/*.reset   :{} > VECS PAGE 0/**/
	.vectors :> VECS PAGE 0  /**/  
	.text :> PROG PAGE 0
	.data :> DRAM_1 PAGE 1
	stack :> DRAM_1 PAGE 1	/*ÏµÍ³¶ÑÕ» */
	.bss :> DRAM_1 PAGE 1
	buf	 :> DMA_DATA PAGE 1
}

