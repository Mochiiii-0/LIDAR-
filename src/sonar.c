/* sonar.c — HC-SR04: gritar en Trig y cronometrar Echo con Input Capture de TIM2 */
#include "sonar.h"
#include "board.h"
#include "gpio.h"

typedef enum { ESPERA_SUBIDA, ESPERA_BAJADA, LISTO } eco_t;
static volatile eco_t    eco = LISTO;
static volatile uint32_t t_sube, t_baja;

void sonar_init(void){
    gpio_clock(GPIOA);
    gpio_out(TRIG_PORT, TRIG_PIN);
    gpio_lo(TRIG_PORT, TRIG_PIN);
    gpio_af(ECHO_PORT, ECHO_PIN, ECHO_AF);          /* PA0 se lo presta a TIM2_CH1 */

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC   = 83u;                              /* 1 MHz -> 1 cuenta = 1 us */
    TIM2->ARR   = 0xFFFFFFFFu;                      /* 32 bits: da la vuelta cada ~71 min */
    TIM2->CCMR1 = (TIM2->CCMR1 & ~0xFFu)
                | (1u << TIM_CCMR1_CC1S_Pos)        /* CC1S = 01: el canal 1 es ENTRADA (TI1) */
                | (3u << TIM_CCMR1_IC1F_Pos);       /* filtro: ignora ruido de menos de 8 tics */
    TIM2->CCER |= TIM_CCER_CC1P | TIM_CCER_CC1NP    /* capturar en AMBOS flancos */
                | TIM_CCER_CC1E;                    /* habilitar la captura */
    TIM2->DIER |= TIM_DIER_CC1IE;                   /* avisar con interrupción en cada captura */
    TIM2->EGR   = TIM_EGR_UG;
    NVIC_SetPriority(TIM2_IRQn, 1);
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1  |= TIM_CR1_CEN;
}

static void espera_us(uint32_t us){
    uint32_t t0 = TIM2->CNT;                        /* TIM2 también sirve de cronómetro */
    while (TIM2->CNT - t0 < us) { }
}

void sonar_disparar(void){
    eco = ESPERA_SUBIDA;                            /* "listo para anotar el primer flanco" */
    gpio_hi(TRIG_PORT, TRIG_PIN);
    espera_us(12u);                                 /* el HC-SR04 pide >= 10 us */
    gpio_lo(TRIG_PORT, TRIG_PIN);
}

int sonar_listo(void){ return eco == LISTO; }

uint32_t sonar_mm(void){
    uint32_t ancho = t_baja - t_sube;               /* us que Echo estuvo en alto */
    uint32_t mm = (ancho * 343u) / 2000u;           /* 0.343 mm/us, ida y vuelta -> /2 */
    if (mm < 20u || mm > 4000u) return 0u;          /* fuera de rango: "no vi nada" */
    return mm;
}

void TIM2_IRQHandler(void){
    if (TIM2->SR & TIM_SR_CC1IF){
        uint32_t c = TIM2->CCR1;                    /* leer CCR1 también baja CC1IF */
        if (eco == ESPERA_SUBIDA)      { t_sube = c; eco = ESPERA_BAJADA; }
        else if (eco == ESPERA_BAJADA) { t_baja = c; eco = LISTO; }
    }
    if (TIM2->SR & TIM_SR_CC1OF) TIM2->SR = ~TIM_SR_CC1OF;   /* se perdió un flanco: limpiar */
}
