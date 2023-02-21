#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H



typedef struct 
{
	volatile u32 CTRL ;
	volatile u32 LOAD ;
	volatile u32 VAL  ;
	volatile u32 CALIB;
		
}STK_t;

// Base address of the STK Registers               0xE000E010

#define MSTK (( STK_t *)(0xE000E010))
//#define USART1    ((UART_t*)USART1_BASE_ADDRESS)

#endif
