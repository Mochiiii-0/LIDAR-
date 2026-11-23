# Escáner ultrasónico pan–tilt con STM32F401RE

**Proyecto final — Microprocesadores e Interfaces (MPEI)**  
Escuela Colombiana de Ingeniería Julio Garavito · 2026-II

**Integrantes:** Iván Carpentier y Sara Sofía Otero

## Descripción

Este proyecto implementa un **sistema de barrido ultrasónico de bajo costo** sobre una tarjeta **NUCLEO-F401RE (ARM Cortex-M4)**. Dos servomotores SG90 posicionan el sensor HC-SR04 en los ejes horizontal (**pan**) y vertical (**tilt**). En cada posición, el microcontrolador mide la distancia a partir del tiempo del pulso ECHO y representa la lectura como una celda coloreada en una pantalla TFT ILI9341.

El firmware está desarrollado en **C bare-metal**, con acceso a registros mediante encabezados CMSIS, sin HAL/LL. La compilación se realiza con GNU Arm Embedded Toolchain y Makefile.

> **Nota de terminología:** aunque el proyecto se denomina informalmente «LiDAR», la medición se realiza con **ultrasonido**, no con un sensor LiDAR óptico. La pantalla muestra un **mapa angular 2D de distancias** obtenido mediante un movimiento en dos ejes; no una nube de puntos cartesiana 3D completa.

## Funcionalidades

- Barrido pan–tilt con **dos SG90**, controlados mediante PWM de hardware con TIM3.
- Medición de distancia con **HC-SR04**, usando captura de entrada de TIM2 para el pulso ECHO.
- Visualización de una **matriz de 31 × 16 posiciones (496 mediciones por barrido)** en la TFT ILI9341, con colores según la distancia.
- Recorrido **serpenteante**, alternando la dirección horizontal entre filas.
- Salida por **USART2** para depuración y seguimiento de las lecturas.
- Control de barrido mediante una máquina de estados, con esperas temporizadas y manejo de timeout del eco.

## Componentes principales

| Componente | Función |
|---|---|
| NUCLEO-F401RE / STM32F401RE | Procesamiento y control (ARM Cortex-M4) |
| HC-SR04 | Medición ultrasónica de distancia |
| 2 × SG90 | Movimiento horizontal (PAN) y vertical (TILT) |
| TFT ILI9341 | Visualización de resultados mediante SPI |
| Fuente externa de 5 V | Alimentación de los servomotores |
| Divisor resistivo en ECHO | Adaptación de nivel lógico de 5 V a aproximadamente 3,3 V |

### Conexiones del firmware

| Señal | STM32F401RE | Periférico / función |
|---|---|---|
| Servo PAN | PB4 | TIM3_CH1 / PWM |
| Servo TILT | PB5 | TIM3_CH2 / PWM |
| HC-SR04 TRIG | PA8 | GPIO de salida |
| HC-SR04 ECHO | PA0 | TIM2_CH1 / Input Capture |
| TFT SCK | PA5 | SPI1_SCK |
| TFT MOSI | PA7 | SPI1_MOSI |
| TFT CS | PB0 | GPIO |
| TFT DC | PC7 | GPIO |
| TFT RESET | PA9 | GPIO |
| UART TX / RX | PA2 / PA3 | USART2 |

**Alimentación:** los servos se alimentan desde una fuente externa de 5 V, **compartiendo GND con la STM32**. No alimentar los servos desde un pin GPIO. La señal ECHO del HC-SR04 debe adaptarse al nivel permitido por el pin configurado; comprobar el divisor y las conexiones del montaje antes de energizarlo. Verificar asimismo la alimentación y niveles lógicos específicos del módulo TFT utilizado.

## Arquitectura del firmware

El programa está organizado en tres capas:

1. **Aplicación:** `src/main.c` coordina las etapas del barrido.
2. **Servicios:** `escaneo.c`, `pantalla.c` y `color.c` administran posiciones, dibujo y codificación de distancias.
3. **Drivers:** `gpio.c`, `clock.c`, `systick.c`, `servo.c`, `sonar.c`, `spi.c`, `ili9341.c` y `uart.c` configuran y controlan los periféricos.

El archivo `inc/board.h` centraliza la asignación de pines. El sistema utiliza un *super-loop* y las interrupciones de **SysTick** y **TIM2**.

### Máquina de estados

```text
MOVER -> ASENTAR -> DISPARAR -> ESPERAR_ECO -> PINTAR
  ^                                                  |
  |------------ siguiente posición ------------------|
                                                     |
                                      (fin de barrido)
                                                     v
                                                  PAUSA_FIN
                                                     |
                                                     +--> reinicio del barrido
```

