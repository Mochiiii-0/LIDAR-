/* systick.c — el reloj de pared del proyecto: suma 1 cada milisegundo */
#include "systick.h"
#include "stm32f4xx.h"
 
static volatile uint32_t ms_ticks = 0;     /* volatile: la cambia una ISR */
 
void SysTick_Handler(void){ ms_ticks++; }
 
void systick_init(void){
    SysTick->LOAD = 84000u - 1u;           /* 84 MHz / 84 000 = 1 kHz -> 1 ms */
    SysTick->VAL  = 0u;
    SysTick->CTRL = 7u;                    /* CLKSOURCE = HCLK, TICKINT = 1, ENABLE = 1 */
}
 
uint32_t millis(void){ return ms_ticks; }
 
void delay_ms(uint32_t n){
    uint32_t t0 = ms_ticks;
    while (ms_ticks - t0 < n) { }
}