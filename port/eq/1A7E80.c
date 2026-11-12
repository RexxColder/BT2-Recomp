#include "common.h"

s32 func_00126560();
void func_00129C28(s32 arg0, s32 arg1);
f32 func_001A8018(s32 arg0);
void func_001A8418(s32 arg0, s64 arg1, s64 arg2, s64 arg3);
void memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *gEftStruggle;

void func_001A7E80(s32 arg0, s32 arg1) {
    u8 *e;
    u8 *p;
    u8 *q;
    s64 c1;
    s64 c2;
    s64 c3;
    f32 var;
    f32 temp;

    e = *(u8 **)(arg0 + 0x38);
    memset(e, 0, 0x390);
    p = (u8 *)arg1;
    q = e + 0x40;
    do {
        s64 c0 = *(s64 *)(p + 0x00);
        c1 = *(s64 *)(p + 0x08);
        c2 = *(s64 *)(p + 0x10);
        c3 = *(s64 *)(p + 0x18);
        *(s64 *)(q + 0x00) = c0;
        *(s64 *)(q + 0x08) = c1;
        *(s64 *)(q + 0x10) = c2;
        *(s64 *)(q + 0x18) = c3;
        p += 0x20;
        q += 0x20;
    } while (p != (u8 *)arg1 + 0x320);
    func_001A8418(arg0, c1, c2, c3);
    *(f32 *)(e + 0x20) = *(f32 *)(e + 0x50);
    if (func_00126560() != 0) {
        func_00129C28((s32)e, (s32)(e + 0x40));
    }
    if (func_00126560() == 0) {
        var = func_001A8018((s32)(e + 0x60));
        temp = func_001A8018((s32)(e + 0x1E0));
        if (!(temp < var)) {
            var = temp;
        }
        if (var < 0.0f) {
            var = 0.0f;
        }
        *(f32 *)(gEftStruggle + 0x630) = var;
    }
}
