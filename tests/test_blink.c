/* test_blink.c — ¿compila, graba y corre? LED LD2 (PA5) + "hola" por UART */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "uart.h"
#include "gpio.h"

int main(void){
    clock_84mhz();
    systick_init();
    uart_init();
    gpio_clock(GPIOA);
    gpio_out(GPIOA, 5u);
    uart_texto("hola desde LIDAR-\r\n");
    while (1) {
        GPIOA->ODR ^= 1u << 5;     /* cambiar el LED */
        delay_ms(250);
    }
}
