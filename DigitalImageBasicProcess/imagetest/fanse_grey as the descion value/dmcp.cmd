-lrts.lib
-heap 8000h	/*origin value = 2000h*/
-stack 1000

MEMORY
{
    PAGE 0: EPROG:      origin = 0x1000,        len = 0x4000
            VECT:       origin = 0x080,        len = 0x80
            
    /*deleted because it hasn't been used,forever. PAGE 1: USERREGS:   origin = 0x5000,          len = 01000*/
    PAGE 1: EDATA:      origin = 0x5000,        len = 0xA000	/*origin value: origin=0x6000,len=0x4000*/
           
}

SECTIONS
{   
  	.my_data: {} > EDATA PAGE 1
    .vectors: {} > VECT  PAGE 0

    .switch:  {} > EPROG PAGE 0
    .text:    {} > EPROG PAGE 0
    .pinit:   {} > EPROG PAGE 0
    .sysinit: {} > EPROG PAGE 0
    .cinit:   {} > EPROG PAGE 0
    
    .const:   {} > EDATA PAGE 1
    .bss:     {} > EDATA PAGE 1
    .stack:   {} > EDATA PAGE 1
    .sysmem:  {} > EDATA PAGE 1
    .cio:{} > EDATA PAGE 1
}
