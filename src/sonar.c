/* sonar.c — VERSIÓN 1: HC-SR04 "a lo bruto": la CPU espera mirando el pin Echo.
   Funciona, pero mientras espera NO puede hacer nada más. En el avance 7 se mejora con Input Capture. */
#include "sonar.h"
#include "board.h"
#include "gpio.h"

void sonar_init(void){
    gpio_clock(GPIOA);
    gpio_out(TRIG_PORT, TRIG_PIN);                   /* PA8 = salida (Trig) */
    gpio_lo(TRIG_PORT, TRIG_PIN);
    ECHO_PORT->MODER &= ~(3u << (2u * ECHO_PIN));    /* PA0 = ENTRADA (MODER = 00). ¡Con divisor! */

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;              /* TIM2 solo como cronómetro */
    TIM2->PSC = 83u;                                 /* 1 cuenta = 1 us */
    TIM2->ARR = 0xFFFFFFFFu;                         /* 32 bits: casi nunca da la vuelta */
    TIM2->EGR = TIM_EGR_UG;
    TIM2->CR1 |= TIM_CR1_CEN;
}

static int echo_alto(void){                          /* leer el pin Echo: 1 o 0 */
    return (ECHO_PORT->IDR >> ECHO_PIN) & 1u;
}

uint32_t sonar_medir_mm(void){
    gpio_hi(TRIG_PORT, TRIG_PIN);                    /* 1. gritar: Trig en 1 ... */
    uint32_t t0 = TIM2->CNT;
    while (TIM2->CNT - t0 < 12u) { }                 /*    ... durante 12 us */
    gpio_lo(TRIG_PORT, TRIG_PIN);

    t0 = TIM2->CNT;
    while (!echo_alto())                             /* 2. esperar a que Echo suba */
        if (TIM2->CNT - t0 > 30000u) return 0u;      /*    (si en 30 ms no sube: nada) */
    uint32_t sube = TIM2->CNT;                       /* 3. anotar la hora de subida */

    while (echo_alto())                              /* 4. esperar a que Echo baje */
        if (TIM2->CNT - sube > 30000u) return 0u;    /*    (30 ms = más de 5 m: nada) */
    uint32_t ancho = TIM2->CNT - sube;               /* 5. cuánto estuvo en alto, en us */

    return (ancho * 343u) / 2000u;                   /* 6. us -> mm (0.343 mm/us, ida y vuelta) */
}
