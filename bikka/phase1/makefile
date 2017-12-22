
default: compile


clean:
	cd 'bikka' && make clean
	if [ -a bikka.bin ] ; \
	then \
	rm 'bikka.bin' ; \
	fi; \

	if [ -a boot/32bit/boot.bin ] ; \
	then \
	rm 'boot/32bit/boot.bin' ; \
	fi; \

	if [ -a bikka_k ] ; \
	then  \
	rm 'bikka_k' ; \
	fi; \

	if [ -a bikkakernel.bin ] ; \
	then  \
	rm 'bikkakernel.bin' ; \
	fi; \

	if [ -a Misha_Phase_1 ] ; \
	then \
	rm 'Misha_Phase_1' ; \
	fi; \


	cd 'stanlib' && make clean

compile:
	
	cd 'bikka' && make
	cd 'boot/32bit' && nasm 32_bit_loader.asm -f bin -o boot.bin
	cd 'stanlib' && make
	ld -T link.ld -m elf_i386 -o bikka.bin -Ttext 0x1000 bikka/asm/kernel_entry.o bikka/bikka.o stanlib/screen/screen.o stanlib/commands_src/pn/pn.o stanlib/lowlevel/low_level.o stanlib/memory/memory.o stanlib/shell/shell.o stanlib/string/string.o stanlib/idt/idt.o stanlib/isr/isr.o stanlib/keyboard/keyboard.o stanlib/time/time.o stanlib/interrupt/interrupt.o stanlib/commands_src/help/help.o stanlib/commands_src/info/info.o stanlib/commands_src/about/about.o
	objcopy -O binary bikka.bin bikkakernel.bin
	cat 'boot/32bit/boot.bin' 'bikkakernel.bin' > Misha_Phase_1

	rm 'bikkakernel.bin'
	rm 'bikka.bin'

run: compile
	qemu-system-i386 'Misha_Phase_1'
