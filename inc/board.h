/* board.h — el "mapa de la casa": qué pin hace qué.
   Si cambian un cable, cambian SOLO este archivo. No tiene .c: solo son nombres. */
#ifndef BOARD_H
#define BOARD_H
#include "stm32f4xx.h"
 
/* ---- Depuración: USART2 por el mismo cable USB ---- */
#define DEBUG_BAUD    115200u
 
#endif