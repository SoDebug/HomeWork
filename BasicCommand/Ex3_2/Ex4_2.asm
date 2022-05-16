		.mmregs
		.global _c_int00	
			
STACK	.usect	"STACK", 10H
		.bss	a, 10
		.bss	x, 10
		.bss	z, 2	;结果存放单元
		.data
table:	.word	10,11,12,13,14,15,16,17,18,19
		.word	10,11,12,13,14,15,16,17,18,19
		.def	_c_int00
		
		.text
_c_int00:
		STM     #STACK+10,	SP
		B       START

START:	
		STM		#a, AR1		;装入数据
		RPT		#19
		MVPD	table, *AR1+
		CALL	SUM			;调用乘法累加子程序
end:	B		end

SUM:	STM		#a, AR3
		STM		#x, AR4
;		code, which are modified
		LD		#0, A	;累加器A清
		STM		#10, AR2	;设置循环为10	
loop:	LD		*AR3+, T
		MAC		*AR4+, A
		BANZ	loop, *AR2-
;		code, which are modified
;		RPTZ	A,  #9
;		MAC		*AR3+,  *AR4+,  A   ;双操作数指令
		STH		A, *(z)
		STL		A, *(z+1)
		RET		
		.end
		