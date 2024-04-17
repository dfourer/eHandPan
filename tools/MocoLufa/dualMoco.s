	.file	"dualMoco.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.RingBuffer_Insert,"ax",@progbits
	.type	RingBuffer_Insert, @function
RingBuffer_Insert:
.LFB73:
	.file 1 "Lib/LightweightRingBuff.h"
	.loc 1 160 0
	.cfi_startproc
.LVL0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 161 0
	movw r30,r24
	subi r30,-128
	sbci r31,-1
	ld r26,Z
	ldd r27,Z+1
	st X,r22
	.loc 1 163 0
	ld r26,Z
	ldd r27,Z+1
	movw r18,r26
	subi r18,-1
	sbci r19,-1
	std Z+1,r19
	st Z,r18
	cp r18,r30
	cpc r19,r31
	brne .L2
	.loc 1 164 0
	adiw r26,1+1
	st X,r25
	st -X,r24
	sbiw r26,1
.L2:
.LBB38:
	.loc 1 166 0
	in r18,__SREG__
.LVL1:
.LBB39:
.LBB40:
	.file 2 "/usr/lib/avr/include/util/atomic.h"
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL2:
/* #NOAPP */
.LBE40:
.LBE39:
	.loc 1 168 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r24,Z
.LVL3:
	subi r24,lo8(-(1))
	st Z,r24
.LVL4:
.LBB41:
.LBB42:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
	ret
.LBE42:
.LBE41:
.LBE38:
	.cfi_endproc
.LFE73:
	.size	RingBuffer_Insert, .-RingBuffer_Insert
	.section	.text.RingBuffer_Remove,"ax",@progbits
	.type	RingBuffer_Remove, @function
RingBuffer_Remove:
.LFB74:
	.loc 1 183 0
	.cfi_startproc
.LVL5:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 184 0
	movw r26,r24
	subi r26,126
	sbci r27,-1
	ld r30,X+
	ld r31,X
	sbiw r26,1
	ld r20,Z+
.LVL6:
	.loc 1 186 0
	adiw r26,1
	st X,r31
	st -X,r30
	movw r18,r24
	subi r18,-128
	sbci r19,-1
	cp r30,r18
	cpc r31,r19
	brne .L5
	.loc 1 187 0
	st X+,r24
	st X,r25
.L5:
.LBB43:
	.loc 1 189 0
	in r18,__SREG__
.LVL7:
.LBB44:
.LBB45:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL8:
/* #NOAPP */
.LBE45:
.LBE44:
	.loc 1 191 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r25,Z
	subi r25,lo8(-(-1))
	st Z,r25
.LVL9:
.LBB46:
.LBB47:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LBE47:
.LBE46:
.LBE43:
	.loc 1 195 0
	mov r24,r20
.LVL10:
	ret
	.cfi_endproc
.LFE74:
	.size	RingBuffer_Remove, .-RingBuffer_Remove
	.section	.text.parseUSBMidiMessage,"ax",@progbits
.global	parseUSBMidiMessage
	.type	parseUSBMidiMessage, @function
parseUSBMidiMessage:
.LFB87:
	.file 3 "dualMoco.c"
	.loc 3 113 0
	.cfi_startproc
.LVL11:
	push r28
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	lds r18,uwptr
	.loc 3 113 0
	movw r30,r24
	add r22,r24
.LVL12:
.L14:
	.loc 3 114 0
	ld r19,Z
	mov r25,r19
	andi r25,lo8(15)
.LVL13:
	.loc 3 117 0
	cpi r25,lo8(2)
	brsh .L7
.L11:
	mov r24,r22
	sub r24,r30
	.loc 3 136 0
	cpi r24,lo8(5)
	brlo .L21
	.loc 3 137 0
	adiw r30,4
	rjmp .L14
.L7:
	.loc 3 117 0
	movw r28,r30
	adiw r28,1
	ldi r24,lo8(1)
	.loc 3 127 0
	andi r19,lo8(11)
	.loc 3 128 0
	ldi r20,lo8(-12)
	add r20,r25
.L13:
.LVL14:
	.loc 3 119 0
	ld r21,Y+
	mov r26,r18
	ldi r27,0
	subi r26,lo8(-(tx_buf))
	sbci r27,hi8(-(tx_buf))
	st X,r21
	subi r18,lo8(-(1))
	.loc 3 120 0
	andi r18,lo8(31)
	.loc 3 121 0
	cpi r24,lo8(1)
	brne .L10
.LVL15:
	.loc 3 122 0
	cpi r25,lo8(5)
	breq .L11
	.loc 3 122 0 is_stmt 0 discriminator 1
	cpi r25,lo8(15)
	brne .L12
	rjmp .L11
.LVL16:
.L10:
	.loc 3 126 0 is_stmt 1
	cpi r24,lo8(2)
	brne .L12
	.loc 3 127 0
	cpi r19,lo8(2)
	breq .L11
	.loc 3 128 0
	cpi r20,lo8(2)
	brlo .L11
.LVL17:
.L12:
	.loc 3 118 0
	subi r24,lo8(-(1))
.LVL18:
	cpi r24,lo8(4)
	brne .L13
	rjmp .L11
.LVL19:
.L21:
	sts uwptr,r18
/* epilogue start */
	.loc 3 139 0
	pop r29
	pop r28
	ret
	.cfi_endproc
.LFE87:
	.size	parseUSBMidiMessage, .-parseUSBMidiMessage
	.section	.text.parseSerialMidiMessage,"ax",@progbits
.global	parseSerialMidiMessage
	.type	parseSerialMidiMessage, @function
parseSerialMidiMessage:
.LFB88:
	.loc 3 141 0
	.cfi_startproc
.LVL20:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 164 0
	lds r25,SysEx.3161
	tst r25
	breq .L23
	lds r30,sysExCnt.3162
	.loc 3 166 0
	ldi r25,lo8(1)
	add r25,r30
	sts sysExCnt.3162,r25
	.loc 3 165 0
	cpi r24,lo8(-9)
	brne .L24
	.loc 3 166 0
	mov r26,r30
	ldi r27,0
	subi r26,lo8(-(utx_buf))
	sbci r27,hi8(-(utx_buf))
	st X,r24
	.loc 3 167 0
	subi r30,lo8(-(4))
	sts utx_buf,r30
	.loc 3 168 0
	sts SysEx.3161,__zero_reg__
	.loc 3 169 0
	sts PC.3160,__zero_reg__
	rjmp .L33
.L24:
	.loc 3 172 0
	ldi r31,0
	subi r30,lo8(-(utx_buf))
	sbci r31,hi8(-(utx_buf))
	st Z,r24
	.loc 3 173 0
	cpi r25,lo8(4)
	brne .L32
	.loc 3 174 0
	sts utx_buf,r25
	.loc 3 175 0
	ldi r24,lo8(1)
.LVL21:
	sts sysExCnt.3162,r24
	.loc 3 176 0
	ret
.LVL22:
.L23:
	.loc 3 181 0
	cpi r24,lo8(-8)
	brlo .L27
	.loc 3 182 0
	ldi r25,lo8(15)
	sts utx_buf,r25
	.loc 3 183 0
	sts utx_buf+1,r24
	.loc 3 184 0
	sts utx_buf+2,__zero_reg__
	.loc 3 185 0
	sts utx_buf+3,__zero_reg__
	rjmp .L33
.L27:
	.loc 3 189 0
	sbrs r24,7
	rjmp .L28
	.loc 3 190 0
	cpi r24,lo8(-16)
	brne .L29
	.loc 3 191 0
	ldi r25,lo8(1)
	sts SysEx.3161,r25
	.loc 3 192 0
	sts utx_buf+1,r24
	.loc 3 193 0
	ldi r24,lo8(2)
.LVL23:
	sts sysExCnt.3162,r24
	rjmp .L32
.LVL24:
.L29:
	.loc 3 196 0
	sts PC.3160,__zero_reg__
.L28:
	.loc 3 199 0
	lds r25,PC.3160
	cpse r25,__zero_reg__
	rjmp .L30
	.loc 3 200 0
	mov r18,r24
	swap r18
	andi r18,lo8(15)
	mov r25,r18
	andi r25,lo8(7)
	lsl r25
	subi r25,lo8(-(2))
	sts PC.3160,r25
	.loc 3 203 0
	sts rx_buf,r18
	.loc 3 204 0
	sts rx_buf+1,r24
	.loc 3 205 0
	sts rx_buf+3,__zero_reg__
.LVL25:
.L32:
	.loc 3 215 0
	ldi r24,0
	ret
.LVL26:
.L30:
.LBB48:
	.loc 3 207 0
	mov r26,r25
	ldi r27,0
	subi r26,lo8(-(stateTransTable.3163))
	sbci r27,hi8(-(stateTransTable.3163))
	ld r18,X
.LVL27:
	.loc 3 208 0
	mov r30,r25
	andi r30,1
	ldi r31,0
	subi r30,lo8(-(rx_buf))
	sbci r31,hi8(-(rx_buf))
	std Z+2,r24
	.loc 3 209 0
	mov r24,r18
.LVL28:
	andi r24,lo8(15)
	sts PC.3160,r24
	.loc 3 210 0
	sbrs r18,7
	rjmp .L32
	.loc 3 211 0
	lds r24,rx_buf
	lds r25,rx_buf+1
	lds r26,rx_buf+2
	lds r27,rx_buf+3
	sts utx_buf,r24
	sts utx_buf+1,r25
	sts utx_buf+2,r26
	sts utx_buf+3,r27
.LVL29:
.L33:
	.loc 3 212 0
	ldi r24,lo8(1)
.LBE48:
	.loc 3 216 0
	ret
	.cfi_endproc
.LFE88:
	.size	parseSerialMidiMessage, .-parseSerialMidiMessage
	.section	.text.processMIDI,"ax",@progbits
.global	processMIDI
	.type	processMIDI, @function
processMIDI:
.LFB90:
	.loc 3 232 0
	.cfi_startproc
	push r28
.LCFI2:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI3:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
	rcall .
	rcall .
.LCFI4:
	.cfi_def_cfa_offset 8
	in r28,__SP_L__
	in r29,__SP_H__
.LCFI5:
	.cfi_def_cfa_register 28
/* prologue: function */
/* frame size = 4 */
/* stack size = 6 */
.L__stack_usage = 6
	.loc 3 236 0
/* #APP */
 ;  236 "dualMoco.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.LBB58:
	.loc 3 243 0
	ldi r17,lo8(3)
	.loc 3 285 0
	ldi r24,lo8(40)
	mov r15,r24
	.loc 3 286 0
	ldi r16,lo8(2)
.L49:
	.loc 3 240 0
	lds r24,200
	sbrs r24,7
	rjmp .L35
	.loc 3 241 0
	lds r14,utxrdy
	lds r24,206
	call parseSerialMidiMessage
.LVL30:
	or r24,r14
	sts utxrdy,r24
.LVL31:
.LBB59:
.LBB60:
	.file 4 "./Board/LEDs.h"
	.loc 4 75 0
	cbi 0xb,5
.LBE60:
.LBE59:
	.loc 3 243 0
	sts PulseMSRemaining,r17
.LVL32:
.L35:
	.loc 3 247 0
	lds r24,utxrdy
	tst r24
	breq .L37
	.loc 3 248 0
	ldi r22,lo8(utx_buf)
	ldi r23,hi8(utx_buf)
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	call MIDI_Device_SendEventPacket
.LVL33:
	.loc 3 249 0
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	call MIDI_Device_Flush
.LVL34:
	.loc 3 250 0
	sts utxrdy,__zero_reg__
