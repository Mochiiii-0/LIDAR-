#ifndef SONAR_H
#define SONAR_H
#include <stdint.h>
void     sonar_init(void);
void     sonar_disparar(void);  /* pulso de 12 us en Trig; no bloquea */
int      sonar_listo(void);     /* 1 cuando ya llegaron los dos flancos del eco */
uint32_t sonar_mm(void);        /* distancia en mm, 0 si está fuera de rango */
#endif
