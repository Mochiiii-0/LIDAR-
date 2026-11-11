/* main.c — AVANCE 1: prender y apagar el LED verde de la placa (LD2 = pin PA5).
   Todavía a 16 MHz (el reloj con el que arranca el chip) y esperando "a lo bruto". */
#include "stm32f4xx.h"            /* los nombres de los registros: RCC, GPIOA, ... */
 
int main(void){
    RCC->AHB1ENR |= (1u << 0);           /* 1. prender el reloj del puerto A (bit 0 = GPIOA) */
    GPIOA->MODER &= ~(3u << (5 * 2));    /* 2. borrar los 2 bits del pin 5 en MODER ... */
    GPIOA->MODER |=  (1u << (5 * 2));    /*    ... y poner 01 = SALIDA */
 
    while (1) {                          /* 3. para siempre: */
        GPIOA->ODR ^= (1u << 5);         /*    cambiar el LED (^ = si estaba en 1 pasa a 0 y al revés) */
        for (volatile uint32_t i = 0; i < 400000u; i++) { }   /* perder tiempo para que se vea */
    }
}
