################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
inc/evmomapl138.obj: ../inc/evmomapl138.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="inc/evmomapl138.d" --obj_directory="inc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

inc/evmomapl138_timer.obj: ../inc/evmomapl138_timer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="inc/evmomapl138_timer.d" --obj_directory="inc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

inc/evmomapl138_uart.obj: ../inc/evmomapl138_uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/HZZD-ME138_Io_fpga" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="inc/evmomapl138_uart.d" --obj_directory="inc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


