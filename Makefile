CFLAGS := -Wall -Werror -I include -MMD

all: shofel2_t124 reset_example.bin jtag_example.bin intermezzo.bin reset_long_bin_example.bin

# --------- x86 ----------

CC_x86 = gcc
CFLAGS_x86 := $(CFLAGS)
# shameless copypasta from https://stackoverflow.com/a/2908351/375416
C_FILES_x86:= $(wildcard exploit/*.c)
OBJ_FILES_x86 := $(addprefix build/obj_x86/,$(notdir $(C_FILES_x86:.c=.o)))
-include $(OBJ_FILES_x86:.o=.d)

build/obj_x86/%.o: exploit/%.c
	$(CC_x86) $(CFLAGS_x86) -c -o $@ $<

shofel2_t124: $(OBJ_FILES_x86)
	$(CC_x86) $(CFLAGS_x86) -o $@ $^

# ------------------------


# ----- ARMv4t Thumb -----

TOOLCHAIN_ARM ?= arm-unknown-eabi-
CC_ARM = $(TOOLCHAIN_ARM)gcc
AS_ARM = $(TOOLCHAIN_ARM)as
OBJCOPY_ARM = $(TOOLCHAIN_ARM)objcopy

CFLAGS_ARM := $(CFLAGS) -march=armv4t -mthumb -Os -ffreestanding \
	-fno-common	-fomit-frame-pointer -nostdlib -fno-builtin-printf \
	-fno-asynchronous-unwind-tables -fPIE -fno-builtin -fno-exceptions \
	-Wl,--no-dynamic-linker,--build-id=none,-T,payloads/payload.ld

# Just to test long binaries
CFLAGS_ARM_LONG_BIN := $(CFLAGS) -march=armv4t -mthumb -Os -ffreestanding \
	-fno-common	-fomit-frame-pointer -nostdlib -fno-builtin-printf \
	-fno-asynchronous-unwind-tables -fPIE -fno-builtin -fno-exceptions \
	-Wl,--no-dynamic-linker,--build-id=none,-T,payloads/payload_long_bin.ld

# shameless copypasta from https://stackoverflow.com/a/2908351/375416
C_FILES_ARM := $(wildcard payloads/*.c)
OBJ_FILES_ARM := $(addprefix build/obj_arm/,$(notdir $(C_FILES_ARM:.c=.o)))
-include $(OBJ_FILES_ARM:.o=.d)

build/obj_arm/%.o: payloads/%.c
	$(CC_ARM) $(CFLAGS_ARM) -c -o $@ $<

build/reset_example.elf: build/obj_arm/reset_example.o 
	$(CC_ARM) $(CFLAGS_ARM) -o $@ $^

build/reset_long_bin_example.elf: build/obj_arm/reset_long_bin_example.o 
	$(CC_ARM) $(CFLAGS_ARM_LONG_BIN) -o $@ $^

build/jtag_example.elf: build/obj_arm/jtag_example.o 
	$(CC_ARM) $(CFLAGS_ARM) -o $@ $^

build/intermezzo.elf: build/obj_arm/intermezzo.o 
	$(CC_ARM) $(CFLAGS_ARM) -o $@ $^

%.bin: build/%.elf
	$(OBJCOPY_ARM) -O binary $< $@

# ------------------------


clean:
	rm -f $(OBJ_FILES_ARM) $(OBJ_FILES_x86)
	rm -f shofel2_t124 reset_example.bin build/reset_example.elf jtag_example.bin build/jtag_example.elf intermezzo.bin build/intermezzo.elf reset_long_bin_example.bin build/reset_long_bin_example.elf

