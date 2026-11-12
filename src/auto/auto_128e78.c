#include "common.h"

/* func_00128E78 */
/* asm: pure tail jump (j sceVu0DropShadowMatrix): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00128E78\n.type func_00128E78, @function\nfunc_00128E78:\n\tjmp sceVu0DropShadowMatrix\n");
