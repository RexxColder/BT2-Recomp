#include "common.h"

/* func_00128D50 */
/* asm: pure tail jump (j sceVu0NormalLightMatrix): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00128D50\n.type func_00128D50, @function\nfunc_00128D50:\n\tjmp sceVu0NormalLightMatrix\n");
