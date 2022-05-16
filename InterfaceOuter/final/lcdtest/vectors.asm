       .title "vectors.asm"
       .ref    _c_int00
       .sect  ".vectors"

RST: 	bd _c_int00
		nop
		nop
		.space 4*19*16
		.space 4*9*16	

