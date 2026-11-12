#define func_002E1000 StgSlot_Call03  /* fix_targets */ /* the original uses 0x2e1000 here */
#include "common.h"

/* func_002E07C0 */
/* asm: pure tail jump (j func_002E1000): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002E07C0\n.type func_002E07C0, @function\nfunc_002E07C0:\n\tjmp func_002E1000\n");
