#include "common.h"

void func_002EA050(s32 arg0);
s32 func_002F1ED0(s32 arg0);
s32 func_002F2D30(s32 arg0);
void func_002F32C0(s32 arg0);
extern u8 D_0037C060[] __attribute__((section(".data")));

s32 func_002EC6E8(s32 arg0) {
    s32 v;

    if (arg0 == 0) {
        func_002EA050((s32)D_0037C060);
        return -3;
    }
    if (*(s32 *)(arg0 + 0xC) > 0xFFFFE) {
        func_002F32C0(*(s32 *)(arg0 + 0x4));
        if (func_002F1ED0(*(s32 *)(arg0 + 0x4)) == 4) {
            return -5;
        }
    }
    v = func_002F2D30(*(s32 *)(arg0 + 0x4));
    *(s32 *)(arg0 + 0xC) = v;
    return v;
}