.L37:
	.loc 3 255 0 discriminator 1
	movw r22,r28
	subi r22,-1
	sbci r23,-1
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	call MIDI_Device_ReceiveEventPacket
.LVL35:
	tst r24
	breq .L59
	.loc 3 257 0
	ldi r22,lo8(4)
	movw r24,r28
	adiw r24,1
	call parseUSBMidiMessage
.LVL36:
.LBB61:
.LBB62:
	.loc 4 75 0
	cbi 0xb,4
.LBE62:
.LBE61:
	.loc 3 259 0
	sts PulseMSRemaining+1,r17
	rjmp .L37
.LVL37:
.L59:
	.loc 3 263 0
	lds r24,200
	sbrs r24,5
	rjmp .L39
	.loc 3 263 0 is_stmt 0 discriminator 1
	lds r30,irptr
	lds r24,uwptr
	cp r24,r30
	breq .L39
	.loc 3 264 0 is_stmt 1
	ldi r24,lo8(1)
	add r24,r30
	sts irptr,r24
	ldi r31,0
	subi r30,lo8(-(tx_buf))
	sbci r31,hi8(-(tx_buf))
	ld r24,Z
	sts 206,r24
	.loc 3 265 0
	lds r24,irptr
	andi r24,lo8(31)
	sts irptr,r24
.L39:
	.loc 3 268 0
	sbis 0x15,0
	rjmp .L41
	.loc 3 269 0
	sbi 0x15,0
	.loc 3 271 0
	lds r24,PulseMSRemaining
	tst r24
	breq .L43
	.loc 3 271 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining
	subi r24,lo8(-(-1))
	sts PulseMSRemaining,r24
	cpse r24,__zero_reg__
	rjmp .L43
.LVL38:
.LBB63:
.LBB64:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,5
.LVL39:
.L43:
.LBE64:
.LBE63:
	.loc 3 275 0
	lds r24,PulseMSRemaining+1
	tst r24
	breq .L41
	.loc 3 275 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining+1
	subi r24,lo8(-(-1))
	sts PulseMSRemaining+1,r24
	cpse r24,__zero_reg__
	rjmp .L41
.LVL40:
.LBB65:
.LBB66:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,4
.LVL41:
.L41:
.LBE66:
.LBE65:
	.loc 3 280 0
	call USB_USBTask
.LVL42:
	.loc 3 282 0
	lds r24,highSpeed
	cpi r24,lo8(1)
	breq .+2
	rjmp .L49
	.loc 3 283 0
	lds r24,cnt.3170
	subi r24,lo8(-(-1))
	sts cnt.3170,r24
	.loc 3 284 0
	cpse r24,__zero_reg__
	rjmp .L49
	.loc 3 285 0
	sts cnt.3170,r15
	.loc 3 286 0
	in r24,0x5
	eor r24,r16
	out 0x5,r24
.LBE58:
	.loc 3 289 0
	rjmp .L49
	.cfi_endproc
.LFE90:
	.size	processMIDI, .-processMIDI
	.section	.text.processSerial,"ax",@progbits
.global	processSerial
	.type	processSerial, @function
processSerial:
.LFB91:
	.loc 3 293 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.LVL43:
.LBB118:
.LBB119:
	.loc 1 87 0
	in r18,__SREG__
.LVL44:
.LBB120:
.LBB121:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL45:
/* #NOAPP */
.LBE121:
.LBE120:
	.loc 1 89 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
	sts USBtoUSART_Buffer+128+1,r25
	sts USBtoUSART_Buffer+128,r24
	.loc 1 90 0
	sts USBtoUSART_Buffer+130+1,r25
	sts USBtoUSART_Buffer+130,r24
.LVL46:
.LBB122:
.LBB123:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL47:
.LBE123:
.LBE122:
.LBE119:
.LBE118:
.LBB124:
.LBB125:
	.loc 1 87 0
	in r18,__SREG__
.LVL48:
.LBB126:
.LBB127:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL49:
/* #NOAPP */
.LBE127:
.LBE126:
	.loc 1 89 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	sts USARTtoUSB_Buffer+128+1,r25
	sts USARTtoUSB_Buffer+128,r24
	.loc 1 90 0
	sts USARTtoUSB_Buffer+130+1,r25
	sts USARTtoUSB_Buffer+130,r24
.LVL50:
.LBB128:
.LBB129:
	.loc 2 70 0
	out __SREG__,r18
.LVL51:
	.loc 2 71 0
.LBE129:
.LBE128:
.LBE125:
.LBE124:
	.loc 3 298 0
/* #APP */
 ;  298 "dualMoco.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.LBB130:
	.loc 3 320 0
	ldi r29,lo8(3)
.LVL52:
.L76:
.LBB131:
.LBB132:
.LBB133:
.LBB134:
	.loc 1 111 0
	in r25,__SREG__
.LVL53:
.LBB135:
.LBB136:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL54:
/* #NOAPP */
.LBE136:
.LBE135:
	.loc 1 113 0
	lds r24,USBtoUSART_Buffer+132
.LVL55:
.LBB137:
.LBB138:
	.loc 2 70 0
	out __SREG__,r25
	.loc 2 71 0
.LBE138:
.LBE137:
.LBE134:
.LBE133:
.LBE132:
.LBE131:
	.loc 3 303 0
	cpi r24,lo8(-128)
	breq .L62
.LBB139:
	.loc 3 305 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
.LVL56:
	call CDC_Device_ReceiveByte
.LVL57:
	.loc 3 308 0
	sbrc r25,7
	rjmp .L62
	.loc 3 309 0
	mov r22,r24
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
.LVL58:
	call RingBuffer_Insert
.LVL59:
.L62:
.LBE139:
.LBB140:
.LBB141:
.LBB142:
	.loc 1 111 0
	in r24,__SREG__
.LVL60:
.LBB143:
.LBB144:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL61:
/* #NOAPP */
.LBE144:
.LBE143:
	.loc 1 113 0
	lds r28,USARTtoUSB_Buffer+132
.LVL62:
.LBB145:
.LBB146:
	.loc 2 70 0
	out __SREG__,r24
	.loc 2 71 0
.LBE146:
.LBE145:
.LBE142:
.LBE141:
.LBE140:
	.loc 3 314 0
	sbic 0x15,0
	rjmp .L64
	.loc 3 314 0 is_stmt 0 discriminator 1
	cpi r28,lo8(97)
	brlo .L65
.L64:
	.loc 3 316 0 is_stmt 1
	sbi 0x15,0
	.loc 3 318 0
	lds r24,USARTtoUSB_Buffer+132
.LVL63:
	tst r24
	breq .L67
.LVL64:
.LBB147:
.LBB148:
	.loc 4 75 0
	cbi 0xb,5
.LBE148:
.LBE147:
	.loc 3 320 0
	sts PulseMSRemaining,r29
.LVL65:
.L67:
	.loc 3 324 0 discriminator 1
	tst r28
	breq .L86
	.loc 3 325 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Remove
.LVL66:
	mov r22,r24
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_SendByte
.LVL67:
	subi r28,lo8(-(-1))
.LVL68:
	rjmp .L67
.LVL69:
.L86:
	.loc 3 328 0
	lds r24,PulseMSRemaining
	tst r24
	breq .L70
	.loc 3 328 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining
	subi r24,lo8(-(-1))
	sts PulseMSRemaining,r24
	cpse r24,__zero_reg__
	rjmp .L70
.LVL70:
.LBB149:
.LBB150:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,5
.LVL71:
.L70:
.LBE150:
.LBE149:
	.loc 3 332 0
	lds r24,PulseMSRemaining+1
	tst r24
	breq .L65
	.loc 3 332 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining+1
	subi r24,lo8(-(-1))
	sts PulseMSRemaining+1,r24
	cpse r24,__zero_reg__
	rjmp .L65
.LVL72:
.LBB151:
.LBB152:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,4
.LVL73:
.L65:
.LBE152:
.LBE151:
.LBB153:
.LBB154:
.LBB155:
.LBB156:
	.loc 1 111 0
	in r25,__SREG__
.LVL74:
.LBB157:
.LBB158:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL75:
/* #NOAPP */
.LBE158:
.LBE157:
	.loc 1 113 0
	lds r24,USBtoUSART_Buffer+132
.LVL76:
.LBB159:
.LBB160:
	.loc 2 70 0
	out __SREG__,r25
	.loc 2 71 0
.LBE160:
.LBE159:
.LBE156:
.LBE155:
.LBE154:
.LBE153:
	.loc 3 337 0
	tst r24
	breq .L73
	.loc 3 338 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
.LVL77:
	call RingBuffer_Remove
.LVL78:
.L75:
.LBB161:
.LBB162:
	.file 5 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/Peripheral/Serial.h"
	.loc 5 142 0
	lds r25,200
	sbrs r25,5
	rjmp .L75
	.loc 5 143 0
	sts 206,r24
.LVL79:
.LBE162:
.LBE161:
.LBB163:
.LBB164:
	.loc 4 75 0
	cbi 0xb,4
.LBE164:
.LBE163:
	.loc 3 341 0
	sts PulseMSRemaining+1,r29
.LVL80:
.L73:
	.loc 3 344 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_USBTask
.LVL81:
	.loc 3 345 0
	call USB_USBTask
.LVL82:
.LBE130:
	.loc 3 346 0
	rjmp .L76
	.cfi_endproc
.LFE91:
	.size	processSerial, .-processSerial
	.section	.text.SetupHardware,"ax",@progbits
.global	SetupHardware
	.type	SetupHardware, @function
SetupHardware:
.LFB92:
	.loc 3 351 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 353 0
	in r24,0x34
	andi r24,lo8(-9)
	out 0x34,r24
	.loc 3 354 0
	ldi r24,lo8(24)
/* #APP */
 ;  354 "dualMoco.c" 1
	in __tmp_reg__, __SREG__
	cli
	sts 96, r24
	sts 96, __zero_reg__
	out __SREG__,__tmp_reg__
	
 ;  0 "" 2
	.loc 3 357 0
/* #NOAPP */
	ldi r24,lo8(2)
	out 0x4,r24
	.loc 3 358 0
	ldi r24,lo8(12)
	out 0x5,r24
	.loc 3 360 0
	sbic 0x3,2
	rjmp .L88
	.loc 3 361 0
	sts mocoMode,__zero_reg__
.LVL83:
.LBB169:
.LBB170:
	.loc 5 102 0
	ldi r24,lo8(103)
	ldi r25,0
	sts 204+1,r25
	sts 204,r24
	.loc 5 104 0
	ldi r24,lo8(6)
	sts 202,r24
	.loc 5 105 0
	sts 200,__zero_reg__
	.loc 5 106 0
	ldi r24,lo8(24)
	sts 201,r24
	.loc 5 108 0
	sbi 0xa,3
	.loc 5 109 0
	sbi 0xb,2
	rjmp .L89
.LVL84:
.L88:
.LBE170:
.LBE169:
	.loc 3 364 0
	ldi r24,lo8(1)
	sts mocoMode,r24
	.loc 3 365 0
	sbic 0x3,3
	rjmp .L90
	.loc 3 366 0
	sts highSpeed,r24
	.loc 3 368 0
	sts 204,__zero_reg__
	rjmp .L91
