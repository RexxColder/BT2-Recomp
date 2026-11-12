#include "common.h"

s32 func_00126528(s32 arg0);
void BtlTask_SetDead(u8 *arg0);
void func_001ABF78(u8 *arg0);
void func_001ACA98(u8 *arg0);
void func_001AD1F8(u8 *arg0);

void func_001AC650(u8 *arg0) {
    u8 *s1;
    u8 mode;
    s32 v;
    s32 flags;

    s1 = *(u8 **)(arg0 + 0x38);
    if (func_00126528((s32)arg0) != 0) {
        return;
    }
    mode = *(u8 *)(s1 + 0x1A);
    if (mode == 0xE) {
        func_001AD1F8(arg0);
    } else if (mode == 0xF) {
        func_001ACA98(arg0);
    }
    flags = *(s32 *)(s1 + 0xC0);
    v = flags & 0x8;
    if (flags & 0x80) {
        func_001ABF78(arg0);
        v = *(s32 *)(s1 + 0xC0) & 0x8;
    }
    if (v != 0) {
        BtlTask_SetDead(arg0);
    }
}
