/* escaneo.c — el "GPS" del barrido: qué fila, qué columna y qué ángulos tocan ahora.
   No toca registros: es pura lógica y se prueba sin mover nada (tests/test_escaneo.c). */
#include "escaneo.h"

static void calcular_angulos(punto_t *p){
    p->pan  = PAN_MIN  + p->col  * PAN_PASO;    /* col 0 = izquierda (si sale espejo: PAN_MAX - ...) */
    p->tilt = TILT_MIN + p->fila * TILT_PASO;   /* invertido: asi quedo montado nuestro servo tilt */
}

void escaneo_reiniciar(punto_t *p){
    p->fila = 0;
    p->col  = 0;
    p->nueva_fila = 1;                          /* el primer punto también necesita esperar */
    calcular_angulos(p);
}

int escaneo_siguiente(punto_t *p){
    int16_t dir = (p->fila % 2 == 0) ? 1 : -1;  /* filas pares -> derecha, impares <- izquierda */
    int16_t c   = p->col + dir;
    p->nueva_fila = 0;

    if (c < 0 || c >= COLUMNAS) {               /* se acabó la fila */
        p->fila++;
        p->nueva_fila = 1;
        if (p->fila >= FILAS) {                 /* se acabó la imagen: volver a empezar */
            escaneo_reiniciar(p);
            return 1;
        }
        /* la columna NO cambia: la fila nueva arranca justo debajo (zig-zag) */
    } else {
        p->col = c;
    }
    calcular_angulos(p);
    return 0;
}
