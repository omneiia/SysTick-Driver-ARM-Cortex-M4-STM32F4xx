#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_config.h"
#include "SYSTICK_private.h"

void (*MSTK_Callback)(void); // global variable of type pointer to function

u8 MSTK_u8ModeOfInterval;

void MSTK_voidInit (void)
{
	MSTK->CTRL = 0x00002; //
}

// Asynchronous Function which keeps the processor busy until it executes the func
void MSTK_voidSetBusyWait        (u32 Copy_u32Ticks)
{
	// Loading the register by the assigned value
	MSTK->LOAD = Copy_u32Ticks;
	// Enables Counter
	SET_BIT(MSTK->CTRL , 0);
	// Polling
	while((GET_BIT(MSTK->CTRL,16))==0);
	// Stop the timer when it reaches 0
	CLR_BIT(MSTK->CTRL,0);
	// Assigning the value and load by 0
	MSTK -> LOAD = 0U;
	MSTK -> VAL  = 0U; 
	
}

void MSTK_voidSetIntervalSingle  (u32 Copy_u32Ticks , void (*Copy_ptr)(void) )
{
	// Assign the Load register by the given value
	MSTK->LOAD = Copy_u32Ticks ;
	// Select Mode to be Signle
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL ; 
	// points to the ISR to be executed
	MSTK_Callback = Copy_ptr;
	// Enable Systick Exception Request
	SET_BIT(MSTK->CTRL,1);
	// Enable Counter
	SET_BIT(MSTK->CTRL,0);
}

void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr)(void) ) 
{
	// Assign the Load register by the given value
	MSTK->LOAD = Copy_u32Ticks ;
	// Select Mode to be periodic
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL ; 
	// points to the ISR to be executed
	MSTK_Callback = Copy_ptr;
	// Enable Systick Exception Request
	SET_BIT(MSTK->CTRL,1);
	// Enable Counter
	SET_BIT(MSTK->CTRL,0);
}
void MSTK_voidStopInterval       (void)
{
	// Disable the Interrupt
	CLR_BIT(MSTK->CTRL,1);
	// Stops the Counter
	CLR_BIT(MSTK->CTRL,0);
	// Assign the Load and Value registers by 0;
	MSTK -> LOAD = 0U;
	MSTK -> VAL  = 0U;
}
u32  MSTK_u32GetElapsedTime      (void)
{
	// How many ticks counted
	u32 Local_u32ElapsedTime = (MSTK->LOAD)-(MSTK->VAL);
	return Local_u32ElapsedTime;
}
u32  MSTK_u32GetRemainingTime	 (void)
{
	u32 Local_u32RemainingTime = MSTK->VAL;
	return Local_u32RemainingTime;
}
void SysTick_Handler             (void)
{
	MSTK_Callback();
	if(MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		// Stop the counter
		CLR_BIT(MSTK->CTRL,0);
		// Assign the LOAD and VAL Registers by 0
		MSTK -> LOAD = 0U;
		MSTK -> VAL  = 0U;
	}
	// Clear the Interrupt flag to start over again
	CLR_BIT(MSTK->CTRL,16);
}
u8 MSTK_u8CounterFlag(void)
{
	// To get value of the flag
	return (GET_BIT(MSTK->CTRL,16));
}
