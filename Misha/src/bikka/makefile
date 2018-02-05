# Flags
OUTPUT_AREA = ../../output_location_ignore
COMPILE_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
COMPILER_DIR = ../../compilers/bin/i686-elf-gcc
ASM_COMPILER = nasm
ASM_COMPILER_FLAGS = -f elf

compile:
	$(COMPILER_DIR) -c bikka.c -o $(OUTPUT_AREA)/critical/bikka.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c _PrintSysSetup.c -o $(OUTPUT_AREA)/_PrintSysSetup.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c video/video.c -o $(OUTPUT_AREA)/video.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c video/print.c -o $(OUTPUT_AREA)/print.o $(COMPILE_FLAGS)

	$(COMPILER_DIR) -c common/strlen.c -o $(OUTPUT_AREA)/strlen.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/inttoascii.c -o $(OUTPUT_AREA)/inttoascii.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/reverse.c -o $(OUTPUT_AREA)/reverse.o $(COMPILE_FLAGS)
	
	$(COMPILER_DIR) -c panic/panic.c -o $(OUTPUT_AREA)/panic.o $(COMPILE_FLAGS)

	$(COMPILER_DIR) -c isr/isr.c -o $(OUTPUT_AREA)/isr.o $(COMPILE_FLAGS)
	$(ASM_COMPILER) isr/isr.asm -o $(OUTPUT_AREA)/isr_asm.o $(ASM_COMPILER_FLAGS)

	$(COMPILER_DIR) -c irq/irq.c -o $(OUTPUT_AREA)/irq.o $(COMPILE_FLAGS)	
	$(ASM_COMPILER) irq/irq.asm -o $(OUTPUT_AREA)/irq_asm.o $(ASM_COMPILER_FLAGS)

	$(COMPILER_DIR) -c idt/idt.c -o $(OUTPUT_AREA)/idt.o $(COMPILE_FLAGS)


	$(COMPILER_DIR) -c low_level/port_byte_in_or_out.c -o $(OUTPUT_AREA)/port_byte.o $(COMPILE_FLAGS)			       
	$(COMPILER_DIR) -c low_level/port_word_in_or_out.c -o $(OUTPUT_AREA)/port_word.o $(COMPILE_FLAGS)				

