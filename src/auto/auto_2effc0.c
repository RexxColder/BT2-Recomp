#include "common.h"

/* func_002EFFC0 */
/* asm: pure tail jump (j func_003038B0): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFFC0\n.type func_002EFFC0, @function\nfunc_002EFFC0:\n\tjmp func_003038B0\n");
