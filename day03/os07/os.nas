; hello-os
; TAB=4

		ORG		0xc200		; 指定程序装载的内存地址
		
		MOV		AL,0x13		; VGA显卡，320*200*8位彩色
		MOV		AH,0x00
		INT		0x10
		
fin:
		HLT
		JMP		fin