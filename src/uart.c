/* uart.c — imprimir al PC por el cable USB (USART2, guía G09) */
#include "uart.h"
#include "board.h"
#include "gpio.h"
 
void uart_init(void){
    gpio_clock(GPIOA);
    gpio_af(GPIOA, 2u, 7u);                      /* PA2 = TX */
    gpio_af(GPIOA, 3u, 7u);                      /* PA3 = RX */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = 42000000u / DEBUG_BAUD;        /* 42 MHz / 115 200 = 364 (error 0.16 %) */
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}
 
void uart_char(char c){
    while (!(USART2->SR & USART_SR_TXE)) { }
    USART2->DR = (uint8_t)c;
}
 
void uart_texto(const char *s){ while (*s) uart_char(*s++); }
 
void uart_num(uint32_t n){                       /* sin printf: dígitos al revés y luego al derecho */
    char b[10]; int i = 0;
    do { b[i++] = (char)('0' + n % 10u); n /= 10u; } while (n);
    while (i) uart_char(b[--i]);
}