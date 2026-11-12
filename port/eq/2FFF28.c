#include "common.h"

void func_002FFF90(void *arg0);
void func_003007F8(void *arg0);
extern u8 D_0037E918[];

void func_002FFF28(u8 *arg0) {
    s8 var_v0;

    if (arg0 == NULL) {
        func_003007F8(D_0037E918);
        return;
    }
    if (*(s8 *)(arg0 + 1) != 0) {
        func_002FFF90(arg0);
    }
    if (*(s32 *)(arg0 + 0x24) <= 0) {
        var_v0 = 1;
    } else {
        var_v0 = 2;
    }
    *(s8 *)(arg0 + 1) = var_v0;
}
