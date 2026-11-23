#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>

#define DIST_CERCA_MM  100u    /* a esta distancia o menos: ROJO  */
#define DIST_LEJOS_MM 1500u    /* a esta distancia o más:   AZUL  */

uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b);
uint16_t color_de_distancia(uint32_t mm);   /* 0 mm (sin eco) -> negro */
#endif
