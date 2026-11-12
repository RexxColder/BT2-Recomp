#include "common.h"

/* func_00272CB0 */
/* asm: pure tail jump (j func_00276B00): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00272CB0\n.type func_00272CB0, @function\nfunc_00272CB0:\n\tjmp func_00276B00\n");
