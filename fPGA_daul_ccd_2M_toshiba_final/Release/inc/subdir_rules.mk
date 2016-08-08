################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
inc/evmomapl138.obj: ../inc/evmomapl138.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="inc/evmomapl138.d" --obj_directory="inc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

inc/evmomapl138_uPP.obj: ../inc/evmomapl138_uPP.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="inc/evmomapl138_uPP.d" --obj_directory="inc" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


