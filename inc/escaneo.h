#ifndef ESCANEO_H
#define ESCANEO_H
#include <stdint.h>

#define PAN_MIN     30    /* grados: borde izquierdo de la imagen */
#define PAN_MAX    150    /* grados: borde derecho */
#define PAN_PASO     4
#define TILT_MIN    60    /* grados: fila de ABAJO */
#define TILT_MAX   120    /* grados: fila de ARRIBA */
#define TILT_PASO    4

#define COLUMNAS  ((PAN_MAX  - PAN_MIN)  / PAN_PASO  + 1)   /* 31 */
#define FILAS     ((TILT_MAX - TILT_MIN) / TILT_PASO + 1)   /* 16 */

typedef struct {
    int16_t fila, col;     /* dónde va en la imagen (fila 0 = arriba, col 0 = izquierda) */
    int16_t pan, tilt;     /* ángulos que se le mandan a los servos */
    uint8_t nueva_fila;    /* 1 si acaba de cambiar de fila: el tilt se movió */
} punto_t;

void escaneo_reiniciar(punto_t *p);
int  escaneo_siguiente(punto_t *p);   /* avanza un punto; devuelve 1 si terminó la imagen */
#endif
