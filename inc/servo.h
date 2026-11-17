#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

/* Versión 1: un solo servo (pan) en TIM3 canal 1 */
void servo_init(void);
void servo_pan(int16_t grados);     /* de 0 a 180 */
#endif
