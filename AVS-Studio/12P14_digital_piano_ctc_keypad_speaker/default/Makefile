###############################################################################
# Makefile for the project 12P14_digital_piano_ctc_keypad_speaker
###############################################################################

## General Flags
PROJECT = 12P14_digital_piano_ctc_keypad_speaker
MCU = atmega16
TARGET = 12P14_digital_piano_ctc_keypad_speaker.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=12P14_digital_piano_ctc_keypad_speaker.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = 12P14_digital_piano_ctc_keypad_speaker.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) 12P14_digital_piano_ctc_keypad_speaker.hex 12P14_digital_piano_ctc_keypad_speaker.eep 12P14_digital_piano_ctc_keypad_speaker.lss size

## Compile
12P14_digital_piano_ctc_keypad_speaker.o: ../12P14_digital_piano_ctc_keypad_speaker.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) 12P14_digital_piano_ctc_keypad_speaker.elf dep/* 12P14_digital_piano_ctc_keypad_speaker.hex 12P14_digital_piano_ctc_keypad_speaker.eep 12P14_digital_piano_ctc_keypad_speaker.lss 12P14_digital_piano_ctc_keypad_speaker.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

