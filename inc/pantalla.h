#ifndef PANTALLA_H
#define PANTALLA_H
#include <stdint.h>
#include "escaneo.h"

#define AREA_X    5                       /* dónde empieza la imagen en la pantalla */
#define AREA_Y   24
#define AREA_W  310
#define AREA_H  192
#define CELDA_W (AREA_W / COLUMNAS)        /* 310 / 31 = 10 px */
#define CELDA_H (AREA_H / FILAS)           /* 192 / 16 = 12 px */

void pantalla_inicio(void);                                  /* tft_init + marco + leyenda */
void pantalla_cursor(int16_t fila, int16_t col);             /* marco blanco: "estoy midiendo aquí" */
void pantalla_celda(int16_t fila, int16_t col, uint32_t mm); /* cuadrito del color de la distancia */
void pantalla_datos(int16_t pan, int16_t tilt, uint32_t mm); /* números de arriba */
#endif