.L90:
	.loc 3 370 0
	ldi r24,lo8(31)
	sts 204,r24
.L91:
	.loc 3 372 0
	ldi r24,lo8(24)
	sts 201,r24
	.loc 3 373 0
	ldi r24,lo8(14)
	out 0x5,r24
.L89:
	.loc 3 377 0
	ldi r24,lo8(4)
	out 0x25,r24
	.loc 3 380 0
	call USB_Init
.LVL85:
.LBB171:
.LBB172:
	.loc 4 69 0
	in r24,0xa
	ori r24,lo8(48)
	out 0xa,r24
	.loc 4 70 0
	in r24,0xb
	ori r24,lo8(48)
	out 0xb,r24
.LBE172:
.LBE171:
	.loc 3 383 0
	lds r24,mocoMode
	cpse r24,__zero_reg__
	rjmp .L87
	.loc 3 385 0
	sbi 0xb,7
	.loc 3 386 0
	sbi 0xa,7
.L87:
	ret
	.cfi_endproc
.LFE92:
	.size	SetupHardware, .-SetupHardware
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
.LFB89:
	.loc 3 221 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 222 0
	call SetupHardware
.LVL86:
	.loc 3 224 0
	lds r24,mocoMode
	cpi r24,lo8(1)
	brne .L94
	.loc 3 225 0
	call processMIDI
.LVL87:
.L94:
	.loc 3 227 0
	call processSerial
.LVL88:
	.cfi_endproc
.LFE89:
	.size	main, .-main
	.section	.text.EVENT_USB_Device_Connect,"ax",@progbits
.global	EVENT_USB_Device_Connect
	.type	EVENT_USB_Device_Connect, @function
EVENT_USB_Device_Connect:
.LFB93:
	.loc 3 391 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE93:
	.size	EVENT_USB_Device_Connect, .-EVENT_USB_Device_Connect
	.section	.text.EVENT_USB_Device_Disconnect,"ax",@progbits
.global	EVENT_USB_Device_Disconnect
	.type	EVENT_USB_Device_Disconnect, @function
EVENT_USB_Device_Disconnect:
.LFB94:
	.loc 3 395 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE94:
	.size	EVENT_USB_Device_Disconnect, .-EVENT_USB_Device_Disconnect
	.section	.text.EVENT_USB_Device_ConfigurationChanged,"ax",@progbits
.global	EVENT_USB_Device_ConfigurationChanged
	.type	EVENT_USB_Device_ConfigurationChanged, @function
EVENT_USB_Device_ConfigurationChanged:
.LFB95:
	.loc 3 399 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 400 0
	lds r24,mocoMode
	cpi r24,lo8(1)
	brne .L98
.LVL89:
.LBB173:
	.loc 3 402 0
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	jmp MIDI_Device_ConfigureEndpoints
.LVL90:
.L98:
.LBE173:
	.loc 3 404 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ConfigureEndpoints
.LVL91:
	.cfi_endproc
.LFE95:
	.size	EVENT_USB_Device_ConfigurationChanged, .-EVENT_USB_Device_ConfigurationChanged
	.section	.text.EVENT_USB_Device_ControlRequest,"ax",@progbits
.global	EVENT_USB_Device_ControlRequest
	.type	EVENT_USB_Device_ControlRequest, @function
EVENT_USB_Device_ControlRequest:
.LFB96:
	.loc 3 409 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE96:
	.size	EVENT_USB_Device_ControlRequest, .-EVENT_USB_Device_ControlRequest
	.section	.text.EVENT_USB_Device_UnhandledControlRequest,"ax",@progbits
.global	EVENT_USB_Device_UnhandledControlRequest
	.type	EVENT_USB_Device_UnhandledControlRequest, @function
EVENT_USB_Device_UnhandledControlRequest:
.LFB97:
	.loc 3 416 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 417 0
	lds r24,mocoMode
	cpse r24,__zero_reg__
	rjmp .L100
	.loc 3 418 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ProcessControlRequest
.LVL92:
.L100:
	ret
	.cfi_endproc
.LFE97:
	.size	EVENT_USB_Device_UnhandledControlRequest, .-EVENT_USB_Device_UnhandledControlRequest
	.section	.text.EVENT_CDC_Device_LineEncodingChanged,"ax",@progbits
.global	EVENT_CDC_Device_LineEncodingChanged
	.type	EVENT_CDC_Device_LineEncodingChanged, @function
EVENT_CDC_Device_LineEncodingChanged:
.LFB98:
	.loc 3 428 0
	.cfi_startproc
.LVL93:
	push r17
.LCFI6:
	.cfi_def_cfa_offset 3
	.cfi_offset 17, -2
	push r28
.LCFI7:
	.cfi_def_cfa_offset 4
	.cfi_offset 28, -3
	push r29
.LCFI8:
	.cfi_def_cfa_offset 5
	.cfi_offset 29, -4
/* prologue: function */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
	movw r28,r24
.LVL94:
	.loc 3 431 0
	ldd r24,Y+20
.LVL95:
	cpi r24,lo8(1)
	breq .L113
	cpi r24,lo8(2)
	breq .L105
	.loc 3 429 0
	ldi r17,0
	rjmp .L104
.L105:
.LVL96:
	.loc 3 437 0
	ldi r17,lo8(32)
	.loc 3 438 0
	rjmp .L104
.LVL97:
.L113:
	.loc 3 434 0
	ldi r17,lo8(48)
.LVL98:
.L104:
	.loc 3 441 0
	ldd r24,Y+19
	cpi r24,lo8(2)
	brne .L106
	.loc 3 442 0
	ori r17,lo8(8)
.LVL99:
.L106:
	.loc 3 444 0
	ldd r24,Y+21
	cpi r24,lo8(7)
	breq .L108
	cpi r24,lo8(8)
	breq .L109
	cpi r24,lo8(6)
	brne .L107
	.loc 3 447 0
	ori r17,lo8(2)
.LVL100:
	.loc 3 448 0
	rjmp .L107
.L108:
	.loc 3 450 0
	ori r17,lo8(4)
.LVL101:
	.loc 3 451 0
	rjmp .L107
.L109:
	.loc 3 453 0
	ori r17,lo8(6)
.LVL102:
.L107:
	.loc 3 458 0
	sts 201,__zero_reg__
	.loc 3 459 0
	sts 200,__zero_reg__
	.loc 3 460 0
	sts 202,__zero_reg__
	.loc 3 463 0
	ldd r18,Y+15
	ldd r19,Y+16
	ldd r20,Y+17
	ldd r21,Y+18
	cp r18,__zero_reg__
	ldi r24,-31
	cpc r19,r24
	cpc r20,__zero_reg__
	cpc r21,__zero_reg__
	breq .L114
	.loc 3 465 0 discriminator 1
	movw r24,r20
	movw r22,r18
	lsr r25
	ror r24
	ror r23
	ror r22
	subi r22,-128
	sbci r23,123
	sbci r24,-31
	sbci r25,-1
	call __udivmodsi4
	.loc 3 463 0 discriminator 1
	subi r18,1
	sbc r19,__zero_reg__
	rjmp .L111
.L114:
	.loc 3 463 0 is_stmt 0
	ldi r18,lo8(16)
	ldi r19,0
.L111:
	.loc 3 463 0 discriminator 2
	sts 204+1,r19
	sts 204,r18
	.loc 3 467 0 is_stmt 1 discriminator 2
	sts 202,r17
	.loc 3 468 0 discriminator 2
	ldd r24,Y+15
	ldd r25,Y+16
	ldd r26,Y+17
	ldd r27,Y+18
	cp r24,__zero_reg__
	sbci r25,-31
	cpc r26,__zero_reg__
	cpc r27,__zero_reg__
	brne .L115
	.loc 3 468 0 is_stmt 0
	ldi r24,0
	rjmp .L112
.L115:
	ldi r24,lo8(2)
.L112:
	.loc 3 468 0 discriminator 3
	sts 200,r24
	.loc 3 469 0 is_stmt 1 discriminator 3
	ldi r24,lo8(-104)
	sts 201,r24
/* epilogue start */
	.loc 3 470 0 discriminator 3
	pop r29
	pop r28
.LVL103:
	pop r17
.LVL104:
	ret
	.cfi_endproc
.LFE98:
	.size	EVENT_CDC_Device_LineEncodingChanged, .-EVENT_CDC_Device_LineEncodingChanged
	.section	.text.__vector_23,"ax",@progbits
.global	__vector_23
	.type	__vector_23, @function
__vector_23:
.LFB99:
	.loc 3 475 0
	.cfi_startproc
	push r1
.LCFI9:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI10:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI11:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r19
.LCFI12:
	.cfi_def_cfa_offset 6
	.cfi_offset 19, -5
	push r20
.LCFI13:
	.cfi_def_cfa_offset 7
	.cfi_offset 20, -6
	push r21
.LCFI14:
	.cfi_def_cfa_offset 8
	.cfi_offset 21, -7
	push r22
.LCFI15:
	.cfi_def_cfa_offset 9
	.cfi_offset 22, -8
	push r23
.LCFI16:
	.cfi_def_cfa_offset 10
	.cfi_offset 23, -9
	push r24
.LCFI17:
	.cfi_def_cfa_offset 11
	.cfi_offset 24, -10
	push r25
.LCFI18:
	.cfi_def_cfa_offset 12
	.cfi_offset 25, -11
	push r26
.LCFI19:
	.cfi_def_cfa_offset 13
	.cfi_offset 26, -12
	push r27
.LCFI20:
	.cfi_def_cfa_offset 14
	.cfi_offset 27, -13
	push r30
.LCFI21:
	.cfi_def_cfa_offset 15
	.cfi_offset 30, -14
	push r31
.LCFI22:
	.cfi_def_cfa_offset 16
	.cfi_offset 31, -15
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 15 */
.L__stack_usage = 15
	.loc 3 476 0
	lds r24,mocoMode
	cpse r24,__zero_reg__
	rjmp .L116
.LBB174:
	.loc 3 477 0
	lds r22,206
.LVL105:
	.loc 3 479 0
	in r24,0x1e
	cpi r24,lo8(4)
	brne .L116
	.loc 3 480 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Insert
.LVL106:
.L116:
/* epilogue start */
.LBE174:
	.loc 3 482 0
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE99:
	.size	__vector_23, .-__vector_23
	.section	.text.EVENT_CDC_Device_ControLineStateChanged,"ax",@progbits
.global	EVENT_CDC_Device_ControLineStateChanged
	.type	EVENT_CDC_Device_ControLineStateChanged, @function
EVENT_CDC_Device_ControLineStateChanged:
.LFB100:
	.loc 3 488 0
	.cfi_startproc
.LVL107:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 489 0
	movw r30,r24
	ldd r24,Z+13
.LVL108:
	.loc 3 491 0
	sbrs r24,0
	rjmp .L119
	.loc 3 492 0
	cbi 0xb,7
	ret
.L119:
	.loc 3 494 0
	sbi 0xb,7
	ret
	.cfi_endproc
.LFE100:
	.size	EVENT_CDC_Device_ControLineStateChanged, .-EVENT_CDC_Device_ControLineStateChanged
	.data
	.type	cnt.3170, @object
	.size	cnt.3170, 1
cnt.3170:
	.byte	40
	.section	.rodata
	.type	stateTransTable.3163, @object
	.size	stateTransTable.3163, 16
