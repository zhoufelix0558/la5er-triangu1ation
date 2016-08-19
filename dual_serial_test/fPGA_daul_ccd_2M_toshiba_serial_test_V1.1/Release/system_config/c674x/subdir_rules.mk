################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
system_config/c674x/cache.obj: ../system_config/c674x/cache.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="system_config/c674x/cache.d" --obj_directory="system_config/c674x" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_config/c674x/interrupt.obj: ../system_config/c674x/interrupt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="system_config/c674x/interrupt.d" --obj_directory="system_config/c674x" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_config/c674x/intvecs.obj: ../system_config/c674x/intvecs.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="system_config/c674x/intvecs.d" --obj_directory="system_config/c674x" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


