/* main.c — la jefa: coordina el barrido punto por punto con una máquina de estados.
   No toca registros: solo llama funciones de los demás archivos. */
#include "board.h"
#include "clock.h"
#include "systick.h"
#include "uart.h"
#include "servo.h"
#include "sonar.h"
#include "escaneo.h"
#include "pantalla.h"
#include "ili9341.h"

#define T_ASENTAR_MS       40u   /* paso de pan (4°): llegar y dejar de temblar */
#define T_ASENTAR_FILA_MS 250u   /* cambio de fila: se movió el tilt, esperar más */
#define T_ENTRE_DISP       60u   /* el HC-SR04 pide >= 60 ms entre disparos */
#define T_MAX_ECO_MS       40u   /* si en 40 ms no terminó el eco: "no hay nada" */
#define T_PAUSA_FIN_MS   1000u   /* al terminar la imagen: 1 s en negro antes de empezar otra */

typedef enum { MOVER, ASENTAR, DISPARAR, ESPERAR_ECO, PINTAR, PAUSA_FIN } estado_t;

static void enviar_pc(const punto_t *p, uint32_t mm){      /* "fila,col,mm" por UART */
    uart_num((uint32_t)p->fila); uart_char(',');
    uart_num((uint32_t)p->col);  uart_char(',');
    uart_num(mm);                uart_texto("\r\n");
}

int main(void){
    clock_84mhz();
    systick_init();
    uart_init();
    servo_init();
    sonar_init();
    pantalla_inicio();
    __enable_irq();

    punto_t  p;
    estado_t estado = MOVER;
    uint32_t t = 0, espera = 0, ultimo_disparo = 0, mm = 0;
    escaneo_reiniciar(&p);

    while (1) {
        switch (estado) {
        case MOVER:
            servo_grados(SERVO_PAN,  p.pan);
            servo_grados(SERVO_TILT, p.tilt);
            pantalla_cursor(p.fila, p.col);
            espera = p.nueva_fila ? T_ASENTAR_FILA_MS : T_ASENTAR_MS;
            t = millis();
            estado = ASENTAR;
            break;

        case ASENTAR:
            if (millis() - t >= espera && millis() - ultimo_disparo >= T_ENTRE_DISP)
                estado = DISPARAR;
            break;

        case DISPARAR:
            sonar_disparar();
            ultimo_disparo = t = millis();
            estado = ESPERAR_ECO;
            break;

        case ESPERAR_ECO:
            if (sonar_listo())                     { mm = sonar_mm(); estado = PINTAR; }
            else if (millis() - t >= T_MAX_ECO_MS) { mm = 0u;         estado = PINTAR; }
            break;

        case PINTAR:
            pantalla_celda(p.fila, p.col, mm);
            pantalla_datos(p.pan, p.tilt, mm);
            enviar_pc(&p, mm);
            if (escaneo_siguiente(&p)) {                       /* imagen completa: */
                uart_texto("FIN\r\n");
                tft_rect(AREA_X, AREA_Y, AREA_W, AREA_H, NEGRO);  /* borrar la imagen */
                t = millis();
                estado = PAUSA_FIN;                            /* esperar 1 s en negro */
            } else {
                estado = MOVER;
            }
            break;

        case PAUSA_FIN:                                        /* igual que ASENTAR: sin bloquear */
            if (millis() - t >= T_PAUSA_FIN_MS) estado = MOVER;   /* p ya volvió a fila 0, col 0 */
            break;
        }
    }
}
