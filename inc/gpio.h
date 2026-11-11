#ifndef GPIO_H
#define GPIO_H
#include "stm32f4xx.h"
 
void gpio_clock(GPIO_TypeDef *g);                              /* prende el reloj del puerto */
void gpio_out(GPIO_TypeDef *g, uint32_t pin);                  /* MODER = 01 */
void gpio_af(GPIO_TypeDef *g, uint32_t pin, uint32_t af);      /* MODER = 10 + AFR */
 
static inline void gpio_hi(GPIO_TypeDef *g, uint32_t pin){ g->BSRR = 1u << pin; }
static inline void gpio_lo(GPIO_TypeDef *g, uint32_t pin){ g->BSRR = 1u << (pin + 16u); }
#endif