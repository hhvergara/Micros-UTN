################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/keyboard.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/keyboard.c \
../Sources/main.c \

OBJS += \
./Sources/keyboard_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/keyboard_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/keyboard_c.d \
./Sources/main_c.d \

C_DEPS_QUOTED += \
"./Sources/keyboard_c.d" \
"./Sources/main_c.d" \

OBJS_OS_FORMAT += \
./Sources/keyboard_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/keyboard_c.obj: ../Sources/keyboard.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/keyboard.args" -ObjN="Sources/keyboard_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


