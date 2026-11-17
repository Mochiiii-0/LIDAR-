#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

/* Calibrar con tests/test_servos.c */
#define SERVO_US_MIN     500u    /* pulso para 0°   */
#define SERVO_US_MAX    2500u    /* pulso para 180° */
#define SERVO_US_CENTRO 1500u    /* pulso para 90°  */

typedef enum { SERVO_PAN, SERVO_TILT } servo_t;

void servo_init(void);
void servo_grados(servo_t s, int16_t g);    /* g de 0 a 180 */
#endif
