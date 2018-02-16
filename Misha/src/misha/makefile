# Flags
OUTPUT_AREA = ../../output_location_ignore
COMPILE_FLAGS = -std=gnu99 -ffreestanding -Wall -Wextra
COMPILER_DIR = ../../compilers/bin/i686-elf-gcc


compile:
	$(COMPILER_DIR) -c shell/temp_shell.c -o $(OUTPUT_AREA)/temp_shell.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c syscall/syscall.c -o $(OUTPUT_AREA)/syscall.o $(COMPILE_FLAGS)	
	$(COMPILER_DIR) -c misha.c -o $(OUTPUT_AREA)/misha.o $(COMPILE_FLAGS)