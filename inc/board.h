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

/* ---- HC-SR04 ---- */
#define TRIG_PORT     GPIOA
#define TRIG_PIN      8u      /* PA8 = D7, salida digital */
#define ECHO_PORT     GPIOA
#define ECHO_PIN      0u      /* PA0 = A0, AF1 = TIM2_CH1. ¡Con divisor 5 V -> 3.3 V! */
#define ECHO_AF       1u

/* ---- ILI9341 por SPI1 ---- */
#define TFT_SCK_PIN   5u      /* PA5 = D13, AF5 = SPI1_SCK  */
#define TFT_MOSI_PIN  7u      /* PA7 = D11, AF5 = SPI1_MOSI */
#define TFT_SPI_AF    5u
#define TFT_CS_PORT   GPIOB
#define TFT_CS_PIN    0u      /* PB0 = A3 */
#define TFT_DC_PORT   GPIOC
#define TFT_DC_PIN    7u      /* PC7 = D9 */
#define TFT_RST_PORT  GPIOA
#define TFT_RST_PIN   9u      /* PA9 = D8 */

/* ---- Depuración: USART2 por el mismo cable USB ---- */
#define DEBUG_BAUD    115200u

#endif
