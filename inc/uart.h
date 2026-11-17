#ifndef UART_H
#define UART_H
#include <stdint.h>
void uart_init(void);
void uart_char(char c);
void uart_texto(const char *s);
void uart_num(uint32_t n);
#endif