stateTransTable.3163:
	.byte	0
	.byte	0
	.byte	3
	.byte	-126
	.byte	5
	.byte	-124
	.byte	7
	.byte	-122
	.byte	9
	.byte	-120
	.byte	-118
	.byte	0
	.byte	-116
	.byte	0
	.byte	15
	.byte	-114
	.local	PC.3160
	.comm	PC.3160,1,1
	.local	sysExCnt.3162
	.comm	sysExCnt.3162,1,1
	.local	SysEx.3161
	.comm	SysEx.3161,1,1
.global	Keyboard_MIDI_Interface
	.data
	.type	Keyboard_MIDI_Interface, @object
	.size	Keyboard_MIDI_Interface, 9
Keyboard_MIDI_Interface:
	.byte	1
	.byte	2
	.word	64
	.byte	0
	.byte	1
	.word	64
	.byte	0
.global	VirtualSerial_CDC_Interface
	.type	VirtualSerial_CDC_Interface, @object
	.size	VirtualSerial_CDC_Interface, 22
VirtualSerial_CDC_Interface:
	.byte	0
	.byte	3
	.word	64
	.byte	0
	.byte	4
	.word	64
	.byte	0
	.byte	2
	.word	8
	.byte	0
	.zero	9
	.local	tx_buf
	.comm	tx_buf,32,1
	.local	irptr
	.comm	irptr,1,1
	.local	uwptr
	.comm	uwptr,1,1
	.local	utx_buf
	.comm	utx_buf,8,1
	.local	rx_buf
	.comm	rx_buf,8,1
	.local	utxrdy
	.comm	utxrdy,1,1
	.comm	PulseMSRemaining,3,1
	.comm	USARTtoUSB_Buffer,133,1
	.comm	USBtoUSART_Buffer,133,1
.global	highSpeed
	.section .bss
	.type	highSpeed, @object
	.size	highSpeed, 1
highSpeed:
	.zero	1
.global	mocoMode
	.data
	.type	mocoMode, @object
	.size	mocoMode, 1
mocoMode:
	.byte	1
	.text
