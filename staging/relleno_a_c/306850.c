#include "common.h"

void func_002FCFE8(void);
extern s32 D_003658E4 __attribute__((section(".data")));

/* 0x00306850: Init con contador: la primera vez (D_003658E4 == 0) llama a func_002FCFE8 (bind del RPC);
 * siempre D_003658E4++. (El lw de D_003658E0 no se usa.) */
void func_00306850(void) {
    if (D_003658E4 == 0) {
        func_002FCFE8();
    }
    D_003658E4 += 1;
}
