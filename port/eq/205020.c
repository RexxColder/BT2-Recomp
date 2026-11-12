#include "common.h"

f32 func_0026A220(s32 arg0);
void func_001D0EB0(s32 arg0, s32 arg1, f32 farg0);
void func_001D0F38(s32 arg0, s32 arg1, f32 farg0);
void func_001D0FC0(s32 arg0, void *arg1, s32 arg2, f32 farg0);
void func_001D1C78(s32 arg0, void *arg1, s32 arg2, f32 farg0);
void func_001D1B30(s32 arg0, f32 farg0);
s32 func_001D0BA8(void *arg0, f32 farg0, f32 farg1);
s32 EftWater_GetSurfaceY(void *arg0);
s32 func_00208DE8(s32 arg0, void *arg1, s32 arg2);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);

s32 func_00205020(s32 arg0) {
    u8 *a;
    u8 fr[0x40];
    f32 f20;
    u64 cur;
    u64 prev;
    u64 pressed;
    u64 released;
    s32 cfg;
    s32 obj;
    s32 s2;
    s32 pos;
    f32 h;
    f32 h2;

    a = (u8 *)arg0;
    f20 = func_0026A220(*(s32 *)(a + 0x1530));
    cfg = *(s32 *)(a + 0x1530);
    if ((*(u32 *)((u8 *)cfg + 0xE80) & 0x30000065u) != 0) {
        *(u64 *)(a + 0x338) &= 0xFFFFFF00FFFFFFFFULL;
    }

    cur = *(u64 *)(a + 0x338);
    prev = *(u64 *)(a + 0x400);
    pressed = cur & ~prev;
    released = prev & ~cur;
    obj = *(s32 *)(a + 0x1534);

    if (pressed & 0x200000000ULL) {
        func_001D0EB0(obj, 0, f20);
    }
    if (released & 0x200000000ULL) {
        func_001D0EB0(obj, 1, f20);
    }
    if (pressed & 0x1000000000ULL) {
        func_001D0F38(obj, 0, f20);
    }
    if (released & 0x1000000000ULL) {
        func_001D0F38(obj, 1, f20);
    }
    if (cur & 0x2000000000ULL) {
        func_001D0FC0(obj, (void *)((u8 *)cfg + 0xE60), 2, f20);
    }

    if (cur & 0x4000000000ULL) {
        *(f32 *)(fr + 0x20) = 0.0f;
        s2 = 0;
        if (EftWater_GetSurfaceY(fr + 0x20) != 0) {
            if (*(f32 *)(fr + 0x20) < *(f32 *)((u8 *)cfg + 0xE64)) {
                s2 = 1;
            }
        }
        if (s2 != 0) {
            func_001D0FC0(obj, (void *)((u8 *)cfg + 0xE60), 2, f20);
        } else {
            pos = BtlChar_GetPos(arg0);
            func_001D1C78(pos, (void *)((u8 *)cfg + 0xE60), obj, f20);
        }
    }

    if (pressed & 0x400000000ULL) {
        func_001D1B30(obj, f20);
    }

    if (cur & 0x800000000ULL) {
        func_00208DE8(obj, fr, 15);
        *(f32 *)(fr + 4) = *(f32 *)((u8 *)cfg + 0xE64);
        func_00208DE8(obj, fr + 0x10, 11);
        *(f32 *)(fr + 0x14) = *(f32 *)((u8 *)cfg + 0xE64);
        h = BtlCharApi_GetHeight(obj);
        func_001D0BA8(fr, h, f20);
        h2 = BtlCharApi_GetHeight(obj);
        return func_001D0BA8(fr + 0x10, h2, f20);
    }
    return 0;
}