.Letext0:
	.file 6 "/usr/lib/avr/include/stdint.h"
	.file 7 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/USB/HighLevel/../LowLevel/Device.h"
	.file 8 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/USB/Class/Device/../Common/CDC.h"
	.file 9 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/USB/Class/Device/CDC.h"
	.file 10 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/USB/Class/Device/../Common/MIDI.h"
	.file 11 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/USB/Class/Device/MIDI.h"
	.file 12 "dualMoco.h"
	.file 13 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/USB/HighLevel/USBTask.h"
	.file 14 "./rambo-32u2-usbserial/LUFA100807//LUFA/Drivers/USB/HighLevel/../LowLevel/USBController.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x1172
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF134
	.byte	0x1
	.long	.LASF135
	.long	.LASF136
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF2
	.byte	0x6
	.byte	0x7a
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.long	.LASF3
	.byte	0x6
	.byte	0x7b
	.long	0x4d
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF4
	.byte	0x6
	.byte	0x7c
	.long	0x5f
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF6
	.uleb128 0x3
	.long	.LASF7
	.byte	0x6
	.byte	0x7e
	.long	0x78
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF11
	.uleb128 0x5
	.long	.LASF18
	.byte	0x1
	.byte	0x7
	.byte	0x72
	.long	0xc5
	.uleb128 0x6
	.long	.LASF12
	.sleb128 0
	.uleb128 0x6
	.long	.LASF13
	.sleb128 1
	.uleb128 0x6
	.long	.LASF14
	.sleb128 2
	.uleb128 0x6
	.long	.LASF15
	.sleb128 3
	.uleb128 0x6
	.long	.LASF16
	.sleb128 4
	.uleb128 0x6
	.long	.LASF17
	.sleb128 5
	.byte	0
	.uleb128 0x5
	.long	.LASF19
	.byte	0x1
	.byte	0x8
	.byte	0x9b
	.long	0xe4
	.uleb128 0x6
	.long	.LASF20
	.sleb128 0
	.uleb128 0x6
	.long	.LASF21
	.sleb128 1
	.uleb128 0x6
	.long	.LASF22
	.sleb128 2
	.byte	0
	.uleb128 0x5
	.long	.LASF23
	.byte	0x1
	.byte	0x8
	.byte	0xa3
	.long	0x10f
	.uleb128 0x6
	.long	.LASF24
	.sleb128 0
	.uleb128 0x6
	.long	.LASF25
	.sleb128 1
	.uleb128 0x6
	.long	.LASF26
	.sleb128 2
	.uleb128 0x6
	.long	.LASF27
	.sleb128 3
	.uleb128 0x6
	.long	.LASF28
	.sleb128 4
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF29
	.uleb128 0x7
	.byte	0xd
	.byte	0x9
	.byte	0x64
	.long	0x1ab
	.uleb128 0x8
	.long	.LASF30
	.byte	0x9
	.byte	0x66
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF31
	.byte	0x9
	.byte	0x68
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF32
	.byte	0x9
	.byte	0x69
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF33
	.byte	0x9
	.byte	0x6a
	.long	0x1ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF34
	.byte	0x9
	.byte	0x6c
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF35
	.byte	0x9
	.byte	0x6d
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x8
	.long	.LASF36
	.byte	0x9
	.byte	0x6e
	.long	0x1ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.long	.LASF37
	.byte	0x9
	.byte	0x70
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.uleb128 0x8
	.long	.LASF38
	.byte	0x9
	.byte	0x71
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0xa
	.uleb128 0x8
	.long	.LASF39
	.byte	0x9
	.byte	0x72
	.long	0x1ab
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.long	.LASF40
	.uleb128 0x7
	.byte	0x2
	.byte	0x9
	.byte	0x78
	.long	0x1d7
	.uleb128 0x8
	.long	.LASF41
	.byte	0x9
	.byte	0x7a
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF42
	.byte	0x9
	.byte	0x7d
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.byte	0x9
	.byte	0x83
	.long	0x218
	.uleb128 0x8
	.long	.LASF43
	.byte	0x9
	.byte	0x85
	.long	0x6d
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF44
	.byte	0x9
	.byte	0x86
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF45
	.byte	0x9
	.byte	0x89
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF46
	.byte	0x9
	.byte	0x8c
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.byte	0
	.uleb128 0x7
	.byte	0x9
	.byte	0x9
	.byte	0x76
	.long	0x23d
	.uleb128 0x8
	.long	.LASF47
	.byte	0x9
	.byte	0x81
	.long	0x1b2
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF48
	.byte	0x9
	.byte	0x8d
	.long	0x1d7
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x7
	.byte	0x16
	.byte	0x9
	.byte	0x62
	.long	0x262
	.uleb128 0x8
	.long	.LASF49
	.byte	0x9
	.byte	0x73
	.long	0x262
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF50
	.byte	0x9
	.byte	0x90
	.long	0x218
	.byte	0x2
	.byte	0x23
	.uleb128 0xd
	.byte	0
	.uleb128 0x9
	.long	0x116
	.uleb128 0x3
	.long	.LASF51
	.byte	0x9
	.byte	0x93
	.long	0x23d
	.uleb128 0x7
	.byte	0x4
	.byte	0xa
	.byte	0xae
	.long	0x2c7
	.uleb128 0xa
	.long	.LASF52
	.byte	0xa
	.byte	0xb0
	.long	0x3b
	.byte	0x1
	.byte	0x4
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.long	.LASF53
	.byte	0xa
	.byte	0xb1
	.long	0x3b
	.byte	0x1
	.byte	0x4
	.byte	0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF54
	.byte	0xa
	.byte	0xb3
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF55
	.byte	0xa
	.byte	0xb4
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF56
	.byte	0xa
	.byte	0xb5
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x3
	.byte	0
	.uleb128 0x3
	.long	.LASF57
	.byte	0xa
	.byte	0xb6
	.long	0x272
	.uleb128 0x7
	.byte	0x9
	.byte	0xb
	.byte	0x52
	.long	0x33d
	.uleb128 0x8
	.long	.LASF58
	.byte	0xb
	.byte	0x54
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF31
	.byte	0xb
	.byte	0x56
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF32
	.byte	0xb
	.byte	0x57
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF33
	.byte	0xb
	.byte	0x58
	.long	0x1ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF34
	.byte	0xb
	.byte	0x5a
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF35
	.byte	0xb
	.byte	0x5b
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x8
	.long	.LASF36
	.byte	0xb
	.byte	0x5c
	.long	0x1ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0xb
	.byte	0
	.byte	0xb
	.byte	0x60
	.uleb128 0x7
	.byte	0x9
	.byte	0xb
	.byte	0x50
	.long	0x366
	.uleb128 0x8
	.long	.LASF49
	.byte	0xb
	.byte	0x5d
	.long	0x366
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF50
	.byte	0xb
	.byte	0x63
	.long	0x33d
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.byte	0
	.uleb128 0x9
	.long	0x2d2
	.uleb128 0x3
	.long	.LASF59
	.byte	0xb
	.byte	0x66
	.long	0x341
	.uleb128 0x7
	.byte	0x85
	.byte	0x1
	.byte	0x46
	.long	0x3b9
	.uleb128 0x8
	.long	.LASF60
	.byte	0x1
	.byte	0x48
	.long	0x3b9
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.string	"In"
	.byte	0x1
	.byte	0x49
	.long	0x3c9
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xc
	.string	"Out"
	.byte	0x1
	.byte	0x4a
	.long	0x3c9
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.uleb128 0x8
	.long	.LASF61
	.byte	0x1
	.byte	0x4b
	.long	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.byte	0
	.uleb128 0xd
	.long	0x30
	.long	0x3c9
	.uleb128 0xe
	.long	0x8d
	.byte	0x7f
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x30
	.uleb128 0x3
	.long	.LASF62
	.byte	0x1
	.byte	0x4c
	.long	0x376
	.uleb128 0x3
	.long	.LASF63
	.byte	0xc
	.byte	0x4e
	.long	0x30
	.uleb128 0x7
	.byte	0x3
	.byte	0x3
	.byte	0x3c
	.long	0x418
	.uleb128 0x8
	.long	.LASF64
	.byte	0x3
	.byte	0x3d
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF65
	.byte	0x3
	.byte	0x3e
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF66
	.byte	0x3
	.byte	0x3f
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x10
	.long	.LASF69
	.byte	0x2
	.byte	0x44
	.byte	0x1
	.byte	0x3
	.long	0x431
	.uleb128 0x11
	.string	"__s"
	.byte	0x2
	.byte	0x44
	.long	0x431
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x437
	.uleb128 0x9
	.long	0x30
	.uleb128 0x12
	.long	.LASF137
	.byte	0x2
	.byte	0x30
	.byte	0x1
	.long	0x30
	.byte	0x3
	.uleb128 0x13
	.long	.LASF75
	.byte	0x1
	.byte	0x6b
	.byte	0x1
	.long	0x30
	.byte	0x3
	.long	0x489
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x6b
	.long	0x489
	.uleb128 0x15
	.long	.LASF61
	.byte	0x1
	.byte	0x6d
	.long	0x30
	.uleb128 0x16
	.uleb128 0x15
	.long	.LASF67
	.byte	0x1
	.byte	0x6f
	.long	0x30
	.uleb128 0x15
	.long	.LASF68
	.byte	0x1
	.byte	0x6f
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x9
	.long	0x48e
	.uleb128 0xf
	.byte	0x2
	.long	0x3cf
	.uleb128 0x10
	.long	.LASF70
	.byte	0xb
	.byte	0xa1
	.byte	0x1
	.byte	0x3
	.long	0x4ad
	.uleb128 0x14
	.long	.LASF71
	.byte	0xb
	.byte	0xa1
	.long	0x4ad
	.byte	0
	.uleb128 0x9
	.long	0x4b2
	.uleb128 0xf
	.byte	0x2
	.long	0x36b
	.uleb128 0x10
	.long	.LASF72
	.byte	0x5
	.byte	0x8c
	.byte	0x1
	.byte	0x3
	.long	0x4d1
	.uleb128 0x14
	.long	.LASF73
	.byte	0x5
	.byte	0x8c
	.long	0x4d1
	.byte	0
	.uleb128 0x9
	.long	0x10f
	.uleb128 0x10
	.long	.LASF74
	.byte	0xb
	.byte	0xac
	.byte	0x1
	.byte	0x3
	.long	0x4ef
	.uleb128 0x14
	.long	.LASF71
	.byte	0xb
	.byte	0xac
	.long	0x4ad
	.byte	0
	.uleb128 0x13
	.long	.LASF76
	.byte	0x1
	.byte	0x7f
	.byte	0x1
	.long	0x1ab
	.byte	0x3
	.long	0x50c
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x7f
	.long	0x489
	.byte	0
	.uleb128 0x13
	.long	.LASF77
	.byte	0x1
	.byte	0x90
	.byte	0x1
	.long	0x1ab
	.byte	0x3
	.long	0x529
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x90
	.long	0x489
	.byte	0
	.uleb128 0x10
	.long	.LASF78
	.byte	0x5
	.byte	0x63
	.byte	0x1
	.byte	0x3
	.long	0x54d
	.uleb128 0x14
	.long	.LASF79
	.byte	0x5
	.byte	0x63
	.long	0x54d
	.uleb128 0x14
	.long	.LASF80
	.byte	0x5
	.byte	0x64
	.long	0x552
	.byte	0
	.uleb128 0x9
	.long	0x6d
	.uleb128 0x9
	.long	0x1ab
	.uleb128 0x17
	.long	.LASF138
	.byte	0x1
	.byte	0x9e
	.byte	0x1
	.long	.LFB73
	.long	.LFE73
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x5de
	.uleb128 0x18
	.long	.LASF60
	.byte	0x1
	.byte	0x9e
	.long	0x489
	.long	.LLST0
	.uleb128 0x19
	.long	.LASF81
	.byte	0x1
	.byte	0x9f
	.long	0x437
	.byte	0x1
	.byte	0x66
	.uleb128 0x1a
	.long	.LBB38
	.long	.LBE38
	.uleb128 0x1b
	.long	.LASF67
	.byte	0x1
	.byte	0xa6
	.long	0x30
	.byte	0x1
	.byte	0x62
	.uleb128 0x1c
	.long	.LASF68
	.byte	0x1
	.byte	0xa6
	.long	0x30
	.long	.LLST1
	.uleb128 0x1d
	.long	0x43c
	.long	.LBB39
	.long	.LBE39
	.byte	0x1
	.byte	0xa6
	.uleb128 0x1e
	.long	0x418
	.long	.LBB41
	.long	.LBE41
	.byte	0x1
	.byte	0xa6
	.uleb128 0x1f
	.long	0x425
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1429
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x20
	.long	.LASF139
	.byte	0x1
	.byte	0xb6
	.byte	0x1
	.long	0x30
	.long	.LFB74
	.long	.LFE74
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x669
	.uleb128 0x18
	.long	.LASF60
	.byte	0x1
	.byte	0xb6
	.long	0x489
	.long	.LLST2
	.uleb128 0x1b
	.long	.LASF81
	.byte	0x1
	.byte	0xb8
	.long	0x30
	.byte	0x1
	.byte	0x64
	.uleb128 0x1a
	.long	.LBB43
	.long	.LBE43
	.uleb128 0x1b
	.long	.LASF67
	.byte	0x1
	.byte	0xbd
	.long	0x30
	.byte	0x1
	.byte	0x62
	.uleb128 0x1c
	.long	.LASF68
	.byte	0x1
	.byte	0xbd
	.long	0x30
	.long	.LLST3
	.uleb128 0x1d
	.long	0x43c
	.long	.LBB44
	.long	.LBE44
	.byte	0x1
	.byte	0xbd
	.uleb128 0x1e
	.long	0x418
	.long	.LBB46
	.long	.LBE46
	.byte	0x1
	.byte	0xbd
	.uleb128 0x1f
	.long	0x425
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1568
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.long	.LASF90
	.byte	0x3
	.byte	0x71
	.byte	0x1
	.long	.LFB87
	.long	.LFE87
	.long	.LLST4
	.byte	0x1
	.long	0x6bc
	.uleb128 0x18
	.long	.LASF82
	.byte	0x3
	.byte	0x71
	.long	0x6bc
	.long	.LLST5
	.uleb128 0x22
	.string	"len"
	.byte	0x3
	.byte	0x71
	.long	0x3da
	.long	.LLST6
	.uleb128 0x23
	.string	"cin"
	.byte	0x3
	.byte	0x72
	.long	0x3da
	.byte	0x1
	.byte	0x69
	.uleb128 0x24
	.string	"i"
	.byte	0x3
	.byte	0x73
	.long	0x3da
	.long	.LLST7
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x3da
	.uleb128 0x25
	.byte	0x1
	.long	.LASF98
	.byte	0x3
	.byte	0x8d
	.byte	0x1
	.long	0x3da
	.long	.LFB88
	.long	.LFE88
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x74b
	.uleb128 0x18
	.long	.LASF83
	.byte	0x3
	.byte	0x8d
	.long	0x3da
	.long	.LLST8
	.uleb128 0x23
	.string	"PC"
	.byte	0x3
	.byte	0x8e
	.long	0x3da
	.byte	0x5
	.byte	0x3
	.long	PC.3160
	.uleb128 0x1b
	.long	.LASF84
	.byte	0x3
	.byte	0x8f
	.long	0x3da
	.byte	0x5
	.byte	0x3
	.long	SysEx.3161
	.uleb128 0x1b
	.long	.LASF85
	.byte	0x3
	.byte	0x90
	.long	0x3da
	.byte	0x5
	.byte	0x3
	.long	sysExCnt.3162
	.uleb128 0x1b
	.long	.LASF86
	.byte	0x3
	.byte	0x91
	.long	0x75b
	.byte	0x5
	.byte	0x3
	.long	stateTransTable.3163
	.uleb128 0x1a
	.long	.LBB48
	.long	.LBE48
	.uleb128 0x24
	.string	"tt"
	.byte	0x3
	.byte	0xcf
	.long	0x3da
	.long	.LLST9
	.byte	0
	.byte	0
	.uleb128 0xd
	.long	0x3da
	.long	0x75b
	.uleb128 0xe
	.long	0x8d
	.byte	0xf
	.byte	0
	.uleb128 0x9
	.long	0x74b
	.uleb128 0x10
	.long	.LASF87
	.byte	0x4
	.byte	0x49
	.byte	0x1
	.byte	0x3
	.long	0x779
	.uleb128 0x14
	.long	.LASF88
	.byte	0x4
	.byte	0x49
	.long	0x437
	.byte	0
	.uleb128 0x10
	.long	.LASF89
	.byte	0x4
	.byte	0x4e
	.byte	0x1
	.byte	0x3
	.long	0x792
	.uleb128 0x14
	.long	.LASF88
	.byte	0x4
	.byte	0x4e
	.long	0x437
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.long	.LASF91
	.byte	0x3
	.byte	0xe8
	.byte	0x1
	.long	.LFB90
	.long	.LFE90
	.long	.LLST10
	.byte	0x1
	.long	0x8ea
	.uleb128 0x23
	.string	"cnt"
	.byte	0x3
	.byte	0xea
	.long	0x30
	.byte	0x5
	.byte	0x3
	.long	cnt.3170
	.uleb128 0x1a
	.long	.LBB58
	.long	.LBE58
	.uleb128 0x1b
	.long	.LASF92
	.byte	0x3
	.byte	0xfe
	.long	0x2c7
	.byte	0x2
	.byte	0x8c
	.sleb128 1
	.uleb128 0x26
	.long	0x760
	.long	.LBB59
	.long	.LBE59
	.byte	0x3
	.byte	0xf2
	.long	0x7f1
	.uleb128 0x27
	.long	0x76d
	.long	.LLST11
	.byte	0
	.uleb128 0x28
	.long	0x760
	.long	.LBB61
	.long	.LBE61
	.byte	0x3
	.word	0x102
	.long	0x80f
	.uleb128 0x27
	.long	0x76d
	.long	.LLST12
	.byte	0
	.uleb128 0x28
	.long	0x779
	.long	.LBB63
	.long	.LBE63
	.byte	0x3
	.word	0x110
	.long	0x82d
	.uleb128 0x27
	.long	0x786
	.long	.LLST13
	.byte	0
	.uleb128 0x28
	.long	0x779
	.long	.LBB65
	.long	.LBE65
	.byte	0x3
	.word	0x114
	.long	0x84b
	.uleb128 0x27
	.long	0x786
	.long	.LLST14
	.byte	0
	.uleb128 0x29
	.long	.LVL30
	.long	0x6c2
	.uleb128 0x2a
	.long	.LVL33
	.long	0x1069
	.long	0x87e
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.uleb128 0x2b
	.byte	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	utx_buf
	.byte	0
	.uleb128 0x2a
	.long	.LVL34
	.long	0x1096
	.long	0x89a
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.byte	0
	.uleb128 0x2a
	.long	.LVL35
	.long	0x10ae
	.long	0x8c1
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.uleb128 0x2b
	.byte	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x8c
	.sleb128 1
	.byte	0
	.uleb128 0x2a
	.long	.LVL36
	.long	0x669
	.long	0x8df
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x8c
	.sleb128 1
	.uleb128 0x2b
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x34
	.byte	0
	.uleb128 0x29
	.long	.LVL42
	.long	0x10d6
	.byte	0
	.byte	0
	.uleb128 0x10
	.long	.LASF93
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x3
	.long	0x91b
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x55
	.long	0x489
	.uleb128 0x16
	.uleb128 0x15
	.long	.LASF67
	.byte	0x1
	.byte	0x57
	.long	0x30
	.uleb128 0x15
	.long	.LASF68
	.byte	0x1
	.byte	0x57
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF94
	.byte	0x3
	.word	0x125
	.byte	0x1
	.long	.LFB91
	.long	.LFE91
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xd0a
	.uleb128 0x28
	.long	0x8ea
	.long	.LBB118
	.long	.LBE118
	.byte	0x3
	.word	0x127
	.long	0x99b
	.uleb128 0x1f
	.long	0x8f7
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x1a
	.long	.LBB119
	.long	.LBE119
	.uleb128 0x2d
	.long	0x903
	.long	.LLST15
	.uleb128 0x2d
	.long	0x90e
	.long	.LLST16
	.uleb128 0x1d
	.long	0x43c
	.long	.LBB120
	.long	.LBE120
	.byte	0x1
	.byte	0x57
	.uleb128 0x1e
	.long	0x418
	.long	.LBB122
	.long	.LBE122
	.byte	0x1
	.byte	0x57
	.uleb128 0x27
	.long	0x425
	.long	.LLST17
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x28
	.long	0x8ea
	.long	.LBB124
	.long	.LBE124
	.byte	0x3
	.word	0x128
	.long	0xa00
	.uleb128 0x1f
	.long	0x8f7
	.byte	0x6
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0x9f
	.uleb128 0x1a
	.long	.LBB125
	.long	.LBE125
	.uleb128 0x2d
	.long	0x903
	.long	.LLST18
	.uleb128 0x2d
	.long	0x90e
	.long	.LLST19
	.uleb128 0x1d
	.long	0x43c
	.long	.LBB126
	.long	.LBE126
	.byte	0x1
	.byte	0x57
	.uleb128 0x1e
	.long	0x418
	.long	.LBB128
	.long	.LBE128
	.byte	0x1
	.byte	0x57
	.uleb128 0x27
	.long	0x425
	.long	.LLST20
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1a
	.long	.LBB130
	.long	.LBE130
	.uleb128 0x2e
	.long	.LASF95
	.byte	0x3
	.word	0x139
	.long	0x30
	.long	.LLST21
	.uleb128 0x28
	.long	0x4ef
	.long	.LBB131
	.long	.LBE131
	.byte	0x3
	.word	0x12f
	.long	0xaa6
	.uleb128 0x1f
	.long	0x500
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x1e
	.long	0x449
	.long	.LBB132
	.long	.LBE132
	.byte	0x1
	.byte	0x81
	.uleb128 0x2f
	.long	0x45a
	.uleb128 0x1a
	.long	.LBB133
	.long	.LBE133
	.uleb128 0x2d
	.long	0x465
	.long	.LLST22
	.uleb128 0x1a
	.long	.LBB134
	.long	.LBE134
	.uleb128 0x2d
	.long	0x471
	.long	.LLST23
	.uleb128 0x2d
	.long	0x47c
	.long	.LLST24
	.uleb128 0x1d
	.long	0x43c
	.long	.LBB135
	.long	.LBE135
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1e
	.long	0x418
	.long	.LBB137
	.long	.LBE137
	.byte	0x1
	.byte	0x6f
	.uleb128 0x27
	.long	0x425
	.long	.LLST25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x30
	.long	.LBB139
	.long	.LBE139
	.long	0xaf8
	.uleb128 0x2e
	.long	.LASF96
	.byte	0x3
	.word	0x131
	.long	0x42
	.long	.LLST26
	.uleb128 0x2a
	.long	.LVL57
	.long	0x10e0
	.long	0xadf
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x31
	.long	.LVL59
	.long	0x557
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0
	.byte	0
	.uleb128 0x28
	.long	0x449
	.long	.LBB140
	.long	.LBE140
	.byte	0x3
	.word	0x139
	.long	0xb69
	.uleb128 0x2f
	.long	0x45a
	.uleb128 0x1a
	.long	.LBB141
	.long	.LBE141
	.uleb128 0x2d
	.long	0x465
	.long	.LLST27
	.uleb128 0x1a
	.long	.LBB142
	.long	.LBE142
	.uleb128 0x2d
	.long	0x471
	.long	.LLST28
	.uleb128 0x2d
	.long	0x47c
	.long	.LLST29
	.uleb128 0x1d
	.long	0x43c
	.long	.LBB143
	.long	.LBE143
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1e
	.long	0x418
	.long	.LBB145
	.long	.LBE145
	.byte	0x1
	.byte	0x6f
	.uleb128 0x27
	.long	0x425
	.long	.LLST30
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x28
	.long	0x760
	.long	.LBB147
	.long	.LBE147
	.byte	0x3
	.word	0x13f
	.long	0xb87
	.uleb128 0x27
	.long	0x76d
	.long	.LLST31
	.byte	0
	.uleb128 0x28
	.long	0x779
	.long	.LBB149
	.long	.LBE149
	.byte	0x3
	.word	0x149
	.long	0xba5
	.uleb128 0x27
	.long	0x786
	.long	.LLST32
	.byte	0
	.uleb128 0x28
	.long	0x779
	.long	.LBB151
	.long	.LBE151
	.byte	0x3
	.word	0x14d
	.long	0xbc3
	.uleb128 0x27
	.long	0x786
	.long	.LLST33
	.byte	0
	.uleb128 0x28
	.long	0x50c
	.long	.LBB153
	.long	.LBE153
	.byte	0x3
	.word	0x151
	.long	0xc53
	.uleb128 0x1f
	.long	0x51d
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x1e
	.long	0x449
	.long	.LBB154
	.long	.LBE154
	.byte	0x1
	.byte	0x92
	.uleb128 0x2f
	.long	0x45a
	.uleb128 0x1a
	.long	.LBB155
	.long	.LBE155
	.uleb128 0x2d
	.long	0x465
	.long	.LLST34
	.uleb128 0x1a
	.long	.LBB156
	.long	.LBE156
	.uleb128 0x2d
	.long	0x471
	.long	.LLST35
	.uleb128 0x2d
	.long	0x47c
	.long	.LLST36
	.uleb128 0x1d
	.long	0x43c
	.long	.LBB157
	.long	.LBE157
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1e
	.long	0x418
	.long	.LBB159
	.long	.LBE159
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1f
	.long	0x425
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3090
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x28
	.long	0x4b8
	.long	.LBB161
	.long	.LBE161
	.byte	0x3
	.word	0x152
	.long	0xc71
	.uleb128 0x27
	.long	0x4c5
	.long	.LLST37
	.byte	0
	.uleb128 0x28
	.long	0x760
	.long	.LBB163
	.long	.LBE163
	.byte	0x3
	.word	0x154
	.long	0xc8f
	.uleb128 0x27
	.long	0x76d
	.long	.LLST38
	.byte	0
	.uleb128 0x2a
	.long	.LVL66
	.long	0x5de
	.long	0xcab
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0
	.uleb128 0x2a
	.long	.LVL67
	.long	0x10f9
	.long	0xcc7
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x2a
	.long	.LVL78
	.long	0x5de
	.long	0xce3
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0
	.uleb128 0x2a
	.long	.LVL81
	.long	0x1116
	.long	0xcff
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x29
	.long	.LVL82
	.long	0x10d6
	.byte	0
	.byte	0
	.uleb128 0x32
	.long	.LASF140
	.byte	0x4
	.byte	0x43
	.byte	0x1
	.byte	0x3
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF97
	.byte	0x3
	.word	0x15f
	.byte	0x1
	.long	.LFB92
	.long	.LFE92
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xd6f
	.uleb128 0x28
	.long	0x529
	.long	.LBB169
	.long	.LBE169
	.byte	0x3
	.word	0x16a
	.long	0xd55
	.uleb128 0x27
	.long	0x536
	.long	.LLST39
	.uleb128 0x27
	.long	0x541
	.long	.LLST40
	.byte	0
	.uleb128 0x33
	.long	0xd0a
	.long	.LBB171
	.long	.LBE171
	.byte	0x3
	.word	0x17d
	.uleb128 0x29
	.long	.LVL85
	.long	0x112a
	.byte	0
	.uleb128 0x25
	.byte	0x1
	.long	.LASF99
	.byte	0x3
	.byte	0xdd
	.byte	0x1
	.long	0x4d
	.long	.LFB89
	.long	.LFE89
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xda9
	.uleb128 0x29
	.long	.LVL86
	.long	0xd13
	.uleb128 0x29
	.long	.LVL87
	.long	0x792
	.uleb128 0x29
	.long	.LVL88
	.long	0x91b
	.byte	0
	.uleb128 0x34
	.byte	0x1
	.long	.LASF100
	.byte	0x3
	.word	0x187
	.byte	0x1
	.long	.LFB93
	.long	.LFE93
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x34
	.byte	0x1
	.long	.LASF101
	.byte	0x3
	.word	0x18b
	.byte	0x1
	.long	.LFB94
	.long	.LFE94
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF102
	.byte	0x3
	.word	0x18f
	.byte	0x1
	.long	.LFB95
	.long	.LFE95
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xe43
	.uleb128 0x30
	.long	.LBB173
	.long	.LBE173
	.long	0xe29
	.uleb128 0x2e
	.long	.LASF103
	.byte	0x3
	.word	0x191
	.long	0x1ab
	.long	.LLST41
	.uleb128 0x35
	.long	.LVL90
	.byte	0x1
	.long	0x1135
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.byte	0
	.byte	0
	.uleb128 0x35
	.long	.LVL91
	.byte	0x1
	.long	0x114d
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.byte	0
	.uleb128 0x34
	.byte	0x1
	.long	.LASF104
	.byte	0x3
	.word	0x199
	.byte	0x1
	.long	.LFB96
	.long	.LFE96
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF105
	.byte	0x3
	.word	0x1a0
	.byte	0x1
	.long	.LFB97
	.long	.LFE97
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xe8f
	.uleb128 0x35
	.long	.LVL92
	.byte	0x1
	.long	0x1165
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.long	.LASF106
	.byte	0x3
	.word	0x1ac
	.byte	0x1
	.long	.LFB98
	.long	.LFE98
	.long	.LLST42
	.byte	0x1
	.long	0xecb
	.uleb128 0x37
	.long	.LASF107
	.byte	0x3
	.word	0x1ac
	.long	0xecb
	.long	.LLST43
	.uleb128 0x2e
	.long	.LASF108
	.byte	0x3
	.word	0x1ad
	.long	0x30
	.long	.LLST44
	.byte	0
	.uleb128 0x9
	.long	0xed0
	.uleb128 0xf
	.byte	0x2
	.long	0x267
	.uleb128 0x36
	.byte	0x1
	.long	.LASF109
	.byte	0x3
	.word	0x1db
	.byte	0x1
	.long	.LFB99
	.long	.LFE99
	.long	.LLST45
	.byte	0x1
	.long	0xf24
	.uleb128 0x1a
	.long	.LBB174
	.long	.LBE174
	.uleb128 0x2e
	.long	.LASF96
	.byte	0x3
	.word	0x1dd
	.long	0x30
	.long	.LLST46
	.uleb128 0x31
	.long	.LVL106
	.long	0x557
	.uleb128 0x2b
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF110
	.byte	0x3
	.word	0x1e8
	.byte	0x1
	.long	.LFB100
	.long	.LFE100
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xf60
	.uleb128 0x37
	.long	.LASF107
	.byte	0x3
	.word	0x1e8
	.long	0xecb
	.long	.LLST47
	.uleb128 0x2e
	.long	.LASF111
	.byte	0x3
	.word	0x1e9
	.long	0x1ab
	.long	.LLST48
	.byte	0
	.uleb128 0x1b
	.long	.LASF112
	.byte	0x3
	.byte	0x43
	.long	0x3da
	.byte	0x5
	.byte	0x3
	.long	utxrdy
	.uleb128 0xd
	.long	0x3da
	.long	0xf81
	.uleb128 0xe
	.long	0x8d
	.byte	0x7
	.byte	0
	.uleb128 0x1b
	.long	.LASF113
	.byte	0x3
	.byte	0x44
	.long	0xf71
	.byte	0x5
	.byte	0x3
	.long	rx_buf
	.uleb128 0x1b
	.long	.LASF114
	.byte	0x3
	.byte	0x45
	.long	0xf71
	.byte	0x5
	.byte	0x3
	.long	utx_buf
	.uleb128 0x1b
	.long	.LASF115
	.byte	0x3
	.byte	0x49
	.long	0x3da
	.byte	0x5
	.byte	0x3
	.long	uwptr
	.uleb128 0x1b
	.long	.LASF116
	.byte	0x3
	.byte	0x49
	.long	0x3da
	.byte	0x5
	.byte	0x3
	.long	irptr
	.uleb128 0xd
	.long	0x3da
	.long	0xfd5
	.uleb128 0xe
	.long	0x8d
	.byte	0x1f
	.byte	0
	.uleb128 0x1b
	.long	.LASF117
	.byte	0x3
	.byte	0x4a
	.long	0xfc5
	.byte	0x5
	.byte	0x3
	.long	tx_buf
	.uleb128 0x38
	.long	.LASF118
	.byte	0x3
	.byte	0x31
	.long	0x3da
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	mocoMode
	.uleb128 0x38
	.long	.LASF119
	.byte	0x3
	.byte	0x32
	.long	0x3da
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	highSpeed
	.uleb128 0x38
	.long	.LASF120
	.byte	0x3
	.byte	0x36
	.long	0x3cf
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.uleb128 0x38
	.long	.LASF121
	.byte	0x3
	.byte	0x39
	.long	0x3cf
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.uleb128 0x38
	.long	.LASF122
	.byte	0x3
	.byte	0x40
	.long	0x1040
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	PulseMSRemaining
	.uleb128 0x39
	.long	0x3e5
	.uleb128 0x38
	.long	.LASF123
	.byte	0x3
	.byte	0x51
	.long	0x267
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.uleb128 0x38
	.long	.LASF124
	.byte	0x3
	.byte	0x63
	.long	0x36b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.uleb128 0x3a
	.byte	0x1
	.long	.LASF125
	.byte	0xb
	.byte	0x7f
	.byte	0x1
	.long	0x30
	.byte	0x1
	.long	0x1086
	.uleb128 0x3b
	.long	0x4ad
	.uleb128 0x3b
	.long	0x1086
	.byte	0
	.uleb128 0x9
	.long	0x108b
	.uleb128 0xf
	.byte	0x2
	.long	0x1091
	.uleb128 0x9
	.long	0x2c7
	.uleb128 0x3a
	.byte	0x1
	.long	.LASF126
	.byte	0xb
	.byte	0x8a
	.byte	0x1
	.long	0x30
	.byte	0x1
	.long	0x10ae
	.uleb128 0x3b
	.long	0x4ad
	.byte	0
	.uleb128 0x3a
	.byte	0x1
	.long	.LASF127
	.byte	0xb
	.byte	0x97
	.byte	0x1
	.long	0x1ab
	.byte	0x1
	.long	0x10cb
	.uleb128 0x3b
	.long	0x4ad
	.uleb128 0x3b
	.long	0x10cb
	.byte	0
	.uleb128 0x9
	.long	0x10d0
	.uleb128 0xf
	.byte	0x2
	.long	0x2c7
	.uleb128 0x3c
	.byte	0x1
	.long	.LASF130
	.byte	0xd
	.byte	0xb2
	.byte	0x1
	.byte	0x1
	.uleb128 0x3d
	.byte	0x1
	.long	.LASF128
	.byte	0x9
	.word	0x106
	.byte	0x1
	.long	0x42
	.byte	0x1
	.long	0x10f9
	.uleb128 0x3b
	.long	0xecb
	.byte	0
	.uleb128 0x3a
	.byte	0x1
	.long	.LASF129
	.byte	0x9
	.byte	0xe9
	.byte	0x1
	.long	0x30
	.byte	0x1
	.long	0x1116
	.uleb128 0x3b
	.long	0xecb
	.uleb128 0x3b
	.long	0x437
	.byte	0
	.uleb128 0x3e
	.byte	0x1
	.long	.LASF141
	.byte	0x9
	.byte	0xac
	.byte	0x1
	.byte	0x1
	.long	0x112a
	.uleb128 0x3b
	.long	0xecb
	.byte	0
	.uleb128 0x3f
	.byte	0x1
	.long	.LASF131
	.byte	0xe
	.word	0x123
	.byte	0x1
	.byte	0x1
	.uleb128 0x3a
	.byte	0x1
	.long	.LASF132
	.byte	0xb
	.byte	0x71
	.byte	0x1
	.long	0x1ab
	.byte	0x1
	.long	0x114d
	.uleb128 0x3b
	.long	0x4ad
	.byte	0
	.uleb128 0x3a
	.byte	0x1
	.long	.LASF133
	.byte	0x9
	.byte	0x9e
	.byte	0x1
	.long	0x1ab
	.byte	0x1
	.long	0x1165
	.uleb128 0x3b
	.long	0xecb
	.byte	0
	.uleb128 0x40
	.byte	0x1
	.long	.LASF142
	.byte	0x9
	.byte	0xa5
	.byte	0x1
	.byte	0x1
	.uleb128 0x3b
	.long	0xecb
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL0
	.long	.LVL3
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL3
	.long	.LFE73
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST1:
	.long	.LVL2
	.long	.LVL4
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL4
	.long	.LFE73
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST2:
	.long	.LVL5
	.long	.LVL10
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL10
	.long	.LFE74
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL8
	.long	.LVL9
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL9
	.long	.LFE74
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LFB87
	.long	.LCFI0
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI0
	.long	.LCFI1
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI1
	.long	.LFE87
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST5:
	.long	.LVL11
	.long	.LVL12
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL12
	.long	.LFE87
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST6:
	.long	.LVL11
	.long	.LVL12
	.word	0x1
	.byte	0x66
	.long	.LVL12
	.long	.LFE87
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST7:
	.long	.LVL14
	.long	.LVL15
	.word	0x1
	.byte	0x68
	.long	.LVL15
	.long	.LVL16
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL16
	.long	.LVL17
	.word	0x1
	.byte	0x68
	.long	.LVL18
	.long	.LVL19
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST8:
	.long	.LVL20
	.long	.LVL21
	.word	0x1
	.byte	0x68
	.long	.LVL21
	.long	.LVL22
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	.LVL22
	.long	.LVL23
	.word	0x1
	.byte	0x68
	.long	.LVL23
	.long	.LVL24
	.word	0x5
	.byte	0x3
	.long	utx_buf+1
	.long	.LVL24
	.long	.LVL25
	.word	0x1
	.byte	0x68
	.long	.LVL25
	.long	.LVL26
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	.LVL26
	.long	.LVL28
	.word	0x1
	.byte	0x68
	.long	.LVL28
	.long	.LVL29
	.word	0x2
	.byte	0x8e
	.sleb128 2
	.long	.LVL29
	.long	.LFE88
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST9:
	.long	.LVL27
	.long	.LVL29
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST10:
	.long	.LFB90
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI5
	.long	.LFE90
	.word	0x2
	.byte	0x8c
	.sleb128 8
	.long	0
	.long	0
