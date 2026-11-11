/* clock.c — sube la CPU de 16 MHz a 84 MHz.
   Si ya tienen el clock_config() de los laboratorios, pueden usar ese y borrar este. */
#include "clock.h"
#include "stm32f4xx.h"
 
void clock_84mhz(void){
    RCC->CR |= RCC_CR_HSION;                         /* oscilador interno de 16 MHz */
    while (!(RCC->CR & RCC_CR_HSIRDY)) { }
 
    FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN
               | FLASH_ACR_LATENCY_2WS;              /* a 84 MHz la Flash necesita 2 esperas */
 
    RCC->PLLCFGR = (16u  << RCC_PLLCFGR_PLLM_Pos)    /* 16 MHz / 16  = 1 MHz   */
                 | (336u << RCC_PLLCFGR_PLLN_Pos)    /*  1 MHz * 336 = 336 MHz */
                 | (1u   << RCC_PLLCFGR_PLLP_Pos)    /* P = 4 -> 336 / 4 = 84 MHz */
                 | (7u   << RCC_PLLCFGR_PLLQ_Pos);   /* fuente = HSI (PLLSRC = 0) */
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY)) { }
 
    RCC->CFGR = RCC_CFGR_HPRE_DIV1                   /* AHB  = 84 MHz */
              | RCC_CFGR_PPRE1_DIV2                  /* APB1 = 42 MHz (timers de APB1 ven 84) */
              | RCC_CFGR_PPRE2_DIV1                  /* APB2 = 84 MHz */
              | RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) { }
 
    SystemCoreClock = 84000000u;
}