En `ESPERAR_ECO`, una lectura válida o el agotamiento del tiempo máximo de espera permite continuar. En `PAUSA_FIN`, el sistema completa la pausa configurada antes de iniciar un nuevo barrido.

### Parámetros de diseño

| Parámetro | Configuración documentada |
|---|---|
| Reloj de CPU | 84 MHz |
| PWM de servos | 50 Hz (período de 20 ms) |
| Resolución temporal TIM2 | 1 µs por cuenta |
| Base de tiempo SysTick | 1 ms |
| SPI1 para TFT | 10,5 MHz |
| USART2 | 115200 baudios |
| PAN | 30° a 150°, paso de 4° (31 posiciones) |
| TILT | 60° a 120°, paso de 4° (16 posiciones) |
| Separación mínima entre disparos | 60 ms |
| Timeout del eco | 40 ms |

**Estos son valores de configuración del firmware, no mediciones realizadas con instrumentos.**

La distancia se obtiene mediante la expresión aproximada:

\[
d = \frac{343\,\Delta t}{2}
\]

donde \(d\) se expresa en metros y \(\Delta t\) corresponde al ancho del pulso ECHO en segundos.

## Estructura del repositorio

```text
LIDAR-/
├── inc/                  # Encabezados y asignación de pines
├── src/                  # Aplicación, servicios y drivers
├── tests/                # Pruebas independientes de módulos
├── startup/              # crt0.S y tabla de vectores
├── linker/               # Linker script
├── cmsis/                # Encabezados oficiales CMSIS
├── docs/                 # Informe, presentación, esquemáticos y evidencias
├── Makefile
├── .gitignore
└── README.md
```


## Compilación y programación

**Requisitos:** `make`, `arm-none-eabi-gcc`, `arm-none-eabi-size`, OpenOCD y una conexión ST-LINK funcional con la tarjeta.

Desde la raíz del repositorio:

```bash
make clean
make
```

Para programar el firmware principal:

```bash
make flash
```

### Pruebas individuales

El Makefile permite compilar programas de prueba utilizando `TEST=`. Por ejemplo:

```bash
make clean
make TEST=servos
make flash TEST=servos
```

También se contemplan las pruebas `sonar`, `tft`, `color`, `escaneo` y `blink`, siempre que sus archivos `tests/test_<nombre>.c` estén presentes en la versión publicada.

## Validación y resultados

El sistema integrado realiza el barrido, obtiene lecturas ultrasónicas y las representa en pantalla. La validación debe documentarse en `docs/` con fotografías del montaje, capturas de UART, señales medidas con osciloscopio y resultados de distancia frente a referencias conocidas.

El artefacto de análisis del firmware reportó para una compilación específica:

- **Imagen Flash:** 4.648 bytes de 512 KB.
- **RAM estática:** 116 bytes (`.data`: 92 B; `.bss`: 24 B) de 96 KB.

Estos tamaños dependen de la versión del código y de las opciones de compilación; deben actualizarse con `arm-none-eabi-size` en la entrega definitiva. Los tiempos de barrido y errores de medición requieren ensayos experimentales, no solo estimaciones a partir de las constantes del programa.

## Retos y limitaciones

- **Sensor HC-SR04:** se observaron fallas intermitentes; se consideró su ubicación como posible causa, pero no se identificó el origen de manera concluyente.
- **Alimentación:** se decidió alimentar externamente los SG90 para evitar exigir a la tarjeta la corriente de los motores, manteniendo una referencia común de GND.
- **Pantalla TFT:** fue la primera integración del equipo con este módulo; se revisaron cuidadosamente las conexiones y se logró su funcionamiento.
- **Limitaciones físicas:** el ángulo de apertura del ultrasonido, la orientación de las superficies, la presencia de ecos falsos y los tiempos de espera del sensor limitan la resolución y la velocidad de exploración.

## Documentación y referencias
 Como fuentes técnicas se emplean el manual de referencia **RM0368** de STMicroelectronics y las hojas de datos de los módulos HC-SR04, SG90 e ILI9341.

## Autoría y uso de inteligencia artificial

**Autores:** Iván Carpentier y Sara Sofía Otero.

Durante el desarrollo del proyecto se emplearon herramientas de inteligencia artificial como apoyo en la planificación del cronograma, las simulaciones previas al montaje físico, la validación de la lógica del programa, la organización y optimización del firmware y la revisión de código y documentación.

La implementación, integración y verificación del funcionamiento sobre el hardware fueron responsabilidad del equipo.

La descripción detallada se encuentra en Declaración de uso de IA.
