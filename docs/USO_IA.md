## Declaración de uso de inteligencia artificial

Durante el desarrollo del proyecto **Sistema de Barrido Ultrasónico de Bajo Costo con STM32F401RE**, se utilizaron herramientas de inteligencia artificial generativa, principalmente **Claude y ChatGPT**, como apoyo en las etapas de planificación, diseño, desarrollo, optimización y documentación del sistema.

Su utilización tuvo como propósito facilitar la organización del trabajo, evaluar alternativas de implementación y apoyar la identificación de posibles errores antes y durante la integración física de los componentes.

### 1. Planificación y organización del proyecto

Se emplearon herramientas de IA como apoyo para la elaboración del cronograma de trabajo, la definición de las etapas de desarrollo y la distribución de actividades.

Esto permitió estructurar el proyecto mediante objetivos progresivos, comenzando por la configuración del microcontrolador y las pruebas individuales de los periféricos, hasta llegar a la integración del sistema completo.

### 2. Simulaciones y validación previa al montaje

La inteligencia artificial se utilizó para apoyar la elaboración y el análisis de simulaciones del funcionamiento del sistema antes de realizar el montaje físico.

Estas simulaciones permitieron estudiar el comportamiento esperado del programa, analizar la secuencia de ejecución de la máquina de estados y verificar conceptualmente la coordinación entre los servomotores, el sensor ultrasónico y la pantalla.

El objetivo principal fue **validar la lógica del firmware e identificar posibles inconsistencias antes de implementar las soluciones sobre el hardware real**, reduciendo la necesidad de realizar modificaciones directamente durante el montaje.

### 3. Desarrollo, organización y optimización del código

Durante la programación del firmware bare-metal, las herramientas de IA proporcionaron asistencia para estructurar, revisar y optimizar diferentes módulos del programa.

Su utilización incluyó la organización del código en archivos independientes, la separación entre drivers, servicios y aplicación principal, y el análisis de alternativas para mejorar la ejecución del sistema.

También se emplearon para revisar la configuración de periféricos, analizar secuencias de temporización, evaluar condiciones de operación y proponer mejoras relacionadas con la legibilidad, modularidad y mantenimiento del código.

Las propuestas generadas fueron utilizadas como material de apoyo para el desarrollo y sometidas a revisión durante la integración del proyecto.

### 4. Revisión de código y documentación

Se utilizaron herramientas de IA para revisar fragmentos de código, interpretar mensajes de compilación y analizar posibles errores de programación.

Adicionalmente, se emplearon para mejorar la claridad, estructura, redacción y presentación de la documentación técnica, incluyendo el informe IEEE, la presentación del proyecto, los diagramas explicativos y el archivo README del repositorio.

La revisión de textos tuvo como finalidad mejorar la comunicación de los procedimientos, decisiones de diseño y resultados del proyecto, manteniendo la coherencia con la implementación desarrollada.

### 5. Responsabilidad y verificación

La inteligencia artificial se utilizó como herramienta complementaria y no como sustituto de la implementación y evaluación del proyecto.

El equipo fue responsable de las decisiones finales de diseño, la selección y conexión de los componentes, la compilación del firmware, su programación en el microcontrolador y las pruebas de funcionamiento sobre el montaje físico.

Las simulaciones y sugerencias generadas mediante IA se consideraron recursos de apoyo, mientras que la validación definitiva del sistema correspondió a las pruebas realizadas sobre el hardware.

Los archivos desarrollados o modificados con asistencia de IA deben identificarse en el repositorio para mantener la trazabilidad del proceso de desarrollo y diferenciar los aportes de estas herramientas del trabajo realizado directamente por el equipo.

## 6. Identificación de archivos y código asistido

Con el propósito de mantener la transparencia y trazabilidad del desarrollo, se identifican los archivos en los que se emplearon herramientas de inteligencia artificial como apoyo para la programación, organización, optimización y revisión del código.

La asistencia de IA fue parcial y variable según el archivo. Esto no significa que la totalidad del código haya sido generada automáticamente.

### 6.1. Archivos desarrollados con asistencia de IA

| Archivo | Tipo de asistencia |
|---|---|
| `src/main.c` | Organización y optimización de la lógica principal, implementación de la máquina de estados y coordinación de los módulos. |
| `src/escaneo.c` | Revisión y organización del algoritmo de barrido serpenteante y control de posiciones angulares. |
| `src/sonar.c` | Apoyo en la lógica de medición ultrasónica, temporización e interrupciones de TIM2. |
| `src/pantalla.c` | Organización de funciones para la representación gráfica y actualización de la pantalla. |
| `src/color.c` | Revisión y optimización de funciones para convertir distancias a colores RGB565. |
| `inc/board.h` | Organización y documentación de la asignación de pines del sistema. |
| `inc/escaneo.h` | Definición y revisión de estructuras, constantes y declaraciones del módulo de escaneo. |
| `inc/sonar.h` | Revisión de declaraciones y organización de la interfaz del módulo ultrasónico. |
| `inc/pantalla.h` | Apoyo en la definición y documentación de funciones y parámetros de visualización. |

Adicionalmente, se utilizaron herramientas de inteligencia artificial para revisar fragmentos de otros módulos, identificar posibles errores de programación y proponer mejoras relacionadas con la claridad, modularidad y mantenimiento del firmware.

### 6.2. Archivos basados en material del profesor

Los siguientes archivos se tomaron como base de ejemplos y materiales proporcionados durante el curso de Microprocesadores e Interfaces:

| Archivo | Origen y modificaciones |
|---|---|
| `startup/crt0.S` | Archivo de arranque basado en el material del curso, originalmente derivado de código de STMicroelectronics. Fue revisado y adaptado para su integración en el proyecto. |
| `linker/linker_script.ld` | Script de enlazado utilizado como referencia durante el curso, con ajustes menores realizados por el equipo. |
| `Makefile` | Basado en ejemplos de compilación suministrados por el profesor. Se modificó para organizar los archivos del proyecto, incorporar diferentes módulos y facilitar la compilación de pruebas individuales. |

Estos archivos no se presentan como desarrollos completamente originales del equipo ni como código generado íntegramente mediante inteligencia artificial. Se reconoce su procedencia académica y las adaptaciones realizadas.

### 6.3. Responsabilidad y verificación

Las herramientas de inteligencia artificial se utilizaron como apoyo para analizar alternativas, resolver dudas técnicas, revisar código y mejorar la documentación.

El equipo fue responsable de las decisiones finales de diseño, selección y conexión de componentes, adaptación del firmware, programación del microcontrolador y pruebas de funcionamiento sobre el montaje físico.

Las sugerencias obtenidas mediante IA fueron revisadas y adaptadas de acuerdo con los requerimientos del proyecto.

