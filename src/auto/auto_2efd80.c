#include "common.h"

/* func_002EFD80 */
void func_002EFD80(void) {  }
/* func_002EFD88 */
/* asm: pure tail jump (j func_00302AC8): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EFD88\n.type func_002EFD88, @function\nfunc_002EFD88:\n\tjmp func_00302AC8\n");
