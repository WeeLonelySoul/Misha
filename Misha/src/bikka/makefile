# Flags
OUTPUT_AREA = ../../output_location_ignore
COMPILE_FLAGS = -std=gnu99 -ffreestanding -Wall -Wextra
COMPILER_DIR = ../../compilers/bin/i686-elf-gcc
ASM_COMPILER = nasm
ASM_COMPILER_FLAGS = -f elf

compile:
	$(COMPILER_DIR) -c bikka.c -o $(OUTPUT_AREA)/critical/bikka.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c syssetupprint.c -o $(OUTPUT_AREA)/syssetupprint.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c video/video.c -o $(OUTPUT_AREA)/video.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c video/print.c -o $(OUTPUT_AREA)/print.o $(COMPILE_FLAGS)

	$(COMPILER_DIR) -c common/strlen.c -o $(OUTPUT_AREA)/strlen.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/inttoascii.c -o $(OUTPUT_AREA)/inttoascii.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/reverse.c -o $(OUTPUT_AREA)/reverse.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/strcmp.c -o $(OUTPUT_AREA)/strcmp.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/append.c -o $(OUTPUT_AREA)/append.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/backspace.c -o $(OUTPUT_AREA)/backspace.o $(COMPILE_FLAGS)

		
	$(COMPILER_DIR) -c panic/panic.c -o $(OUTPUT_AREA)/panic.o $(COMPILE_FLAGS)

	$(COMPILER_DIR) -c isr/isr.c -o $(OUTPUT_AREA)/isr.o $(COMPILE_FLAGS)
	$(ASM_COMPILER) isr/isr.asm -o $(OUTPUT_AREA)/isr_asm.o $(ASM_COMPILER_FLAGS)

	$(COMPILER_DIR) -c irq/irq.c -o $(OUTPUT_AREA)/irq.o $(COMPILE_FLAGS)	
	$(ASM_COMPILER) irq/irq.asm -o $(OUTPUT_AREA)/irq_asm.o $(ASM_COMPILER_FLAGS)

	$(COMPILER_DIR) -c idt/idt.c -o $(OUTPUT_AREA)/idt.o $(COMPILE_FLAGS)
	$(ASM_COMPILER) idt/idt.asm -o $(OUTPUT_AREA)/idt_asm.o $(ASM_COMPILER_FLAGS)

	$(COMPILER_DIR) -c gdt/gdt.c -o $(OUTPUT_AREA)/gdt.o $(COMPILE_FLAGS)
	$(ASM_COMPILER) gdt/gdt.asm -o $(OUTPUT_AREA)/gdt_asm.o	$(ASM_COMPILER_FLAGS)			

	$(COMPILER_DIR) -c tss/tss.c -o $(OUTPUT_AREA)/tss.o $(COMPILE_FLAGS)
	$(ASM_COMPILER) tss/tss.asm -o $(OUTPUT_AREA)/tss_asm.o $(ASM_COMPILER_FLAGS)

	$(COMPILER_DIR) -c low_level/port_byte_in_or_out.c -o $(OUTPUT_AREA)/port_byte.o $(COMPILE_FLAGS)			       
	$(COMPILER_DIR) -c low_level/port_word_in_or_out.c -o $(OUTPUT_AREA)/port_word.o $(COMPILE_FLAGS)

	$(COMPILER_DIR) -c memory/memory.c -o $(OUTPUT_AREA)/memory.o $(COMPILE_FLAGS)
	$(ASM_COMPILER) memory/memory_detect.asm -o $(OUTPUT_AREA)/memory_detect.o $(ASM_COMPILER_FLAGS)			
	$(ASM_COMPILER) memory/multitasking.asm -o $(OUTPUT_AREA)/multitasking.o $(ASM_COMPILER_FLAGS)			

	$(COMPILER_DIR) -c keyboard/keyboard.c -o $(OUTPUT_AREA)/keyboard.o $(COMPILE_FLAGS)

	$(COMPILER_DIR) -c time/time.c -o $(OUTPUT_AREA)/time.o $(COMPILE_FLAGS)

	$(COMPILER_DIR) -c task/task.c -o $(OUTPUT_AREA)/task.o $(COMPILE_FLAGS)			       
	$(ASM_COMPILER) task/task.asm -o $(OUTPUT_AREA)/task_asm.o $(ASM_COMPILER_FLAGS)			

	$(COMPILER_DIR) -c ordered_array_algorithm/ordered_array_algorithm.c -o $(OUTPUT_AREA)/ordered_array_algorithm.o $(COMPILE_FLAGS)			       

	$(COMPILER_DIR) -c heap/kheap.c -o $(OUTPUT_AREA)/kheap.o $(COMPILE_FLAGS)			       

		$(COMPILER_DIR) -c shell/shell.c -o $(OUTPUT_AREA)/shell.o $(COMPILE_FLAGS)			       