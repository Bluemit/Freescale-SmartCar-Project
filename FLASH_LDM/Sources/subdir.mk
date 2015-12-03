################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Cam.c" \
"../Sources/Drive.c" \
"../Sources/Events.c" \
"../Sources/OLED.c" \
"../Sources/ProcessorExpert.c" \

C_SRCS += \
../Sources/Cam.c \
../Sources/Drive.c \
../Sources/Events.c \
../Sources/OLED.c \
../Sources/ProcessorExpert.c \

OBJS += \
./Sources/Cam_c.obj \
./Sources/Drive_c.obj \
./Sources/Events_c.obj \
./Sources/OLED_c.obj \
./Sources/ProcessorExpert_c.obj \

OBJS_QUOTED += \
"./Sources/Cam_c.obj" \
"./Sources/Drive_c.obj" \
"./Sources/Events_c.obj" \
"./Sources/OLED_c.obj" \
"./Sources/ProcessorExpert_c.obj" \

C_DEPS += \
./Sources/Cam_c.d \
./Sources/Drive_c.d \
./Sources/Events_c.d \
./Sources/OLED_c.d \
./Sources/ProcessorExpert_c.d \

C_DEPS_QUOTED += \
"./Sources/Cam_c.d" \
"./Sources/Drive_c.d" \
"./Sources/Events_c.d" \
"./Sources/OLED_c.d" \
"./Sources/ProcessorExpert_c.d" \

OBJS_OS_FORMAT += \
./Sources/Cam_c.obj \
./Sources/Drive_c.obj \
./Sources/Events_c.obj \
./Sources/OLED_c.obj \
./Sources/ProcessorExpert_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Cam_c.obj: ../Sources/Cam.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Sources/Cam.args" -o "Sources/Cam_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Drive_c.obj: ../Sources/Drive.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Sources/Drive.args" -o "Sources/Drive_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Sources/Events.args" -o "Sources/Events_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/OLED_c.obj: ../Sources/OLED.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Sources/OLED.args" -o "Sources/OLED_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/ProcessorExpert_c.obj: ../Sources/ProcessorExpert.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c @@"Sources/ProcessorExpert.args" -o "Sources/ProcessorExpert_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


