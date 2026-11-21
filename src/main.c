/* main.c — AVANCE 7: el mismo sensor, ahora con Input Capture + interrupción (TIM2).
   El timer anota las horas solito; la CPU solo pregunta "¿ya está?". */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "uart.h"
#include "sonar.h"

int main(void){
    clock_84mhz();
    systick_init();
    uart_init();
    sonar_init();                        /* TIM2 CH1 en captura + NVIC IRQ 28 */
    __enable_irq();                      /* permitir interrupciones */

    while (1) {
        sonar_disparar();                /* grita y regresa enseguida */
        uint32_t t0 = millis();
        while (!sonar_listo() && millis() - t0 < 40u) {
            /* aquí la CPU podría hacer otras cosas: las horas las anota la interrupción */
        }
        uart_num(sonar_listo() ? sonar_mm() : 0u);   /* 0 = no llegó eco en 40 ms */
        uart_texto(" mm\r\n");
        delay_ms(100);
    }
}
