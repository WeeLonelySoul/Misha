default: compile


compile:
	cd 'screen' && make
	cd 'lowlevel' && make
	cd 'memory'	&& make
	cd 'shell' && make
	cd 'string' && make

	cd 'commands_src/help' && make
	cd 'commands_src/info' && make
	cd 'commands_src/about' && make
	cd 'commands_src/pn' && make

	cd 'isr' && make
	cd 'idt' && make
	cd 'keyboard' && make
	cd 'time' && make
	cd 'interrupt' && make

clean:
	cd 'screen' && make clean
	cd 'lowlevel' && make clean
	cd 'memory' && make clean
	cd 'shell' && make clean
	cd 'string' && make clean
	cd 'commands_src/help' && make clean
	cd 'commands_src/info' && make clean
	cd 'commands_src/about' && make clean
	cd 'commands_src/pn' && make clean
	cd 'isr' && make clean
	cd 'idt' && make clean
	cd 'keyboard' && make clean
	cd 'time' && make clean 
	cd 'interrupt' && make clean
