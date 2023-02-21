#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H



#define     MSTK_SRC_AHB            0U
#define     MSTK_SRC_AHB_8         	1U

#define     MSTK_SINGLE_INTERVAL    0U
#define     MSTK_PERIOD_INTERVAL    1U

void MSTK_voidInit (void);
void MSTK_voidSetBusyWait        (u32 Copy_u32Ticks);
// Function given number of ticks and function to callback
void MSTK_voidSetIntervalSingle  (u32 Copy_u32Ticks , void (*Copy_ptr)(void) ); // Asynchronous Function After Finishing will alert you, Will be given function to call when it finishes execution
void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr)(void) ); // Synchronous Function
void MSTK_voidStopInterval       (void);
u32  MSTK_u32GetElapsedTime      (void);
u32  MSTK_u32GetRemainingTime	 (void);

#endif
