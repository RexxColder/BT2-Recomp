#include "common.h"

/* func_00296DE8 */
/* asm: pure tail jump (j Rigid_SetTransform): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_00296DE8\n.type func_00296DE8, @function\nfunc_00296DE8:\n\tjmp Rigid_SetTransform\n");
