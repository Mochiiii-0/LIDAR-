/* test_escaneo.c — imprime el recorrido completo SIN mover nada.
   Debe salir 496 líneas "fila,col,pan,tilt,nueva_fila" en zig-zag y luego FIN. */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "uart.h"
#include "escaneo.h"

int main(void){
    clock_84mhz();
    systick_init();
    uart_init();
    punto_t p;
    escaneo_reiniciar(&p);
    uint32_t n = 0;
    do {
        uart_num((uint32_t)p.fila); uart_char(',');
        uart_num((uint32_t)p.col);  uart_char(',');
        uart_num((uint32_t)p.pan);  uart_char(',');
        uart_num((uint32_t)p.tilt); uart_char(',');
        uart_num(p.nueva_fila);     uart_texto("\r\n");
        n++;
    } while (!escaneo_siguiente(&p));
    uart_texto("FIN, puntos = "); uart_num(n); uart_texto("\r\n");
    while (1) { }
}
