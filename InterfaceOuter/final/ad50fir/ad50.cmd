-stack 200

/******************************************************************************/
/* File Name: 2407_PM.cmd */
/*2002.4.14	REV 1.5 */
/******************************************************************************/    
                     

                     
MEMORY
{
PAGE 0: /* PROGRAM MEMORY */
	VECS:	origin=0ff80h, length=0080h
	PROG:    origin =  1000h, length = 3000h
PAGE 1: /* DATA MEMORY */
	
	DRAM_1 :ORIGIN=0080H , LENGTH=1f80H 
	DMA_DATA :ORIGIN=2000h , LENGTH=6000h 
	 
PAGE 2: /* I/O MEMORY */
	IO_EX :ORIGIN=0000h , LENGTH=0FFF0h /* External I/O mapped peripherals */
	IO_IN :ORIGIN=0FFF0h, LENGTH=0Fh /* On¨Cchip I/O mapped peripherals */
}   

SECTIONS
{
	/*.reset   :{} > VECS PAGE 0*/
	.vectors :{} > VECS PAGE 0    
	.text :{} > PROG PAGE 0
	.cinit : {} >PROG PAGE 0
	.data :{} > DRAM_1 PAGE 1	
	.stack :{} >DRAM_1 PAGE 1	/*ÏµÍ³¶ÑÕ»,for C language */
	.bss :{} > DRAM_1 PAGE 1
	.const :{} > DRAM_1 PAGE 1
 	coffbuf :{} > DRAM_1 PAGE 1
}
