/* board.h — el "mapa de la casa": qué pin hace qué.
   Si cambian un cable, cambian SOLO este archivo. No tiene .c: solo son nombres. */
#ifndef BOARD_H
#define BOARD_H
#include "stm32f4xx.h"

/* ---- Servos SG90: TIM3, un canal para cada uno ---- */
#define SERVO_PORT    GPIOB
#define PAN_PIN       4u      /* PB4 = D5, AF2 = TIM3_CH1 (izquierda-derecha) */
#define TILT_PIN      5u      /* PB5 = D4, AF2 = TIM3_CH2 (arriba-abajo)      */
#define SERVO_AF      2u

/* ---- Depuración: USART2 por el mismo cable USB ---- */
#define DEBUG_BAUD    115200u

#endif
