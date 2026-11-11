/* main.c — AVANCE 3: la placa le habla al PC por el cable USB (USART2).
   Y el LED ya no se maneja con registros sueltos sino con las funciones de gpio.c */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "gpio.h"
#include "uart.h"
 
int main(void){
    clock_84mhz();
    systick_init();
    uart_init();                         /* PA2/PA3 en AF7, 115 200 baudios */
 
    gpio_clock(GPIOA);                   /* LED: reloj del puerto A ... */
    gpio_out(GPIOA, 5u);                 /* ... y PA5 como salida */
 
    uint32_t n = 0;
    while (1) {
        uart_texto("Hola LIDAR ");       /* se ve en Serial Monitor a 115200 */
        uart_num(n++);
        uart_texto("\r\n");
        gpio_hi(GPIOA, 5u); delay_ms(100);   /* LED prendido 0.1 s */
        gpio_lo(GPIOA, 5u); delay_ms(900);   /* apagado 0.9 s */
    }
}