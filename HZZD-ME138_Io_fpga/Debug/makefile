################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/c6000_7.4.16

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./drivers/cpsw.obj" \
"./drivers/dcan.obj" \
"./drivers/dmtimer.obj" \
"./drivers/ecap.obj" \
"./drivers/edma.obj" \
"./drivers/ehrpwm.obj" \
"./drivers/elm.obj" \
"./drivers/emac.obj" \
"./drivers/emifa.obj" \
"./drivers/gpio_v2.obj" \
"./drivers/gpmc.obj" \
"./drivers/hsi2c.obj" \
"./drivers/lan8710a.obj" \
"./drivers/lidd.obj" \
"./drivers/mcasp.obj" \
"./drivers/mcspi.obj" \
"./drivers/mdio.obj" \
"./drivers/phy.obj" \
"./drivers/psc.obj" \
"./drivers/raster.obj" \
"./drivers/rtc.obj" \
"./drivers/spi.obj" \
"./drivers/timer.obj" \
"./drivers/tsc_adc.obj" \
"./drivers/uart.obj" \
"./drivers/vpif.obj" \
"./drivers/watchdog.obj" \
"./inc/evmomapl138.obj" \
"./inc/evmomapl138_timer.obj" \
"./inc/evmomapl138_uart.obj" \
"./src/Io_fpga.obj" \
"./src/ad9822.obj" \
"./src/dataProcess.obj" \
"./src/evmomapl138_i2c.obj" \
"./src/evmomapl138_i2c_gpio.obj" \
"./src/fpga_config.obj" \
"./src/fpga_upp.obj" \
"./src/hzzduart.obj" \
"./src/main.obj" \
"./src/tables.obj" \
"./system_config/c674x/cache.obj" \
"./system_config/c674x/interrupt.obj" \
"./system_config/c674x/intvecs.obj" \
"../OMAPL138.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include drivers/subdir_vars.mk
-include inc/subdir_vars.mk
-include src/subdir_vars.mk
-include system_config/c674x/subdir_vars.mk
-include subdir_rules.mk
-include drivers/subdir_rules.mk
-include inc/subdir_rules.mk
-include src/subdir_rules.mk
-include system_config/c674x/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
HZZD-ME138_Io_fpga.out \

EXE_OUTPUTS__QUOTED += \
"HZZD-ME138_Io_fpga.out" \

BIN_OUTPUTS += \
HZZD-ME138_Io_fpga.hex \

BIN_OUTPUTS__QUOTED += \
"HZZD-ME138_Io_fpga.hex" \


# All Target
all: HZZD-ME138_Io_fpga.out

# Tool invocations
HZZD-ME138_Io_fpga.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number -z -m"HZZD-ME138_Io_fpga.map" --stack_size=0x800 --heap_size=0x800 -i"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/lib" -i"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --reread_libs --define=DSP_CORE=1 --diag_wrap=off --display_error_number --warn_sections --xml_link_info="HZZD-ME138_Io_fpga_linkInfo.xml" --rom_model -o "HZZD-ME138_Io_fpga.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

HZZD-ME138_Io_fpga.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C6000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/hex6x"  -o "HZZD-ME138_Io_fpga.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "drivers\cpsw.d" "drivers\dcan.d" "drivers\dmtimer.d" "drivers\ecap.d" "drivers\edma.d" "drivers\ehrpwm.d" "drivers\elm.d" "drivers\emac.d" "drivers\emifa.d" "drivers\gpio_v2.d" "drivers\gpmc.d" "drivers\hsi2c.d" "drivers\lan8710a.d" "drivers\lidd.d" "drivers\mcasp.d" "drivers\mcspi.d" "drivers\mdio.d" "drivers\phy.d" "drivers\psc.d" "drivers\raster.d" "drivers\rtc.d" "drivers\spi.d" "drivers\timer.d" "drivers\tsc_adc.d" "drivers\uart.d" "drivers\vpif.d" "drivers\watchdog.d" "inc\evmomapl138.d" "inc\evmomapl138_timer.d" "inc\evmomapl138_uart.d" "src\Io_fpga.d" "src\ad9822.d" "src\dataProcess.d" "src\evmomapl138_i2c.d" "src\evmomapl138_i2c_gpio.d" "src\fpga_config.d" "src\fpga_upp.d" "src\hzzduart.d" "src\main.d" "src\tables.d" "system_config\c674x\cache.d" "system_config\c674x\interrupt.d" 
	-$(RM) "drivers\cpsw.obj" "drivers\dcan.obj" "drivers\dmtimer.obj" "drivers\ecap.obj" "drivers\edma.obj" "drivers\ehrpwm.obj" "drivers\elm.obj" "drivers\emac.obj" "drivers\emifa.obj" "drivers\gpio_v2.obj" "drivers\gpmc.obj" "drivers\hsi2c.obj" "drivers\lan8710a.obj" "drivers\lidd.obj" "drivers\mcasp.obj" "drivers\mcspi.obj" "drivers\mdio.obj" "drivers\phy.obj" "drivers\psc.obj" "drivers\raster.obj" "drivers\rtc.obj" "drivers\spi.obj" "drivers\timer.obj" "drivers\tsc_adc.obj" "drivers\uart.obj" "drivers\vpif.obj" "drivers\watchdog.obj" "inc\evmomapl138.obj" "inc\evmomapl138_timer.obj" "inc\evmomapl138_uart.obj" "src\Io_fpga.obj" "src\ad9822.obj" "src\dataProcess.obj" "src\evmomapl138_i2c.obj" "src\evmomapl138_i2c_gpio.obj" "src\fpga_config.obj" "src\fpga_upp.obj" "src\hzzduart.obj" "src\main.obj" "src\tables.obj" "system_config\c674x\cache.obj" "system_config\c674x\interrupt.obj" "system_config\c674x\intvecs.obj" 
	-$(RM) "system_config\c674x\intvecs.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

