################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../include/ \
../include/libraries/ \
../include/libraries/RN2483-Arduino-Library-master/ \
../include/libraries/RN2483-Arduino-Library-master/examples/ \
../include/libraries/RN2483-Arduino-Library-master/examples/SodaqOne-TTN-Mapper-ascii/ \
../include/libraries/RN2483-Arduino-Library-master/examples/SodaqOne-TTN-Mapper-binary/ \
../include/libraries/RN2483-Arduino-Library-master/examples/TheThingsUno-GPSshield-TTN-Mapper-binary/ \
../include/libraries/RN2483-Arduino-Library-master/src/ \
../include/libraries/SoftwareSerial/ \
../include/libraries/SoftwareSerial/src/ \
../src/ \
../src/libraries/ \
../src/libraries/RN2483-Arduino-Library-master/ \
../src/libraries/RN2483-Arduino-Library-master/examples/ \
../src/libraries/RN2483-Arduino-Library-master/examples/SodaqOne-TTN-Mapper-ascii/ \
../src/libraries/RN2483-Arduino-Library-master/examples/SodaqOne-TTN-Mapper-binary/ \
../src/libraries/RN2483-Arduino-Library-master/examples/TheThingsUno-GPSshield-TTN-Mapper-binary/ \
../src/libraries/RN2483-Arduino-Library-master/src/ \
../src/libraries/SoftwareSerial/ \
../src/libraries/SoftwareSerial/src/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o

OBJS_AS_ARGS +=  \
main.o

C_DEPS +=  \
main.d

C_DEPS_AS_ARGS +=  \
main.d

OUTPUT_FILE_PATH +=LoraLola.elf

OUTPUT_FILE_PATH_AS_ARGS +=LoraLola.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega328" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="LoraLola.map" -Wl,--start-group -Wl,-lm -Wl,-lRN2483-Arduino-Library-master.zip -Wl,-lArduino.h -Wl,-lSoftwareSerial.h -Wl,-lSoftwareSerial.cpp -Wl,-lHardwareSerial.cpp -Wl,-lHardwareSerial.h -Wl,-lHardwareSerial_private.h -Wl,-lHardwareSerial0.cpp -Wl,-lHardwareSerial1.cpp -Wl,-lHardwareSerial2.cpp -Wl,-lHardwareSerial3.cpp -Wl,-lrn2xx3.cpp -Wl,-lrn2xx3.h  -Wl,--end-group -Wl,-L"C:\Users\riman\Downloads" -Wl,-L"C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" -Wl,-L"C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SoftwareSerial\src" -Wl,-L"C:\Users\riman\Downloads\RN2483-Arduino-Library-master\src"  -Wl,--gc-sections -mmcu=atmega328 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega328"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "LoraLola.elf" "LoraLola.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "LoraLola.elf" "LoraLola.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "LoraLola.elf" > "LoraLola.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "LoraLola.elf" "LoraLola.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "LoraLola.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "LoraLola.elf" "LoraLola.a" "LoraLola.hex" "LoraLola.lss" "LoraLola.eep" "LoraLola.map" "LoraLola.srec" "LoraLola.usersignatures"
	