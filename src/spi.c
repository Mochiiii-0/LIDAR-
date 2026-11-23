/* spi.c — SPI1 como maestro, solo transmite (la pantalla no necesita contestar) */
#include "spi.h"
#include "board.h"
#include "gpio.h"

void spi1_init(void){
    gpio_clock(GPIOA);
    gpio_af(GPIOA, TFT_SCK_PIN,  TFT_SPI_AF);
    gpio_af(GPIOA, TFT_MOSI_PIN, TFT_SPI_AF);
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 = SPI_CR1_MSTR                 /* somos el jefe del bus */
              | SPI_CR1_SSM | SPI_CR1_SSI    /* el CS lo manejamos nosotros por GPIO */
              | (2u << SPI_CR1_BR_Pos);      /* 84 MHz / 8 = 10.5 MHz; CPOL = CPHA = 0 (modo 0) */
    SPI1->CR1 |= SPI_CR1_SPE;                /* encender */
}

void spi1_tx(uint8_t b){
    while (!(SPI1->SR & SPI_SR_TXE)) { }     /* esperar a que haya puesto en la fila */
    *(volatile uint8_t *)&SPI1->DR = b;      /* escribir 8 bits, no 16 */
}

void spi1_fin(void){
    while (!(SPI1->SR & SPI_SR_TXE)) { }     /* la fila quedó vacía ... */
    while (SPI1->SR & SPI_SR_BSY)    { }     /* ... y el último bit ya salió por MOSI */
}
