Ex4_2.obj

-m Ex4_2.map 
-o Ex4_2.out

MEMORY
{
   PAGE 0:  
   	PROG:  org=01000H  len=0100h
   
   PAGE 1:  
   	DATA:	org=0060H	len=0100H
   	
}

SECTIONS
{
   .text   :> PROG PAGE 0
   .data   :> PROG PAGE 0
   .bss    :> DATA PAGE 1
   STACK   :> DATA PAGE 1
}
