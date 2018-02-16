#ifndef MULTITASKING_H
#define MULTITASKING_H 1


page_directory_t *MULTITASKING_CLONE_DIRECTORY(page_directory_t *SRC);
static page_table_t *MULTITASKING_CLONE_TABLE(page_table_t *SRC, u32 *PhysAddr);
extern MULTITASKING_COPY_PHYSICAL_PAGE(); /* Look in multitasking.asm */
#endif