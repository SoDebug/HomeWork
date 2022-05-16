   .sect ".vectors"
   .ref _c_int00
RSVECT:	 BD _c_int00	; Reset Vector
    nop
    nop
nmi:
        rete
  nop
  nop
  nop
;software interrupts
sint17          .space 4*16
sint18          .space 4*16
sint19          .space 4*16
sint20          .space 4*16
sint21          .space 4*16
sint22          .space 4*16
sint23          .space 4*16
sint24          .space 4*16
sint25          .space 4*16
sint26          .space 4*16
sint27          .space 4*16
sint28          .space 4*16
sint29          .space 4*16
sint30          .space 4*16
int0: rete
  nop
  nop
  nop
int1: rete
  nop
  nop
  nop
int2: rete
  nop
  nop
  nop
tint: rete
  nop
  nop
  nop
rint0:rete
   nop
   nop
   nop
xint0:rete
   nop
   nop
   nop
rint2:rete
   nop
   nop
   nop
xint2:rete
   nop
   nop
   nop
int3:rete
   nop
   nop
   nop
hpint: rete
  nop
  nop
  nop
rint1: rete
  nop
  nop
  nop
xint1: rete
  nop
  nop
  nop
dmac4: rete
  nop
  nop
  nop
dmac5: rete
  nop
  nop
  nop
rsvd1:  rete
        nop
        nop
        nop
rsvd2:  rete
        nop
        nop
        nop
 .end
