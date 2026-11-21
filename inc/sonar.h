#ifndef SONAR_H
#define SONAR_H
#include <stdint.h>

/* Versión 1 (sencilla): la CPU se queda mirando el pin Echo */
void     sonar_init(void);
uint32_t sonar_medir_mm(void);   /* tarda hasta 60 ms; devuelve 0 si no hay eco */
#endif
