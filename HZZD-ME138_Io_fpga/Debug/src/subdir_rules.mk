################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/Io_fpga.obj: ../src/Io_fpga.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/Io_fpga.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ad9822.obj: ../src/ad9822.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/ad9822.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/dataProcess.obj: ../src/dataProcess.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/dataProcess.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/evmomapl138_i2c.obj: ../src/evmomapl138_i2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/evmomapl138_i2c.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/evmomapl138_i2c_gpio.obj: ../src/evmomapl138_i2c_gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/evmomapl138_i2c_gpio.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fpga_config.obj: ../src/fpga_config.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/fpga_config.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fpga_upp.obj: ../src/fpga_upp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/fpga_upp.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/hzzduart.obj: ../src/hzzduart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/hzzduart.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.obj: ../src/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/main.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/tables.obj: ../src/tables.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/tables.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


