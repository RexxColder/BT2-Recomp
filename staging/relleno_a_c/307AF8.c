#include "common.h"

void func_00307A50(void);
extern s32 D_0036645C __attribute__((section(".data")));

/* 0x00307AF8: Init con contador: la primera vez (D_0036645C == 0) llama a func_00307A50; siempre D_0036645C++. */
void func_00307AF8(void) {
    if (D_0036645C == 0) {
        func_00307A50();
    }
    D_0036645C += 1;
}
