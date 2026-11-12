#include "m2c_macros.h"

void func_002EA050(void *arg0);
void func_002FFE88(s32 arg0);
extern u8 D_0037C480 __attribute__((section(".data")));

void func_002EDB90(void *arg0) {
    if (arg0 == NULL) {
        func_002EA050(&D_0037C480);
        return;
    }
    if (*(s8 *)((u8 *)arg0 + 1) == 0) {
        func_002FFE88(*(s32 *)((u8 *)arg0 + 0x94));
    }
}
