#include "common.h"
#include "sys/mem_read.h"

/*
 * Typed reads from a data pointer, 0x11F968..0x11FA10: three loads and five wrappers that give them a type.
 * All are plain aligned loads (no byte swapping, no unaligned access). Only a file parser at 0x261C78 / 0x261D10
 * calls them.
 */

/* Loads a 32-bit word. */
s32 Mem_LoadWord(const void *p);

/* Loads a float. */
f32 Mem_LoadFloat(const void *p);

/* Loads an unsigned 16-bit value. */
u16 Mem_LoadHalf(const void *p);

/* Reads a signed 32-bit value. */
s32 Mem_ReadS32(const void *p);

/* Reads an unsigned 32-bit value. */
u32 Mem_ReadU32(const void *p);

/* Reads a float. */
f32 Mem_ReadF32(const void *p);

/* 0x001957D8 in BT2 is NOT BT3's Mem_ReadU16: it is `addiu sp; sd ra; jal 0x195250; ld ra; jr ra`, a pure
   forward of a0/a1 to 0x195250 (named Mem_LoadHalf here, really the technique beam spawner: it creates the
   Kamehameha body through 0x18BA90 when a1 == 0). The C passed only one argument, a1 was garbage, the spawner
   returned early and the beam body was never created (B14). An x86 jmp forwards every register as the asm does. */
__asm__(".text\n.globl Mem_ReadU16\n.type Mem_ReadU16, @function\nMem_ReadU16:\n\tjmp Mem_LoadHalf\n");

/* Reads a signed 16-bit value. */
s16 Mem_ReadS16(const void *p);