.LLST11:
	.long	.LVL31
	.long	.LVL32
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST12:
	.long	.LVL36
	.long	.LVL37
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST13:
	.long	.LVL38
	.long	.LVL39
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST14:
	.long	.LVL40
	.long	.LVL41
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST15:
	.long	.LVL44
	.long	.LVL48
	.word	0x1
	.byte	0x62
	.long	.LVL48
	.long	.LVL51
	.word	0x2
	.byte	0x8
	.byte	0x5f
	.long	0
	.long	0
.LLST16:
	.long	.LVL45
	.long	.LVL46
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL46
	.long	.LFE91
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST17:
	.long	.LVL46
	.long	.LVL50
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2399
	.sleb128 0
	.long	.LVL50
	.long	.LVL52
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2500
	.sleb128 0
	.long	.LVL55
	.long	.LVL62
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2664
	.sleb128 0
	.long	.LVL62
	.long	.LVL76
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2860
	.sleb128 0
	.long	.LVL76
	.long	.LFE91
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3090
	.sleb128 0
	.long	0
	.long	0
.LLST18:
	.long	.LVL48
	.long	.LVL52
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST19:
	.long	.LVL49
	.long	.LVL50
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL50
	.long	.LFE91
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST20:
	.long	.LVL50
	.long	.LVL52
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2500
	.sleb128 0
	.long	.LVL55
	.long	.LVL62
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2664
	.sleb128 0
	.long	.LVL62
	.long	.LVL76
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2860
	.sleb128 0
	.long	.LVL76
	.long	.LFE91
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3090
	.sleb128 0
	.long	0
	.long	0
