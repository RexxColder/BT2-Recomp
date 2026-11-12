#include "common.h"

/* func_002EF398 */
/* asm: pure tail jump (j BtlLoad_EndStageSwap): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002EF398\n.type func_002EF398, @function\nfunc_002EF398:\n\tjmp BtlLoad_EndStageSwap\n");
