Default: compile


compile:
	gcc -fno-pie -m32 -ffreestanding -c 'idt.c' -o 'idt.o'

clean:
	if [ -a idt.o ] ; \
	then \
	rm 'idt.o' ; \
	fi; \
