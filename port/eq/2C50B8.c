#include "common.h"

s32 BtlCharApi_GetOpponentObjId(void);
void func_002C2FF0(s32 arg0, s32 arg1, void *arg2);
void func_002C5180(void *arg0);
void func_002C5270(s32 arg0);
s32 func_002DCAF0(s32 arg0, void *arg1, void *arg2);
extern s32 func_002C5208 __attribute__((section(".data")));

void func_002C50B8(u8 *arg0) {
    u8 *s2;
    s32 temp_v0;

    s2 = arg0 + 0x2198;
    *(u8 **)(arg0 + 0x1F7C) = s2;
    func_002C5180(s2);
    temp_v0 = BtlCharApi_GetOpponentObjId();
    if (temp_v0 == 0) {
        func_002C2FF0(0, 0xFF000D08, arg0);
        return;
    }
    if (func_002DCAF0(temp_v0, (void *)&func_002C5208, arg0) != 0) {
        func_002C5270(temp_v0);
        ((void (*)(s32, s32))func_002C2FF0)(0, 0xFF000D09);
        return;
    }
    *(s32 *)s2 = temp_v0;
}
