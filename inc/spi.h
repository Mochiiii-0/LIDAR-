#ifndef SPI_H
#define SPI_H
#include <stdint.h>
void spi1_init(void);
void spi1_tx(uint8_t b);   /* pone un byte en la fila de salida */
void spi1_fin(void);       /* espera a que el último bit haya salido del todo */
#endif
