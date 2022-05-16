		.mmregs
		.global	_c_int00
		
STACK	.usect	"STACK", 10H
		.bss	x, 2		;32位的加数
		.bss	y, 2		;32位的加数
		.bss	z, 2		;32位的和数
		.def	start
		.data
table:	.long	16782345H, 10200347H  ;两个加数的值

		.text
_c_int00:
		STM     #STACK+10,	SP
		B 		start
		
start:	ST		#x, AR2
		RPT		#5
		ST		#0, *AR2+
		STM		#x, AR3
		RPT		#5
		ST		#0, *AR3+
		LD		#0, A
		STM		#x,  AR1	;装入数据
		RPT		#3
		MVPD	table, *AR1+
;		code, which are modified
;		LD		*(x), 16, A
;		ADDS	*(x+1) , A
;		ADD		*(y), 16, A
;		ADDS	*(y+1), A
;		STH		A,*(z)
;		STL		A,*(z+1)
;		code, which are modified
		DLD		*(x),	 A		;长字装入
		DADD	*(y),	 A		;长字加法
		DST		A,	 *(z)		;长字装入
end:	B		end
		.end