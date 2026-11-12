#include "common.h"

s32 Rand_Range(s32 arg0, s32 arg1);
void func_002B3190(s32 arg0);
void func_002B6D10(s32 arg0);
void func_002B7138(s32 arg0);
s32 func_002B8280(s32 arg0, s32 arg1, s32 arg2);
void func_002BD380();
s32 func_00303D48(s32 arg0, s32 arg1);
extern s32 D_00378BC8 __attribute__((section(".data")));
extern s32 D_00378BF8 __attribute__((section(".data")));

void func_002B6FA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 tmp;
    s32 v;

    if (func_002B8280(arg0, arg1, arg2) != 1) {
        Rand_Range((s32)&D_00378BC8, 2);
        return;
    }
    if (*(s32 *)(arg0 + 8) == 2) {
        Rand_Range((s32)&D_00378BF8, 2);
        return;
    }
    func_002BD380(1, 2);
    func_002B7138(arg0);
    tmp = *(s32 *)(arg0 + 0x1E0);
    ((void (*)(s32))(*(s32 *)(*(s32 *)tmp + 0xC)))(tmp);
    v = func_00303D48(arg1, arg2);
    *(s32 *)(arg0 + 0x1E4) = arg1;
    *(s32 *)(arg0 + 0x1BC) = v;
    *(s32 *)(arg0 + 0x1E0) = v;
    *(s32 *)(arg0 + 0x1E8) = arg2;
    func_002B6D10(arg0);
    func_002BD380(0);
    func_002B3190(arg0);
}
