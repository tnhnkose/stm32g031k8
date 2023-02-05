/*
 * asm.s
 *
 * author: Tunahan Köseoğlu
 *
 * Description:  Connecting 8 LEDs to the board, and implementing a “Knight  Rider ”
 *
 */


.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb


/* make linker see this */
.global Reset_Handler

/* get these from linker script */
.word _sdata
.word _edata
.word _sbss
.word _ebss


/* define peripheral addresses from RM0444 page 57, Tables 3-4 */
.equ RCC_BASE,         (0x40021000)          // RCC base address
.equ RCC_IOPENR,       (RCC_BASE   + (0x34)) // RCC IOPENR register offset

.equ GPIOB_BASE,       (0x50000400)          // GPIOC base address
.equ GPIOB_MODER,      (GPIOB_BASE + (0x00)) // GPIOC MODER register offset
.equ GPIOB_ODR,        (GPIOB_BASE + (0x14)) // GPIOC ODR register offset
.equ GPIOB_IDR,        (GPIOB_BASE + (0x10)) // GPIOC IDR register offset



/* vector table, +1 thumb mode */
.section .vectors
vector_table:
	.word _estack             /*     Stack pointer */
	.word Reset_Handler +1    /*     Reset handler */
	.word Default_Handler +1  /*       NMI handler */
	.word Default_Handler +1  /* HardFault handler */
	/* add rest of them here if needed */


/* reset handler */
.section .text
Reset_Handler:
	/* set stack pointer */
	ldr r0, =_estack
	mov sp, r0

	/* initialize data and bss 
	 * not necessary for rom only code 
	 * */
	bl init_data
	/* call main */
	bl main
	/* trap if returned */
	b .


/* initialize data and bss sections */
.section .text
init_data:

	/* copy rom to ram */
	ldr r0, =_sdata
	ldr r1, =_edata
	ldr r2, =_sidata
	movs r3, #0
	b LoopCopyDataInit

	CopyDataInit:
		ldr r4, [r2, r3]
		str r4, [r0, r3]
		adds r3, r3, #4

	LoopCopyDataInit:
		adds r4, r0, r3
		cmp r4, r1
		bcc CopyDataInit

	/* zero bss */
	ldr r2, =_sbss
	ldr r4, =_ebss
	movs r3, #0
	b LoopFillZerobss

	FillZerobss:
		str  r3, [r2]
		adds r2, r2, #4

	LoopFillZerobss:
		cmp r2, r4
		bcc FillZerobss

	bx lr


/* default handler */
.section .text
Default_Handler:
	b Default_Handler


/* main function */
.section .text
main:
		/* enable GPIOB clock, bit2 on IOPENR */
	ldr r6, =RCC_IOPENR
	ldr r5, [r6]
	/* movs expects imm8, so this should be fine */
	movs r4, 0x2
	orrs r5, r5, r4
	str r5, [r6]



	/* setup PB1 for LED 01 for bits 2-3 in MODER */
	ldr r6, =GPIOB_MODER
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0x5555
	orrs r5, r5, r4
	str r5, [r6]



	bl t0
	bl delay

	bl t1
	bl delay

	loop:

	bl t2
	bl delay


	bl t3
	bl delay


	bl t4
	bl delay


	bl t5
	bl delay


	bl t6
	bl delay


	bl t7
	bl delay


	bl t6
	bl delay


	bl t5
	bl delay


	bl t4
	bl delay


	bl t3
	bl delay

	b loop

	t0:
	/* setup PB0 for LED  for bits 0 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0x1
	orrs r5, r5, r4
	str r5, [r6]
	bx lr

	t1:
	/* setup PB0-1 for LED  for bits 0-1 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0x3
	orrs r5, r5, r4
	str r5, [r6]
	bx lr

	t2:
	/* setup PB0-2 for LED  for bits 0-2 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0x7
	orrs r5, r5, r4
	str r5, [r6]
	bx lr


	t3:

	/* setup PB1-3 for LED  for bits 1-3 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0xE
	orrs r5, r5, r4
	str r5, [r6]
	bx lr


	t4:

	/* setup PB2-4 for LED  for bits 2-4 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0x1C
	orrs r5, r5, r4
	str r5, [r6]
	bx lr


	t5:

	/* setup PB3-5 for LED  for bits 3-5 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0x38
	orrs r5, r5, r4
	str r5, [r6]
	bx lr

	t6:

	/* setup PB4-6 for LED  for bits 4-6 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0x70
	orrs r5, r5, r4
	str r5, [r6]
	bx lr

	t7:

	/* setup PB5-7 for LED  for bits 5-6-7 in ODR */
	ldr r6, =GPIOB_ODR
	ldr r5, [r6]
	/* cannot do with movs, so use pc relative */
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r5, r5, r4
	ldr r4, =0xE0
	orrs r5, r5, r4
	str r5, [r6]
	bx lr





	delay:

	ldr r1,=#500000

	init:
	subs r1, r1, #1
	bne init
	bx lr



