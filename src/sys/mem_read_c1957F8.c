#define Mem_LoadHalf func_00195538  /* fix_targets */ /* the original uses 0x195538 here */
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

/* Reads an unsigned 16-bit value. */
s32 func_001957F8(const void *p) {
    return Mem_LoadHalf(p);
}

/* Reads a signed 16-bit value. */
s16 Mem_ReadS16(const void *p);
