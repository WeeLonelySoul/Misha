default: compile

compile:
	nasm interrupt.asm -f elf  -o interrupt.o

clean:
	if [ -a interrupt.o ] ; \
	then  \
	rm 'interrupt.o' ; \
	fi; \
