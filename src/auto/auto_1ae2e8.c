#include "common.h"

/* func_001AE2E8 */
/* asm: pure tail jump (j func_001B0B20): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_001AE2E8\n.type func_001AE2E8, @function\nfunc_001AE2E8:\n\tjmp func_001B0B20\n");
