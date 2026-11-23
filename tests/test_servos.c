/* test_servos.c — mueve primero el PAN y luego el TILT. Sirve para calibrar */
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
    uart_texto("test_servos\r\n");
    while (1) {
        servo_grados(SERVO_TILT, 90);
        for (int16_t g = 0; g <= 180; g++)  { servo_grados(SERVO_PAN, g); delay_ms(15); }
        for (int16_t g = 180; g >= 0; g--)  { servo_grados(SERVO_PAN, g); delay_ms(15); }
        uart_texto("pan listo\r\n");
        servo_grados(SERVO_PAN, 90);
        for (int16_t g = 60; g <= 120; g++) { servo_grados(SERVO_TILT, g); delay_ms(25); }
        for (int16_t g = 120; g >= 60; g--) { servo_grados(SERVO_TILT, g); delay_ms(25); }
        uart_texto("tilt listo\r\n");
    }
}
