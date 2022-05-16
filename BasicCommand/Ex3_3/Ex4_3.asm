		.mmregs
		.global _c_int00
		
STACK	.usect	"STACK", 10H
		.bss	x, 1
		.bss	y, 1
		.bss	z, 1
		.bss	d, 1
		.bss	e, 1
		.bss	f, 1
		.def	start
		.data
table:	.word	0123H		; x
		.word	1027H		; y
		.word	0			; z
		.word	1020H		; d
		.word	0345H		; e
		.word	0			; f

		.text
_c_int00:
		STM     #STACK+10,	SP
		B 		start
				
start:	LD		#0, A			;¿€º”∆˜A÷√0
		ST		#0, AR1			;AR1÷√0
		LD		#0, B			;B÷√0
		ST		#0, AR2			;AR2÷√0
		STM		#x, AR1
		RPT		#5
		MVPD	table, *AR1+
		STM		#x, AR5
		STM		#d, AR2
		LD		#0, ASM
		LD		*AR5+,	16, A
		ADD		*AR5+,	16, A
;		code, which are modified
		STH		A, *AR5
		LD		*AR2+, 16, B
;		code, which are modified
;		ST		A, *AR5
;		|| LD	*AR2+, 	B
		ADD		*AR2+,	16, B
		STH		B, *AR2
end:	B		end
		.end