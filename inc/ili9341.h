#ifndef ILI9341_H
#define ILI9341_H
#include <stdint.h>

#define TFT_W 320
#define TFT_H 240

/* Colores RGB565: rrrrrggg gggbbbbb */
#define NEGRO        0x0000u
#define BLANCO       0xFFFFu
#define GRIS         0x4208u
#define ROJO         0xF800u
#define VERDE        0x07E0u
#define AZUL         0x001Fu
#define AMARILLO     0xFFE0u

void tft_init(void);
void tft_fill(uint16_t c);
void tft_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
void tft_pixel(int16_t x, int16_t y, uint16_t c);
void tft_numero(int16_t x, int16_t y, uint32_t n, uint8_t cifras,
                uint8_t esc, uint16_t c, uint16_t fondo);
#endif
