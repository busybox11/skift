#pragma once

#include <libsystem/Common.h>

#define GDT_ENTRY_COUNT 6

#define GDT_PRESENT 0b10010000	  // Present bit. This must be 1 for all valid selectors.
#define GDT_USER 0b01100000		  // Privilege, 2 bits. Contains the ring level, 0 = highest (kernel), 3 = lowest (user applications).
#define GDT_EXECUTABLE 0b00001000 // Executable bit. If 1 code in this segment can be executed, ie. a code selector. If 0 it is a data selector.
#define GDT_READWRITE 0b00000010  // Readable bit for code selectors //Writable bit for data selectors
#define GDT_ACCESSED 0b00000001

#define GDT_FLAGS 0b1100
#define TSS_FLAGS 0

struct __packed TSS
{
	uint32_t prev_tss;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomap_base;
};

struct __packed GDTDescriptor
{
	uint16_t size;
	uint32_t offset;
};

struct __packed GDTEntry
{
	uint16_t limit0_15;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t acces;
	uint8_t limit16_19 : 4;
	uint8_t flags : 4;
	uint8_t base24_31;
};

#define GDT_ENTRY(__base, __limit, __access, __flags)    \
	(GDTEntry)                                           \
	{                                                    \
		.limit0_15 = (uint16_t)((__limit)&0xffff),       \
		.base0_15 = (uint16_t)((__base)&0xffff),         \
		.base16_23 = (uint8_t)(((__base) >> 16) & 0xff), \
		.acces = (__access),                             \
		.limit16_19 = ((__limit) >> 16) & 0x0f,          \
		.flags = (__flags),                              \
		.base24_31 = (uint8_t)(((__base) >> 24) & 0xff), \
	}

void gdt_initialize();

#ifdef __cplusplus
extern "C" void gdt_flush(uint32_t);
#else
extern void gdt_flush(uint32_t);
#endif

void set_kernel_stack(uint32_t stack);
