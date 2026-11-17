/* servo.c — VERSIÓN 1: UN servo (pan) con el PWM de TIM3 canal 1 (guía G08) */
#include "servo.h"
#include "board.h"
#include "gpio.h"

void servo_init(void){
    gpio_clock(SERVO_PORT);
    gpio_af(SERVO_PORT, PAN_PIN, SERVO_AF);      /* PB4 se lo prestamos a TIM3_CH1 (AF2) */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;          /* prender el reloj de TIM3 */

    TIM3->PSC   = 83u;                           /* 84 MHz / 84 = 1 MHz -> 1 cuenta = 1 us */
    TIM3->ARR   = 19999u;                        /* 20 000 us = 20 ms: el periodo que pide el SG90 */
    TIM3->CCMR1 = (6u << TIM_CCMR1_OC1M_Pos);    /* canal 1 en modo PWM 1 */
    TIM3->CCER |= TIM_CCER_CC1E;                 /* sacar la señal por el pin */
    TIM3->CCR1  = 1500u;                         /* pulso de 1500 us = 90° (el centro) */
    TIM3->CR1  |= TIM_CR1_CEN;                   /* ¡a contar! desde aquí el pulso sale solo */
}

void servo_pan(int16_t grados){
    if (grados < 0)   grados = 0;                /* no dejar pasar valores locos */
    if (grados > 180) grados = 180;
    TIM3->CCR1 = 500u + ((uint32_t)grados * 2000u) / 180u;   /* 0° = 500 us ... 180° = 2500 us */
}
