# Flags
OUTPUT_AREA = ../../output_location_ignore
COMPILE_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
COMPILER_DIR = ../../compilers/bin/i686-elf-gcc

compile:
	$(COMPILER_DIR) -c bikka.c -o $(OUTPUT_AREA)/critical/bikka.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c video/video.c -o $(OUTPUT_AREA)/video.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c video/print.c -o $(OUTPUT_AREA)/print.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c common/strlen.c -o $(OUTPUT_AREA)/strlen.o $(COMPILE_FLAGS)
	$(COMPILER_DIR) -c panic/panic.c -o $(OUTPUT_AREA)/panic.o $(COMPILE_FLAGS)

