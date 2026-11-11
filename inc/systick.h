#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>
void     systick_init(void);   /* interrupción cada 1 ms */
uint32_t millis(void);         /* milisegundos desde el arranque */
void     delay_ms(uint32_t n); /* espera bloqueante: solo para init y tests */
#endif