.LLST21:
	.long	.LVL65
	.long	.LVL68
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	.LVL68
	.long	.LVL69
	.word	0x1
	.byte	0x6c
	.long	.LVL69
	.long	.LVL73
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	0
	.long	0
.LLST22:
	.long	.LVL55
	.long	.LVL56
	.word	0x1
	.byte	0x68
	.long	.LVL56
	.long	.LVL57-1
	.word	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer+132
	.long	0
	.long	0
.LLST23:
	.long	.LVL53
	.long	.LVL57-1
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST24:
	.long	.LVL54
	.long	.LVL55
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL55
	.long	.LFE91
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST25:
	.long	.LVL55
	.long	.LVL62
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2664
	.sleb128 0
	.long	.LVL62
	.long	.LVL76
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2860
	.sleb128 0
	.long	.LVL76
	.long	.LFE91
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3090
	.sleb128 0
	.long	0
	.long	0
.LLST26:
	.long	.LVL57
	.long	.LVL58
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST27:
	.long	.LVL62
	.long	.LVL65
	.word	0x1
	.byte	0x6c
	.long	0
	.long	0
.LLST28:
	.long	.LVL60
	.long	.LVL63
	.word	0x1
	.byte	0x68
	.long	.LVL63
	.long	.LVL65
	.word	0x2
	.byte	0x8
	.byte	0x5f
	.long	0
	.long	0
.LLST29:
	.long	.LVL61
	.long	.LVL62
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL62
	.long	.LFE91
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST30:
	.long	.LVL62
	.long	.LVL76
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2860
	.sleb128 0
	.long	.LVL76
	.long	.LFE91
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3090
	.sleb128 0
	.long	0
	.long	0
.LLST31:
	.long	.LVL64
	.long	.LVL65
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST32:
	.long	.LVL70
	.long	.LVL71
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST33:
	.long	.LVL72
	.long	.LVL73
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST34:
	.long	.LVL76
	.long	.LVL77
	.word	0x1
	.byte	0x68
	.long	.LVL77
	.long	.LVL78-1
	.word	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer+132
	.long	0
	.long	0
.LLST35:
	.long	.LVL74
	.long	.LVL78-1
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST36:
	.long	.LVL75
	.long	.LVL76
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL76
	.long	.LFE91
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST37:
	.long	.LVL78
	.long	.LVL80
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST38:
	.long	.LVL79
	.long	.LVL80
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST39:
	.long	.LVL83
	.long	.LVL84
	.word	0x4
	.byte	0xa
	.word	0x2580
	.byte	0x9f
	.long	0
	.long	0
.LLST40:
	.long	.LVL83
	.long	.LVL84
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST41:
	.long	.LVL89
	.long	.LVL90
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	0
	.long	0
.LLST42:
	.long	.LFB98
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI8
	.long	.LFE98
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	0
	.long	0
.LLST43:
	.long	.LVL93
	.long	.LVL95
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL95
	.long	.LVL103
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL103
	.long	.LFE98
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST44:
	.long	.LVL94
	.long	.LVL96
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL96
	.long	.LVL97
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	.LVL97
	.long	.LVL98
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL98
	.long	.LVL104
	.word	0x1
	.byte	0x61
	.long	0
	.long	0
