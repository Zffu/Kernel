rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

KERNEL_SOURCES = $(call rwildcard,src,*.c)

OBJ = ${KERNEL_SOURCES:.c=.o}

FLAGS = -g -Iinclude

all: os-image.bin
image: os-image.bin

kernel: kernel.bin
bootsector: bootsector/bootsector.bin

os-image.bin: bootsector/bootsector.bin kernel.bin
	copy /b bootsector\bootsector.bin + kernel.bin os-image.bin

kernel.bin: bootsector/kernel.o ${OBJ}
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

run: os-image.bin
	qemu-system-x86_64 -fda os-image.bin

%.o: %.c ${HEADERS}:
	x86_64-elf-gcc ${FLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -p $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	del /Q /F *.bin *.dis *.o os-image.bin
	del /Q /F kernel\*.o bootsector\*.bin drivers\*.o bootsector\*.o