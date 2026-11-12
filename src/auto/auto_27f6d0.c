#include "common.h"

/* func_0027F6D0 */
/* asm: pure tail jump (j GfxPost_CopyAlphaToDepth): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_0027F6D0\n.type func_0027F6D0, @function\nfunc_0027F6D0:\n\tjmp GfxPost_CopyAlphaToDepth\n");
