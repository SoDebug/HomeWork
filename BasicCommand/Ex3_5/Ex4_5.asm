		.mmregs
		.global	_c_int00
		
STACK	.usect	"STACK", 10H
		.bss	x, 2		;32λ�ļ���
		.bss	y, 2		;32λ�ļ���
		.bss	z, 2		;32λ�ĺ���
		.def	start
		.data
table:	.long	16782345H, 10200347H  ;����������ֵ

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
		STM		#x,  AR1	;װ������
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
		DLD		*(x),	 A		;����װ��
		DADD	*(y),	 A		;���ּӷ�
		DST		A,	 *(z)		;����װ��
end:	B		end
		.end