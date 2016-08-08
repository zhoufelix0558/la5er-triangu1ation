################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/Io_fpga.obj: ../src/Io_fpga.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/Io_fpga.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Nand_Flash.obj: ../src/Nand_Flash.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/Nand_Flash.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ad9822.obj: ../src/ad9822.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/ad9822.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/dataprocess.obj: ../src/dataprocess.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/dataprocess.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/dsp_Uart.obj: ../src/dsp_Uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/dsp_Uart.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fpga_config.obj: ../src/fpga_config.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/fpga_config.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fpga_upp.obj: ../src/fpga_upp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/fpga_upp.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.obj: ../src/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6740 -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --define=omapl138 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/main.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


