################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
third_party/fatfs/src/ff.obj: ../third_party/fatfs/src/ff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/third_party" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573" -g --gcc --define=ccs="ccs" --define=ENABLE_LFN --define=TARGET_IS_TM4C129_RA0 --define=PART_TM4C129XNCZAD --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="third_party/fatfs/src/ff.pp" --obj_directory="third_party/fatfs/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


