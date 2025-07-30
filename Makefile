# Detect OS
ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    RMDIR = rmdir /S /Q
    SEP = \\
else
    RM = rm -f
    RMDIR = rm -rf
    SEP = /
endif

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

KERNEL_SOURCES = $(call rwildcard,kernel,*.c) $(call rwildcard,drivers,*.c) $(call rwildcard,std,*.c) $(call rwildcard,cpu,*.c)
HEADERS = $(call rwildcard,includes,*.h) $(call rwildcard,drivers,*.h) $(call rwildcard,std,*.h) $(call rwildcard,cpu,*.h)

OBJ = ${KERNEL_SOURCES:.c=.o cpu/interrupt.o}

FLAGS = -g -Iinclude -Istd/includes -Idrivers/includes -Icpu/includes -Ikernel/includes

all: os-image.bin
image: os-image.bin

kernel: kernel.bin
bootsector: bootsector/bootsector.bin

os-image.bin: bootsector/bootsector.bin kernel.bin
	copy /b bootsector\bootsector.bin + kernel.bin os-image.bin

kernel.bin: bootsector/kernel.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: bootsector/kernel.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os-image.bin
	qemu-system-i386 -fda os-image.bin


%.o: %.c ${HEADERS}
	i686-elf-gcc ${FLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -p $@

%.bin: %.asm
	nasm $< -f bin -o $@

define fixpath
$(subst /,$(SEP),$1)
endef

clean:
	$(foreach file,$(OBJ),$(RM) $(call fixpath,$(file));)
	$(RM) $(call fixpath,bootsector\bootsector.bin) $(call fixpath,bootsector\kernel.o) kernel.bin os-image.bin