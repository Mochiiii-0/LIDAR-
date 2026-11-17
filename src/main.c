/* main.c — AVANCE 4: mover UN servo (pan) a 0°, 90° y 180°. */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "uart.h"
#include "servo.h"

int main(void){
    clock_84mhz();
    systick_init();
    uart_init();
    servo_init();

    const int16_t angulos[] = { 0, 90, 180, 90 };
    uint32_t i = 0;
    while (1) {
        servo_pan(angulos[i]);           /* cambia TIM3->CCR1 */
        uart_texto("pan = ");
        uart_num((uint32_t)angulos[i]);
        uart_texto("\r\n");
        i = (i + 1u) % 4u;               /* 0, 1, 2, 3, 0, 1, ... */
        delay_ms(1000);
    }
}
