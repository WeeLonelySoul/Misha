default: compile


compile:
	gcc -fno-pie -m32 -ffreestanding -c 'bikka.c' -o 'bikka.o'
	cd asm && nasm -f elf kernel_entry.asm -o kernel_entry.o

clean:
	if [ -a bikka.o ] ; \
	then \
	rm 'bikka.o' ; \
	fi; \

	if [ -a asm/kernel_entry.o ] ; \
	then \
	rm 'asm/kernel_entry.o' ; \
	fi; \
