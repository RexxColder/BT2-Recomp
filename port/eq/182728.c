#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void BtlTask_SetDead(void *arg0);
void func_00151FB0(void *arg0);
void func_00152260(s32 arg0, void *arg1);
void func_00152930(s32 arg0, void *arg1);
f32 func_00152958(void *arg0);
void func_00182198(void *arg0);
void func_00182380(void *arg0, s32 arg1, s32 arg2);

typedef void (*func_cb3)(void *, void *, s32);

void func_00182728(void *arg0) {
    u8 *p;
    u8 *t;
    u8 *s;
    u8 *u;
    s32 doblock7;
    f32 f0;
    u16 v16;
    func_cb3 cb;

    p = (u8 *)arg0;
    t = *(u8 **)(p + 0x38);
    s = t + 0xA00;
    u = *(u8 **)(s + 0x28);
    if (BtlScene_IsCharStopped(*(s32 *)u) != 0) {
        return;
    }
    *(s32 *)(t + 0xA8C) += 1;

    doblock7 = 1;
    if (!(s[0] & 8)) {
        func_00152260(*(s32 *)u, t + 0x7B0);
        func_00151FB0(t);
        if ((*(s64 *)(t + 0xA80) & 0x60) != 0x20) {
            doblock7 = 0;
        }
    } else {
        func_00151FB0(t);
    }
    if (doblock7) {
        cb = *(func_cb3 *)(s + 0x18);
        if (cb != NULL) {
            cb(s, t + 0xA30, *(s32 *)(t + 0xA84));
        }
        *(s32 *)(t + 0xA84) += 1;
    }

    if (*(s32 *)(t + 0xA8C) >= s[2]) {
        cb = *(func_cb3 *)(s + 0x1C);
        if (cb != NULL) {
            cb(s, t + 0xA88, *(s32 *)(t + 0xA84));
        } else {
            func_00152930(*(s32 *)(s + 0x24), t);
            f0 = func_00152958(t);
            *(f32 *)(t + 0xA88) = *(f32 *)(*(u8 **)(u + 0x24) + 4) * f0 * *(f32 *)(s + 8);
        }
        if (*(s32 *)(t + 0xA80) & 0x10) {
            func_00182198(p);
        }
    }
    if (!(s[0] & 8)) {
        func_00182380(p, *(s32 *)(s + 0x24), 0);
    }
    if (*(s32 *)(t + 0xA80) & 8) {
        BtlTask_SetDead(p);
    }
    if (*(s32 *)(t + 0xA8C) >= s[2]) {
        v16 = (u16)(*(u16 *)(s + 4) - 1);
        *(u16 *)(s + 4) = v16;
        if ((s32)((u32)v16 << 16) <= 0) {
            *(s32 *)(t + 0xA80) = *(s32 *)(t + 0xA80) | 2;
        }
    }
}
