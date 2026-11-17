/* main.c — AVANCE 5: los DOS servos (pan y tilt) con el mismo timer TIM3. */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "uart.h"
#include "servo.h"

int main(void){
    clock_84mhz();
    systick_init();
    uart_init();
    servo_init();                        /* CH1 = pan (PB4), CH2 = tilt (PB5) */

    while (1) {
        for (int16_t g = 30; g <= 150; g += 10) {   /* pan de izquierda a derecha */
            servo_grados(SERVO_PAN, g);
            delay_ms(150);
        }
        servo_grados(SERVO_TILT, 60);  delay_ms(500);   /* tilt: abajo ... */
        servo_grados(SERVO_TILT, 120); delay_ms(500);   /* ... arriba ... */
        servo_grados(SERVO_TILT, 90);  delay_ms(500);   /* ... al centro */
        servo_grados(SERVO_PAN, 30);   delay_ms(500);
        uart_texto("vuelta lista\r\n");
    }
}
