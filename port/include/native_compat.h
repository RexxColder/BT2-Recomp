/* Forced into the game's C when it is compiled natively for PC (port/tools/gen_native.py), like
   Tenkaichi3Decomp's port_compat.h: the base types keep their PS2 sizes (long is 64-bit on the EE and on x86-64
   Linux alike), and the assembly-inclusion macros of the decomp disappear. */
#ifndef NATIVE_COMPAT_H
#define NATIVE_COMPAT_H
#define PORT 1
#define M2CTX 1  /* include_asm.h: no MIPS assembly blocks (labels.inc, INCLUDE_ASM) */
#define INCLUDE_ASM(...)
#define INCLUDE_RODATA(...)
#endif
