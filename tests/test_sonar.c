/* test_sonar.c — una medida cada 100 ms, impresa en mm por UART */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "uart.h"
#include "sonar.h"

int main(void){
    clock_84mhz();
    systick_init();
    uart_init();
    sonar_init();
    __enable_irq();
    uart_texto("test_sonar (mm)\r\n");
    while (1) {
        sonar_disparar();
        uint32_t t0 = millis();
        while (!sonar_listo() && millis() - t0 < 40u) { }
        uart_num(sonar_listo() ? sonar_mm() : 0u);
        uart_texto("\r\n");
        delay_ms(100);
    }
}
