 		.mmregs
		.global  _c_int00
		
STACK	.usect	"STACK", 10H
		.bss	x, 5
		.bss	y, 1
		.def 	start
		
		.data
table:	.word	10, 20, 3, 4, 25   ; x1 -- x5

		.text				
_c_int00:
		STM     #STACK+10,	SP
		B 		start
		
start:	STM		#x, AR1
		RPT		#4
		MVPD	table, *AR1+	;װ������
		LD 		#0, A
		CALL 	SUM				;�����ۼ��ӳ���
end:	B 		$
SUM:	STM		#x, AR3
;		code,which are modified
		RPT		#4
		ADD		*AR3+,A
;		code,which are modified
;		STM		#4, AR2			;װ��ѭ������
;loop:	ADD 	*AR3+, A
;		BANZ	loop, *AR2-		;ѭ��ִ��ָ��
		STL		A, *(y)
		RETD
		NOP
		NOP
		.end
		
 