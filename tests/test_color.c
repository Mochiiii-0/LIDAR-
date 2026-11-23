/* test_color.c — pinta la paleta completa: ¿se ve rojo cerca y azul lejos? */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "ili9341.h"
#include "color.h"

int main(void){
    clock_84mhz();
    systick_init();
    tft_init();
    tft_fill(NEGRO);
    for (int16_t x = 0; x < 320; x++) {              /* de 0 a 2000 mm de izquierda a derecha */
        uint32_t mm = ((uint32_t)x * 2000u) / 319u;
        tft_rect(x, 60, 1, 120, color_de_distancia(mm));
    }
    tft_numero(4, 200, DIST_CERCA_MM, 4, 3, BLANCO, NEGRO);
    tft_numero(250, 200, DIST_LEJOS_MM, 4, 3, BLANCO, NEGRO);
    while (1) { }
}
