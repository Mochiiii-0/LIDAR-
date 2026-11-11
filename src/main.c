/* main.c — AVANCE 2: el mismo LED, pero con el reloj a 84 MHz y esperas EXACTAS de 500 ms. */
#include "stm32f4xx.h"
#include "clock.h"
#include "systick.h"
 
int main(void){
    clock_84mhz();                       /* 1. subir la CPU de 16 MHz a 84 MHz (PLL) */
    systick_init();                      /* 2. SysTick: millis() sube 1 cada milisegundo */
 
    RCC->AHB1ENR |= (1u << 0);           /* 3. el LED en PA5, igual que en el avance 1 */
    GPIOA->MODER &= ~(3u << (5 * 2));
    GPIOA->MODER |=  (1u << (5 * 2));
 
    while (1) {
        GPIOA->ODR ^= (1u << 5);
        delay_ms(500);                   /* 4. ahora sí: medio segundo exacto (1 parpadeo por segundo) */
    }
}