.LLST45:
	.long	.LFB99
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI10
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI12
	.long	.LCFI13
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI13
	.long	.LCFI14
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI14
	.long	.LCFI15
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI15
	.long	.LCFI16
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI16
	.long	.LCFI17
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI17
	.long	.LCFI18
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	.LCFI18
	.long	.LCFI19
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 12
	.long	.LCFI19
	.long	.LCFI20
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 13
	.long	.LCFI20
	.long	.LCFI21
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 14
	.long	.LCFI21
	.long	.LCFI22
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 15
	.long	.LCFI22
	.long	.LFE99
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 16
	.long	0
	.long	0
.LLST46:
	.long	.LVL105
	.long	.LVL106-1
	.word	0x1
	.byte	0x66
	.long	0
	.long	0
.LLST47:
	.long	.LVL107
	.long	.LVL108
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL108
	.long	.LFE100
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST48:
	.long	.LVL107
	.long	.LVL108
	.word	0x7
	.byte	0x88
	.sleb128 13
	.byte	0x94
	.byte	0x1
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	.LVL108
	.long	.LFE100
	.word	0x5
	.byte	0x88
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x94
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB73
	.long	.LFE73-.LFB73
	.long	.LFB74
	.long	.LFE74-.LFB74
	.long	.LFB87
	.long	.LFE87-.LFB87
	.long	.LFB88
	.long	.LFE88-.LFB88
	.long	.LFB90
	.long	.LFE90-.LFB90
	.long	.LFB91
	.long	.LFE91-.LFB91
	.long	.LFB92
	.long	.LFE92-.LFB92
	.long	.LFB89
	.long	.LFE89-.LFB89
	.long	.LFB93
	.long	.LFE93-.LFB93
	.long	.LFB94
	.long	.LFE94-.LFB94
	.long	.LFB95
	.long	.LFE95-.LFB95
	.long	.LFB96
	.long	.LFE96-.LFB96
	.long	.LFB97
	.long	.LFE97-.LFB97
	.long	.LFB98
	.long	.LFE98-.LFB98
	.long	.LFB99
	.long	.LFE99-.LFB99
	.long	.LFB100
	.long	.LFE100-.LFB100
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB73
	.long	.LFE73
	.long	.LFB74
	.long	.LFE74
	.long	.LFB87
	.long	.LFE87
	.long	.LFB88
	.long	.LFE88
	.long	.LFB90
	.long	.LFE90
	.long	.LFB91
	.long	.LFE91
	.long	.LFB92
	.long	.LFE92
	.long	.LFB89
	.long	.LFE89
	.long	.LFB93
	.long	.LFE93
	.long	.LFB94
	.long	.LFE94
	.long	.LFB95
	.long	.LFE95
	.long	.LFB96
	.long	.LFE96
	.long	.LFB97
	.long	.LFE97
	.long	.LFB98
	.long	.LFE98
	.long	.LFB99
	.long	.LFE99
	.long	.LFB100
	.long	.LFE100
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF79:
	.string	"BaudRate"
.LASF141:
	.string	"CDC_Device_USBTask"
.LASF108:
	.string	"ConfigMask"
.LASF48:
	.string	"LineEncoding"
.LASF91:
	.string	"processMIDI"
.LASF114:
	.string	"utx_buf"
.LASF102:
	.string	"EVENT_USB_Device_ConfigurationChanged"
.LASF28:
	.string	"CDC_PARITY_Space"
.LASF16:
	.string	"DEVICE_STATE_Configured"
.LASF83:
	.string	"RxByte"
.LASF120:
	.string	"USBtoUSART_Buffer"
.LASF5:
	.string	"unsigned int"
.LASF43:
	.string	"BaudRateBPS"
.LASF84:
	.string	"SysEx"
.LASF97:
	.string	"SetupHardware"
.LASF140:
	.string	"LEDs_Init"
.LASF113:
	.string	"rx_buf"
.LASF93:
	.string	"RingBuffer_InitBuffer"
.LASF46:
	.string	"DataBits"
.LASF50:
	.string	"State"
.LASF33:
	.string	"DataINEndpointDoubleBank"
.LASF107:
	.string	"CDCInterfaceInfo"
.LASF31:
	.string	"DataINEndpointNumber"
.LASF135:
	.string	"dualMoco.c"
.LASF15:
	.string	"DEVICE_STATE_Addressed"
.LASF7:
	.string	"uint32_t"
.LASF36:
	.string	"DataOUTEndpointDoubleBank"
.LASF87:
	.string	"LEDs_TurnOnLEDs"
.LASF105:
	.string	"EVENT_USB_Device_UnhandledControlRequest"
.LASF59:
	.string	"USB_ClassInfo_MIDI_Device_t"
.LASF34:
	.string	"DataOUTEndpointNumber"
.LASF38:
	.string	"NotificationEndpointSize"
.LASF39:
	.string	"NotificationEndpointDoubleBank"
.LASF122:
	.string	"PulseMSRemaining"
.LASF3:
	.string	"int16_t"
.LASF10:
	.string	"long long unsigned int"
.LASF14:
	.string	"DEVICE_STATE_Default"
.LASF132:
	.string	"MIDI_Device_ConfigureEndpoints"
.LASF100:
	.string	"EVENT_USB_Device_Connect"
.LASF19:
	.string	"CDC_LineEncodingFormats_t"
.LASF116:
	.string	"irptr"
.LASF49:
	.string	"Config"
.LASF37:
	.string	"NotificationEndpointNumber"
.LASF125:
	.string	"MIDI_Device_SendEventPacket"
.LASF92:
	.string	"ReceivedMIDIEvent"
.LASF42:
	.string	"DeviceToHost"
.LASF128:
	.string	"CDC_Device_ReceiveByte"
.LASF126:
	.string	"MIDI_Device_Flush"
.LASF78:
	.string	"Serial_Init"
.LASF118:
	.string	"mocoMode"
.LASF40:
	.string	"_Bool"
.LASF80:
	.string	"DoubleSpeed"
.LASF77:
	.string	"RingBuffer_IsEmpty"
.LASF85:
	.string	"sysExCnt"
.LASF61:
	.string	"Count"
.LASF117:
	.string	"tx_buf"
.LASF35:
	.string	"DataOUTEndpointSize"
.LASF18:
	.string	"USB_Device_States_t"
.LASF138:
	.string	"RingBuffer_Insert"
.LASF29:
	.string	"char"
.LASF136:
	.string	"/home/dfourer/workspace/mocolufa"
.LASF70:
	.string	"MIDI_Device_USBTask"
.LASF82:
	.string	"data"
.LASF2:
	.string	"uint8_t"
.LASF121:
	.string	"USARTtoUSB_Buffer"
.LASF73:
	.string	"DataByte"
.LASF98:
	.string	"parseSerialMidiMessage"
.LASF65:
	.string	"RxLEDPulse"
.LASF131:
	.string	"USB_Init"
.LASF41:
	.string	"HostToDevice"
.LASF130:
	.string	"USB_USBTask"
.LASF9:
	.string	"long long int"
.LASF101:
	.string	"EVENT_USB_Device_Disconnect"
.LASF111:
	.string	"CurrentDTRState"
.LASF71:
	.string	"MIDIInterfaceInfo"
.LASF69:
	.string	"__iRestore"
.LASF75:
	.string	"RingBuffer_GetCount"
.LASF88:
	.string	"LEDMask"
.LASF12:
	.string	"DEVICE_STATE_Unattached"
.LASF89:
	.string	"LEDs_TurnOffLEDs"
.LASF103:
	.string	"ConfigSuccess"
.LASF124:
	.string	"Keyboard_MIDI_Interface"
.LASF30:
	.string	"ControlInterfaceNumber"
.LASF63:
	.string	"uchar"
.LASF74:
	.string	"MIDI_Device_ProcessControlRequest"
.LASF20:
	.string	"CDC_LINEENCODING_OneStopBit"
.LASF25:
	.string	"CDC_PARITY_Odd"
.LASF66:
	.string	"PingPongLEDPulse"
.LASF67:
	.string	"sreg_save"
.LASF4:
	.string	"uint16_t"
.LASF127:
	.string	"MIDI_Device_ReceiveEventPacket"
.LASF62:
	.string	"RingBuff_t"
.LASF54:
	.string	"Data1"
.LASF55:
	.string	"Data2"
.LASF56:
	.string	"Data3"
.LASF76:
	.string	"RingBuffer_IsFull"
.LASF60:
	.string	"Buffer"
.LASF6:
	.string	"long int"
.LASF123:
	.string	"VirtualSerial_CDC_Interface"
.LASF32:
	.string	"DataINEndpointSize"
.LASF142:
	.string	"CDC_Device_ProcessControlRequest"
.LASF13:
	.string	"DEVICE_STATE_Powered"
.LASF52:
	.string	"Command"
.LASF139:
	.string	"RingBuffer_Remove"
.LASF95:
	.string	"BufferCount"
.LASF24:
	.string	"CDC_PARITY_None"
.LASF26:
	.string	"CDC_PARITY_Even"
.LASF72:
	.string	"Serial_TxByte"
.LASF94:
	.string	"processSerial"
.LASF90:
	.string	"parseUSBMidiMessage"
.LASF11:
	.string	"sizetype"
.LASF8:
	.string	"long unsigned int"
.LASF106:
	.string	"EVENT_CDC_Device_LineEncodingChanged"
.LASF104:
	.string	"EVENT_USB_Device_ControlRequest"
.LASF21:
	.string	"CDC_LINEENCODING_OneAndAHalfStopBits"
.LASF1:
	.string	"unsigned char"
.LASF129:
	.string	"CDC_Device_SendByte"
.LASF17:
	.string	"DEVICE_STATE_Suspended"
.LASF53:
	.string	"CableNumber"
.LASF115:
	.string	"uwptr"
.LASF57:
	.string	"MIDI_EventPacket_t"
.LASF119:
	.string	"highSpeed"
.LASF51:
	.string	"USB_ClassInfo_CDC_Device_t"
.LASF86:
	.string	"stateTransTable"
.LASF27:
	.string	"CDC_PARITY_Mark"
.LASF96:
	.string	"ReceivedByte"
.LASF0:
	.string	"signed char"
.LASF22:
	.string	"CDC_LINEENCODING_TwoStopBits"
.LASF99:
	.string	"main"
.LASF23:
	.string	"CDC_LineEncodingParity_t"
.LASF137:
	.string	"__iCliRetVal"
.LASF68:
	.string	"__ToDo"
.LASF64:
	.string	"TxLEDPulse"
.LASF45:
	.string	"ParityType"
.LASF133:
	.string	"CDC_Device_ConfigureEndpoints"
.LASF58:
	.string	"StreamingInterfaceNumber"
.LASF47:
	.string	"ControlLineStates"
.LASF109:
	.string	"__vector_23"
.LASF110:
	.string	"EVENT_CDC_Device_ControLineStateChanged"
.LASF44:
	.string	"CharFormat"
.LASF81:
	.string	"Data"
.LASF112:
	.string	"utxrdy"
.LASF134:
	.string	"GNU C 4.8.2 -mmcu=atmega16u2 -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing"
	.ident	"GCC: (GNU) 4.8.2"
.global __do_copy_data
.global __do_clear_bss
