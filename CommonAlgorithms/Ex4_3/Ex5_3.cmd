Ex5_3.obj
-c 
-m Ex5_3.map 
-o Ex5_3.out

-lrts.lib
-stack 0x100

MEMORY
{
   PAGE 0:  PROG:    origin =  1a00h, length = 2800h
   PAGE 1:  DATA:    origin =  0200h, length = 1800h
}

SECTIONS
{
   .text   > PROG PAGE 0
   .cinit  > PROG PAGE 0
   .switch > PROG PAGE 0
    vect   > 3f80h PAGE 0
    
   .data   > DATA PAGE 1
   .bss    > DATA PAGE 1
   .const  > DATA PAGE 1
   .sysmem > DATA PAGE 1
   .stack  > DATA PAGE 1
}