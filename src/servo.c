/* servo.c — dos SG90 con UN timer (TIM3): mismo periodo, un canal para cada uno */
#include "servo.h"
#include "board.h"
#include "gpio.h"

void servo_init(void){
    gpio_clock(SERVO_PORT);
    gpio_af(SERVO_PORT, PAN_PIN,  SERVO_AF);    /* PB4 se lo presta a TIM3_CH1 */
    gpio_af(SERVO_PORT, TILT_PIN, SERVO_AF);    /* PB5 se lo presta a TIM3_CH2 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;         /* prender el reloj de TIM3 */

    TIM3->PSC   = 83u;                          /* 84 MHz / 84 = 1 MHz -> 1 cuenta = 1 us */
    TIM3->ARR   = 19999u;                       /* 20 000 cuentas = 20 ms -> 50 Hz (para los dos) */
    TIM3->CCMR1 = (6u << TIM_CCMR1_OC1M_Pos) | TIM_CCMR1_OC1PE     /* canal 1: PWM 1 + precarga */
                | (6u << TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC2PE;    /* canal 2: PWM 1 + precarga */
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;                   /* conectar los dos canales a sus pines */
    TIM3->CCR1  = SERVO_US_CENTRO;              /* pan  a 90° */
    TIM3->CCR2  = SERVO_US_CENTRO;              /* tilt a 90° */
    TIM3->CR1  |= TIM_CR1_ARPE;
    TIM3->EGR   = TIM_EGR_UG;                   /* cargar PSC, ARR y CCR ya mismo */
    TIM3->CR1  |= TIM_CR1_CEN;                  /* ¡a contar! desde aquí los pulsos salen solos */
}

void servo_grados(servo_t s, int16_t g){
    if (g < 0)   g = 0;
    if (g > 180) g = 180;
    uint32_t us = SERVO_US_MIN + ((uint32_t)g * (SERVO_US_MAX - SERVO_US_MIN)) / 180u;
    if (s == SERVO_PAN) TIM3->CCR1 = us;        /* cada servo tiene su propio CCR */
    else                TIM3->CCR2 = us;
}
