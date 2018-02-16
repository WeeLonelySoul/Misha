OUTPUT_AREA = ./output_location_ignore
FINISHED_AREA = ./finished_compile_area
VIRTUAL_MACHINE = qemu-system-i386
VIRTUAL_MACHINE_CONFIG = -kernel
COLOR_YELLOW = \e[93m
COLOR_BLUE = \e[1;34m
COLOR_END_THE_SPREAD = \e[0m
FLAGS = -ffreestanding -nostdlib
COMPILER = ./compilers/bin/i686-elf-gcc
COMPILER_DIR = ./compilers/i686-elf


compile:

	if [ -a output_location_ignore ] ; \
	then \
		echo -e "File already exists. Ignoring!" ; \
	else \
		mkdir output_location_ignore ; \
	fi ; \

	if [ -a ./finished_compile_area ] ; \
	then \
		echo -e "File already exists. Ignoring!" ; \
	else \
		mkdir finished_compile_area ; \
	fi ; \

	if [ -a ./compilers ] ; \
	then \
		echo -e "File already exists. Ignoring!" ; \
	else \
		mkdir compilers ; \
	fi ; \

	if [ -a $(OUTPUT_AREA)/critical ] ; \
	then \
		echo -e "File already exists. Ignoring!" ; \
	else \
		mkdir $(OUTPUT_AREA)/critical ; \
	fi ; \

	if [ -a $(COMPILER_DIR) ] ; \
	then \
		clear; \
		cd src/ && make ; \
	else \
		clear ; \
		make compile-compilers ; \
		cd src/ && make ; \
	fi; \

	# Finishing up
	$(COMPILER) -T link.ld -o $(FINISHED_AREA)/Misha.bin $(FLAGS) $(OUTPUT_AREA)/critical/boot.o $(OUTPUT_AREA)/critical/bikka.o $(OUTPUT_AREA)/*.o  	


clean:
	if [ -a $(OUTPUT_AREA)/critical ] ; \
	then \
		rm -r $(OUTPUT_AREA)/* ; \
		clear ; \
		echo "Removed output files from the directory 'output_location_ignore'!" ; \
	else \
		clear ; \
		echo "Nothing to remove!" ; \
	fi ;\

	if [ -a $(FINISHED_AREA)/Misha.bin ] ; \
	then \
		rm $(FINISHED_AREA)/Misha.bin ; \
		clear ; \
		echo "Removed output files from the directory '$(FINISHED_AREA)'!" ; \
	else \
		clear ; \
		echo "Nothing to remove!" ; \
	fi; \



run: compile
	$(VIRTUAL_MACHINE) $(VIRTUAL_MACHINE_CONFIG) $(FINISHED_AREA)/Misha.bin


help:
	@echo -e "$(COLOR_YELLOW) Commands available: $(COLOR_END_THE_SPREAD)"
	@echo ""
	@echo -e "$(COLOR_BLUE) compile $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Compiles the OS and the Kernel $(COLOR_END_THE_SPREAD)"
	@echo ""
	@echo -e "$(COLOR_BLUE) clean $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Cleans out any .o from 'output_location_ignore' $(COLOR_END_THE_SPREAD)"
	@echo ""
	@echo -e "$(COLOR_BLUE) run $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Compiles everything and runs it through qemu [$(VIRTUAL_MACHINE)] $(COLOR_END_THE_SPREAD)"
	@echo ""
	@echo -e "$(COLOR_BLUE) help $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Shows this screen $(COLOR_END_THE_SPREAD)"
	@echo ""
	@echo -e "$(COLOR_BLUE) compile-compilers $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Used to compile the compilers needed for this project $(COLOR_END_THE_SPREAD)"
	@echo ""
	@echo -e "$(COLOR_BLUE) clean-compilers $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Removes all the compiled files in $(COLOR_BLUE)'./compilers/'$(COLOR_END_THE_SPREAD)" 

	@echo ""
	@echo -e "$(COLOR_BLUE) iso $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Creates an iso image in the folder $(COLOR_BLUE)'./finished_compile_area'$(COLOR_END_THE_SPREAD)"

	@echo ""
	@echo -e "$(COLOR_BLUE) iso-run $(COLOR_END_THE_SPREAD)"
	@echo -e "$(COLOR_YELLOW)  -> Creates an iso image and runs it $(COLOR_END_THE_SPREAD)"


compile-compilers:
	@echo -e "$(COLOR_BLUE) Compiling 'Compilers' to the local location $(COLOR_YELLOW)'compilers' $(COLOR_END_THE_SPREAD)"
	./src/compilers/install.sh

clean-compilers:
	rm -r compilers/*


iso: compile
	mkdir -p finished_compile_area/iso/
	mkdir -p finished_compile_area/iso/boot/
	mkdir -p finished_compile_area/iso/boot/grub

	cp finished_compile_area/Misha.bin finished_compile_area/iso/
	@echo -e 'menuentry "Misha" {\n multiboot /Misha.bin	\n}' > finished_compile_area/iso/boot/grub/grub.cfg
	grub-mkrescue -o finished_compile_area/Misha.iso finished_compile_area/iso/


iso-run: compile iso
	$(VIRTUAL_MACHINE) $(FINISHED_AREA)/Misha.iso
	