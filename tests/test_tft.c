/* test_tft.c — colores, rectángulos y un contador en la pantalla */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "ili9341.h"

int main(void){
    clock_84mhz();
    systick_init();
    tft_init();
    tft_fill(ROJO);  delay_ms(500);     /* si sale azul: quitar el bit BGR en MADCTL */
    tft_fill(VERDE); delay_ms(500);
    tft_fill(AZUL);  delay_ms(500);
    tft_fill(NEGRO);
    tft_rect(10, 10, 100, 60, AMARILLO);
    tft_rect(200, 150, 10, 12, BLANCO);  /* del tamaño de un cuadrito del LIDAR */
    uint32_t n = 0;
    while (1) {
        tft_numero(200, 200, n++, 4, 4, VERDE, NEGRO);
        delay_ms(100);
    }
}
