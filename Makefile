Proj_Name=syn115
CMSIS_Dir=/home/jack/w/lib/cmsis/STM32CubeF1/Drivers/CMSIS

CMSIS_Core_Include=$(CMSIS_Dir)/Core/Include
CMSIS_Device_Include=$(CMSIS_Dir)/Device/ST/STM32F1xx/Include
CMSIS_Device_Source=$(CMSIS_Dir)/Device/ST/STM32F1xx/Source/Templates

Arm_Dir=/home/jack/w/tools/gcc-arm-none-eabi
Arm_Lib_Dir=$(Arm_Dir)/arm-none-eabi/lib/thumb/v7-m/nofp
Arm_Lib_Gcc_Dir=$(Arm_Dir)/lib/gcc/arm-none-eabi/10.3.1/thumb/v7-m/nofp

COREFLAGS=-mthumb -mcpu=cortex-m3
CFLAGS=$(COREFLAGS) -Wall -Wdouble-promotion -fsingle-precision-constant -g -ggdb -c
CFLAGS+=-ffunction-sections -fdata-sections -std=c99
LDFLAGS=$(COREFLAGS) -L$(Arm_Lib_Dir) -L$(Arm_Lib_Gcc_Dir) --specs=nosys.specs

all:$(Proj_Name)

$(Proj_Name):startup_stm32f103x6.o system_stm32f1xx.o main.o rcc.o gpio.o usart.o
	arm-none-eabi-gcc $(LDFLAGS) -Tmem.ld -o $(Proj_Name).elf startup_stm32f103x6.o system_stm32f1xx.o main.o rcc.o gpio.o usart.o -lnosys -lm
	arm-none-eabi-objcopy -O binary $(Proj_Name).elf $(Proj_Name).bin

startup_stm32f103x6.o:
	arm-none-eabi-as -mthumb -mcpu=cortex-m3 -o $@ $(CMSIS_Device_Source)/gcc/startup_stm32f103x6.s
	
system_stm32f1xx.o:
	arm-none-eabi-gcc $(CFLAGS) -nostdlib -nostartfiles -ffreestanding -I$(CMSIS_Device_Include) -I$(CMSIS_Core_Include) -c $(CMSIS_Device_Source)/system_stm32f1xx.c -o $@ -g -DSTM32F103x6
	
main.o:
	arm-none-eabi-gcc $(CFLAGS) -I$(CMSIS_Device_Include) -I$(CMSIS_Core_Include) -c -g -o $@ main.c -DSTM32F103x6
			
rcc.o:
	arm-none-eabi-gcc $(CFLAGS) -I$(CMSIS_Device_Include) -I$(CMSIS_Core_Include) -c -g -o $@ rcc.c -DSTM32F103x6
	
gpio.o:
	arm-none-eabi-gcc $(CFLAGS) -I$(CMSIS_Device_Include) -I$(CMSIS_Core_Include) -c -g -o $@ gpio.c -DSTM32F103x6
	
usart.o:
	arm-none-eabi-gcc $(CFLAGS) -I$(CMSIS_Device_Include) -I$(CMSIS_Core_Include) -c -g -o $@ usart.c -DSTM32F103x6
	
clean:
	rm *.o *.bin *.elf
