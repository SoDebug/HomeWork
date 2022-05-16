	.ref _mtmp,_Type
	.mmregs
	.global _FIR321,_initfir
	.data
	.bss f32_p,1
	.bss temp,1
	
	.align 256
COFF1_FIR32: 
  
;---newest
;3K低通	
;	.word  -15,    -28,     -6,     31,     37,    -10,    -64,    -44,     54	
;	.word  115,     28,   -140,   -166,     46,    269,    178,   -206,   -422	
;	.word	-97,   477,    551,   -149,   -872,   -576,    679,   1429,    345
;	.word -1842,  -2412,    803,   6794,  11599,  11599,   6794,    803,  -2412
;	.word -1842,    345,   1429,    679,   -576,   -872,   -149,    551,    477
;	.word -97,   -422,   -206,    178,    269,     46,   -166,   -140,     28
;	.word 115,     54,    -44,    -64,    -10,     37,     31,     -6,    -28,	-15
;1K 高通      
;	.word 11,     22,     33,     43,     48,     45,     29,      0    
;	.word  -43,    -95,   -148,   -190,   -206,   -185,   -116,      0,    156
;	.word  332,    499,    622,    663,    587,    369,      0,   -511,  -1134
;	.word  -1823,  -2517,  -3149,  -3656,  -3983,  28676,  -3983,  -3656,  -3149
;	.word  -2517,  -1823,  -1134,   -511,      0,    369,    587,    663,    622 
;	.word 499,    332,    156,      0,   -116,   -185,   -206,   -190,   -148
;	.word -95,    -43,      0,     29,     45,     48,     43,     33,     22,   11,   0
;带通1k-3K     	
;	.word -10,    -12,     20,     67,     80,     34,    -28,    -29,     35
;	.word 50,    -90,   -305,   -361,   -149,    117,    115,   -134,   -183   
;	.word 317,   1041,   1201,    488,   -378,   -374,    441,    620,  -1128
;	.word -4019,  -5264,  -2624,   2949,   7534,   7534,   2949,  -2624,  -5264 
;	.word  -4019,  -1128,    620,    441,   -374,   -378,    488,   1201,   1041  
;	.word 317,   -183,   -134,    115,    117,   -149,   -361,   -305, -90
;	.word  50,     35,    -29,    -28,     34,     80,     67,     20,    -12,	-10
;1K低通
	.word  	-6,  	-16,  	-27,  	-37,  	-44,  	-45,  	-37,  	-16,  	18  
	.word 	65,  	117,  	165,  	195,  	195,  	152,  	62,  	-73,  	-240
	.word 	-414,  	-564,  	-651,  	-638,  	-495,  	-203,  	238,  	810,  	1474
	.word 	2175,  	2849,  	3428,  	3853,  	4078,  	4078,  	3853,	3428,  	2849 
	.word 	2175,  	1474,  	810,  	238,  	-203,  	-495,  	-638,  	-651,  	-564
	.word 	-414,  	-240,  	-73,  	62,  	152,  	195,  	195,  	165,  	117
	.word 	65,  	18,  	-16,  	-37,  	-45,  	-44,  	-37,  	-27,  	-16,  -6
;2K高通
	.word 	-1,  	19,  	30,  	25,  	-1,  	-37,  	-64,  	-55,  	-1 
	.word 	79,  	134,  	113,  	-1,  	-158,  	-261,  	-215,  	-1,  	287  
	.word 	469,  	382,  	-1,  	-508,  	-831,  	-682,  	-1,  	943,  	1604 
	.word	1395,  	-1,  	-2411,  -5171,  -7362,	24583,  -7362,  -5171,  -2411 
	.word 	-1,  	1395,  	1604,  	943,  	-1,  	-682,  	-831,  	-508,  	-1 
	.word	382,  	469,  	287,  	-1,  	-215,  	-261,  	-158,  	-1,  	113
	.word	134,  	79,  	-1,  	-55,  	-64,  	-37,  	-1,  	25,  	30,  19,  -1
;1K-2K带通
	.word 	-5,  	-11,  	-3,  	21,  	59,  	93,  	96,  	45,  	-56 
	.word	-173,  	-247,  	-229,  	-119,  	21,  	100,  	59,  	-70,  	-158 
	.word	-46,  	341,  	898,  	1337,  	1308,  	596,  	-703,  	-2144,  -3092 
	.word	-3005,  -1727,  378,  	2537,  	3895,  	3895,  	2537,  	378,  	-1727 
	.word	-3005,  -3092,  -2144,  -703,  	596,  	1308,  	1337,  	898,  	341
	.word	-46,  	-158,  	-70,  	59,  	100,  	21,  	-119,  	-229,  	-247
	.word	-173,  	-56,  	45,  	96,  	93,  	59,  	21,  	-3,  	-11,  -5


	 	
DATA_P .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		.word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

    
	.text
_initfir:
	PSHM	AR3
	STM		#DATA_P,	AR3
	RPTZ	A,	63
	STL		A,	*AR3+
	LD      #DATA_P,	A
	STL     A,	*(f32_p)
	POPM	AR3
	RET	
_FIR321:	
	PSHM	AR3
	PSHM	AR4
	PSHM	AR5
	PSHM	ST1
	PSHM	ST0
	.asg 	AR4,FIR_DATA_P
	.asg 	AR5,FIR_COFF_P	
	ssbx  SXM							;data sign ext. before usage
    rsbx  OVM							;no saturation of accu if overflow
	ssbx	FRCT
	LD		#COFF1_FIR32,	DP
	RSBX	CPL
	STM 	#63,BK 			; FIR circular bffr size
	STM		#1,	AR0
	MVDM   f32_p,FIR_DATA_P
	NOP
	NOP
	LD     *(_Type),	A
	ADD    #COFF1_FIR32,	A
	STLM	A,FIR_COFF_P		
	NOP
	NOP
	LD     *(_mtmp),	A
 
fir_filter:
	STL A,*FIR_DATA_P+% ; replace oldest sample with newest
						; sample
	MVMD    FIR_DATA_P,f32_p  
	NOP
	NOP
	RPTZ A,#63
	MAC *FIR_DATA_P+0%,*FIR_COFF_P+0%,A ; filtering
	NOP
	NOP
	STH 	A, 	*(_mtmp)   
	nop
	nop
	POPM	ST0
	POPM	ST1
	POPM	AR5
	POPM	AR4
	POPM	AR3
	retd
	nop
	nop

	.end