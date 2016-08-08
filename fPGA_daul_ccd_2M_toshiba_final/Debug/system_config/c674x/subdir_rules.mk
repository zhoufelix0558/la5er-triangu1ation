################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
system_config/c674x/cache.obj: ../system_config/c674x/cache.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="system_config/c674x/cache.d" --obj_directory="system_config/c674x" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_config/c674x/interrupt.obj: ../system_config/c674x/interrupt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="system_config/c674x/interrupt.d" --obj_directory="system_config/c674x" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_config/c674x/intvecs.obj: ../system_config/c674x/intvecs.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.16/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.16/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/Users/Hypersen04/workspace_v6_1_3/fPGA_daul_ccd_2M_toshiba" --define=omapl138 --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="system_config/c674x/intvecs.d" --obj_directory="system_config/c674x" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


