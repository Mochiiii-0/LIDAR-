# Makefile de LIDAR-  (basado en NUCLEO-64/13-Timers-IC-1 del profe)
#   make              -> compila src/main.c + los demás src/*.c
#   make TEST=servos  -> cambia main.c por tests/test_servos.c (también blink, sonar, tft, color, escaneo)
#   make flash        -> graba la NUCLEO con openocd
APPNAME = main
CC      = arm-none-eabi-gcc
CFLAGS  = -Wall -Wextra -std=c11 -ffreestanding
ARCH    = -mcpu=cortex-m4
LINKERSCRIPT = linker/linker_script.ld
BUILD   = build
 
# CMSIS: copiado dentro del repo para que compile en cualquier computador
CMSIS   = cmsis
STM32F4 = $(CMSIS)/Device/ST/STM32F4xx
INCLUDE = -Iinc -I$(STM32F4)/Include -I$(CMSIS)/Core/Include
 
# Programa principal o un test
ifdef TEST
  APP = tests/test_$(TEST).c
else
  APP = src/main.c
endif
C_SRC  = $(APP)
C_SRC += $(filter-out src/main.c, $(wildcard src/*.c))
C_SRC += $(STM32F4)/Source/system_stm32f4xx.c
ASM_SRC = startup/crt0.S
 
OBJS  = $(patsubst %.c, $(BUILD)/%.o, $(notdir $(C_SRC)))
OBJS += $(patsubst %.S, $(BUILD)/%.o, $(notdir $(ASM_SRC)))
vpath %.c $(sort $(dir $(C_SRC)))
vpath %.S $(sort $(dir $(ASM_SRC)))
 
CFLAGS += -Og -g -fno-pic
CFLAGS += $(ARCH) --specs=nosys.specs --specs=nano.specs $(INCLUDE) -DSTM32F401xE
LDFLAGS = -T$(LINKERSCRIPT) -nostdlib -Wl,--no-relax
LDLIBS  = -lc -lgcc
 
all: $(APPNAME).elf
 
$(APPNAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	arm-none-eabi-size $@
 
$(BUILD)/%.o: %.S
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
 
$(BUILD)/%.o: %.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
 
.PHONY: clean flash debug
clean:
	rm -rf $(BUILD) *.elf
 
flash: $(APPNAME).elf
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(APPNAME).elf verify reset exit"
 
debug: $(APPNAME).elf
	gdb-multiarch $(APPNAME).elf -ex "target remote :1234" -ex "tb Reset_Handler"