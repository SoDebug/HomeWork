		.mmregs
		.global _c_int00	
			
STACK	.usect	"STACK", 10H
		.bss	a, 10
		.bss	x, 10
		.bss	z, 2	;�����ŵ�Ԫ
		.data
table:	.word	10,11,12,13,14,15,16,17,18,19
		.word	10,11,12,13,14,15,16,17,18,19
		.def	_c_int00
		
		.text
_c_int00:
		STM     #STACK+10,	SP
		B       START

START:	
		STM		#a, AR1		;װ������
		RPT		#19
		MVPD	table, *AR1+
		CALL	SUM			;���ó˷��ۼ��ӳ���
end:	B		end

SUM:	STM		#a, AR3
		STM		#x, AR4
;		code, which are modified
		LD		#0, A	;�ۼ���A��
		STM		#10, AR2	;����ѭ��Ϊ10	
loop:	LD		*AR3+, T
		MAC		*AR4+, A
		BANZ	loop, *AR2-
;		code, which are modified
;		RPTZ	A,  #9
;		MAC		*AR3+,  *AR4+,  A   ;˫������ָ��
		STH		A, *(z)
		STL		A, *(z+1)
		RET		
		.end
		