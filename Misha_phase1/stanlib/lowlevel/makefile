defualt: compile

compile:
	gcc -fno-pie -m32 --freestanding -c 'low_level.c' -o 'low_level.o'

clean:

	if [ -a low_level.o ] ; \
	then \
	rm 'low_level.o' ; \
	fi; \
