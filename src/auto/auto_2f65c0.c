#include "common.h"

/* func_002F65C0 */
u32 func_002F65C0(u32 a0) { return func_002F0420(*(u32 *)((u8 *)a0 + 0x4)); }
/* func_002F65D8 */
void func_002F65D8(void) {  }
/* func_002F65E0 */
u32 func_002F65E0(void) { return 0; }
/* func_002F65E8 */
void func_002F65E8(void) {  }
/* func_002F65F0 */
void func_002F65F0(void) {  }
/* func_002F65F8 */
void func_002F65F8(void) {  }
/* func_002F6600 */
void func_002F6600(void) {  }
/* func_002F6608 */
/* asm: pure tail jump (j func_002EA028): an x86 jmp keeps every argument register, stack argument and float
   exactly as the caller left them (a C wrapper re-passing 8 args lost stack/float args: black 3D) */
__asm__(".text\n.globl func_002F6608\n.type func_002F6608, @function\nfunc_002F6608:\n\tjmp func_002EA028\n");
