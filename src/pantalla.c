/* pantalla.c — cómo se ve el LIDAR: dónde va cada cuadrito, la leyenda y los números.
   Sabe de diseño de pantalla; NO sabe de SPI (eso es ili9341.c) ni de servos. */
#include "pantalla.h"
#include "ili9341.h"
#include "color.h"

#define MARCA_PAN   0xFD20u   /* naranja: el número de la izquierda es el pan */
#define MARCA_TILT  0x07FFu   /* cian:    el número del medio es el tilt      */

static int16_t celda_x(int16_t col) { return AREA_X + col  * CELDA_W; }
static int16_t celda_y(int16_t fila){ return AREA_Y + fila * CELDA_H; }

void pantalla_inicio(void){
    tft_init();
    tft_fill(NEGRO);
    tft_rect(AREA_X - 1, AREA_Y - 1, AREA_W + 2, 1, GRIS);           /* marco: arriba    */
    tft_rect(AREA_X - 1, AREA_Y + AREA_H, AREA_W + 2, 1, GRIS);      /*        abajo     */
    tft_rect(AREA_X - 1, AREA_Y - 1, 1, AREA_H + 2, GRIS);           /*        izquierda */
    tft_rect(AREA_X + AREA_W, AREA_Y - 1, 1, AREA_H + 2, GRIS);      /*        derecha   */

    for (int16_t x = 0; x < 300; x++) {                              /* leyenda: la regla de colores */
        uint32_t mm = DIST_CERCA_MM + ((uint32_t)x * (DIST_LEJOS_MM - DIST_CERCA_MM)) / 299u;
        tft_rect(10 + x, 222, 1, 6, color_de_distancia(mm));
    }
    tft_numero(10,  230, DIST_CERCA_MM / 10u, 2, 2, BLANCO, NEGRO);  /* "10"  cm */
    tft_numero(286, 230, DIST_LEJOS_MM / 10u, 3, 2, BLANCO, NEGRO);  /* "150" cm */
    tft_rect(4,   8, 6, 6, MARCA_PAN);
    tft_rect(110, 8, 6, 6, MARCA_TILT);
}

void pantalla_cursor(int16_t fila, int16_t col){
    int16_t x = celda_x(col), y = celda_y(fila);
    tft_rect(x, y, CELDA_W, 1, BLANCO);                  /* arriba    */
    tft_rect(x, y + CELDA_H - 1, CELDA_W, 1, BLANCO);    /* abajo     */
    tft_rect(x, y, 1, CELDA_H, BLANCO);                  /* izquierda */
    tft_rect(x + CELDA_W - 1, y, 1, CELDA_H, BLANCO);    /* derecha   */
}

void pantalla_celda(int16_t fila, int16_t col, uint32_t mm){
    tft_rect(celda_x(col), celda_y(fila), CELDA_W, CELDA_H, color_de_distancia(mm));  /* tapa el cursor */
}

void pantalla_datos(int16_t pan, int16_t tilt, uint32_t mm){
    tft_numero(14,  4, (uint32_t)pan,  3, 3, BLANCO, NEGRO);
    tft_numero(120, 4, (uint32_t)tilt, 3, 3, BLANCO, NEGRO);
    tft_numero(240, 4, mm / 10u,       3, 3, AMARILLO, NEGRO);       /* distancia en cm */
}
