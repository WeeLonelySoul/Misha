Default: compile


compile:
	gcc -fno-pie -fstack-protector -m32 -ffreestanding -c 'keyboard.c' -o 'keyboard.o'

clean:
	if [ -a keyboard.o ] ; \
	then \
	rm 'keyboard.o' ; \
	fi; \
