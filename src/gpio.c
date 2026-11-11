gpio.c
nuevo en este escalón
📋 Copiar este archivo
/* gpio.c — las tres cosas que siempre hacemos con un pin (guía G05) */
#include "gpio.h"
 
void gpio_clock(GPIO_TypeDef *g){
    uint32_t n = ((uint32_t)g - GPIOA_BASE) / 0x400u;   /* GPIOA = 0, GPIOB = 1, GPIOC = 2 ... */
    RCC->AHB1ENR |= 1u << n;
}
 
void gpio_out(GPIO_TypeDef *g, uint32_t pin){
    g->MODER = (g->MODER & ~(3u << (2u * pin))) | (1u << (2u * pin));
}
 
void gpio_af(GPIO_TypeDef *g, uint32_t pin, uint32_t af){
    g->MODER   = (g->MODER & ~(3u << (2u * pin))) | (2u << (2u * pin));
    g->OSPEEDR |= 3u << (2u * pin);                      /* velocidad alta: SPI la necesita */
    uint32_t r = pin >> 3, s = 4u * (pin & 7u);          /* AFR[0] pines 0-7, AFR[1] pines 8-15 */
    g->AFR[r]  = (g->AFR[r] & ~(0xFu << s)) | (af << s);
}