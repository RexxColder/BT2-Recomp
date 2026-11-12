#include "common.h"

/* func_0025B8F8 */
/* asm: pure tail jump (j DemoCam_Stop): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0025B8F8\n.type func_0025B8F8, @function\nfunc_0025B8F8:\n\tjmp DemoCam_Stop\n");
