#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void BtlTask_SetDead(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_001DC058(u8 *arg0) {
    u8 *s0;
    s32 v;
    s32 a0v;
    s32 a1v;
    s32 a2v;

    s0 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsCharStopped(*(s32 *)(s0 + 0x10)) != 0) {
        return;
    }
    v = *(s32 *)(s0 + 0x20) - 1;
    *(s32 *)(s0 + 0x20) = v;
    if (v > 0) {
        return;
    }
    a2v = *(s32 *)(s0 + 0x34);
    *(s32 *)(s0 + 0x20) = 0;
    a1v = *(s32 *)(s0 + 0x18);
    if (a2v < a1v) {
        a0v = *(s32 *)(s0 + 0x30);
        if (*(s32 *)(s0 + 0x1C) == 0 || a0v % *(s32 *)(s0 + 0x1C) == 0) {
            func_00297FE0(1, *(s32 *)(s0 + 0x14), 0x7F, 0x40, 0);
            *(s32 *)(s0 + 0x30) = 0;
            a0v = 0;
            a2v = *(s32 *)(s0 + 0x34) + 1;
            *(s32 *)(s0 + 0x34) = a2v;
            a1v = *(s32 *)(s0 + 0x18);
        }
        if (a2v < a1v) {
            *(s32 *)(s0 + 0x30) = a0v + 1;
            return;
        }
    } else {
        a0v = *(s32 *)(s0 + 0x30);
    }
    *(s32 *)(s0 + 0x30) = a0v + 1;
    if (a2v >= a1v) {
        BtlTask_SetDead(arg0, a1v, a2v);
    }
}
