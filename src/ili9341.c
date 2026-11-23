/* ili9341.c — "voy a pintar este rectángulo" + "ahí van los colores" */
#include "ili9341.h"
#include "board.h"
#include "gpio.h"
#include "spi.h"
#include "systick.h"

static void cmd(uint8_t c){
    spi1_fin();                              /* que termine el byte anterior ANTES de mover DC */
    gpio_lo(TFT_DC_PORT, TFT_DC_PIN);        /* DC = 0 -> lo que viene es una ORDEN */
    spi1_tx(c);
    spi1_fin();
    gpio_hi(TFT_DC_PORT, TFT_DC_PIN);        /* DC = 1 -> lo que siga son DATOS */
}

static void dat(uint8_t d){ spi1_tx(d); }

void tft_init(void){
    gpio_clock(GPIOA); gpio_clock(GPIOB); gpio_clock(GPIOC);
    gpio_out(TFT_CS_PORT,  TFT_CS_PIN);
    gpio_out(TFT_DC_PORT,  TFT_DC_PIN);
    gpio_out(TFT_RST_PORT, TFT_RST_PIN);
    spi1_init();

    gpio_lo(TFT_CS_PORT, TFT_CS_PIN);        /* un solo esclavo: queda elegido siempre */
    gpio_lo(TFT_RST_PORT, TFT_RST_PIN); delay_ms(10);
    gpio_hi(TFT_RST_PORT, TFT_RST_PIN); delay_ms(120);

    cmd(0x01); delay_ms(150);                /* SWRESET */
    cmd(0x11); delay_ms(120);                /* SLPOUT: despertar */
    cmd(0x3A); dat(0x55);                    /* COLMOD: 16 bits por píxel (RGB565) */
    cmd(0x36); dat(0x28);                    /* MADCTL: horizontal 320x240, orden BGR */
    cmd(0x29);                               /* DISPON: encender */
}

static void ventana(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
    cmd(0x2A); dat(x0 >> 8); dat(x0 & 0xFF); dat(x1 >> 8); dat(x1 & 0xFF);   /* CASET: columnas */
    cmd(0x2B); dat(y0 >> 8); dat(y0 & 0xFF); dat(y1 >> 8); dat(y1 & 0xFF);   /* PASET: filas */
    cmd(0x2C);                                                                /* RAMWR: ahí van */
}

void tft_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c){
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > TFT_W || y + h > TFT_H) return;
    ventana(x, y, x + w - 1, y + h - 1);
    uint32_t n = (uint32_t)w * h;
    while (n--) { dat(c >> 8); dat(c & 0xFF); }     /* primero el byte alto */
}

void tft_pixel(int16_t x, int16_t y, uint16_t c){ tft_rect(x, y, 1, 1, c); }
void tft_fill(uint16_t c){ tft_rect(0, 0, TFT_W, TFT_H, c); }

/* Dígitos de 3x5 cuadritos: cada número es un dibujo de 15 bits (fila por fila) */
static const uint16_t FONT3x5[10] = {
    0x7B6F, 0x2C97, 0x73E7, 0x73CF, 0x5BC9, 0x79CF, 0x79EF, 0x7249, 0x7BEF, 0x7BCF
};

static void digito(int16_t x, int16_t y, uint8_t d, uint8_t s, uint16_t c, uint16_t f){
    uint16_t m = FONT3x5[d % 10u];
    for (uint8_t fila = 0; fila < 5u; fila++)
        for (uint8_t col = 0; col < 3u; col++) {
            uint8_t bit = 14u - (fila * 3u + col);
            tft_rect(x + col * s, y + fila * s, s, s, ((m >> bit) & 1u) ? c : f);
        }
}

void tft_numero(int16_t x, int16_t y, uint32_t n, uint8_t cifras,
                uint8_t s, uint16_t c, uint16_t f){
    for (int8_t i = (int8_t)cifras - 1; i >= 0; i--) {
        digito(x + i * 4 * s, y, n % 10u, s, c, f);
        n /= 10u;
    }
}
