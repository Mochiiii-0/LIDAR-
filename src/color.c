/* color.c — traduce milímetros a un color del mapa de calor.
   Cerca = rojo -> amarillo -> verde -> cian -> azul = lejos. Sin eco = negro.
   No toca registros: es pura matemática. */
#include "color.h"

uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b){
    return (uint16_t)(((r & 0xF8u) << 8) | ((g & 0xFCu) << 3) | (b >> 3));
}

uint16_t color_de_distancia(uint32_t mm){
    if (mm == 0u) return 0x0000u;                       /* sin eco: negro */
    if (mm < DIST_CERCA_MM) mm = DIST_CERCA_MM;         /* recortar a la regla */
    if (mm > DIST_LEJOS_MM) mm = DIST_LEJOS_MM;
    uint32_t t = ((mm - DIST_CERCA_MM) * 1023u) / (DIST_LEJOS_MM - DIST_CERCA_MM);   /* 0..1023 */
    uint8_t  u = (uint8_t)(t & 0xFFu);                  /* avance dentro del tramo: 0..255 */
    switch (t >> 8) {                                   /* ¿en cuál de los 4 tramos cae? */
    case 0:  return rgb565(255, u, 0);                  /* rojo     -> amarillo */
    case 1:  return rgb565(255 - u, 255, 0);            /* amarillo -> verde    */
    case 2:  return rgb565(0, 255, u);                  /* verde    -> cian     */
    default: return rgb565(0, 255 - u, 255);            /* cian     -> azul     */
    }
}
