Default: compile


compile:
	gcc -fno-pie -fstack-protector -m32 -ffreestanding -c 'isr.c' -o 'isr.o'

clean:
	if [ -a isr.o ] ; \
	then \
	rm 'isr.o' ; \
	fi; \
