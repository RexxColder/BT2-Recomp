#include "common.h"

s32 func_002113C0(u8 *obj, s32 a1, s32 a2, s32 a3);
void func_00206958(u8 *obj, s64 bits);
u8 *BtlChar_GetPos(u8 *obj);
f32 func_0023F010(u8 *obj);
void func_0020E4B0(f32 farg0, f32 farg1, u8 *obj);
s32 func_0023ED70(u8 *obj);
void func_00203888(u8 *obj, s32 a1, s32 a2);
s32 BtlMember_IsKiEmpty(u8 *obj);
s32 func_0023E520(u8 *obj);
s32 func_001FCF88(u8 *obj, s32 arg1);

/* 0x001FE9F0: (a, b) sets state flags on a and b, adds 30000 to a+0x9B4 (cap 100000), then finishes b via 1FCF88. */
s32 func_001FE9F0(u8 *a, u8 *b) {
    s32 v;
    u8 *pos;

    func_002113C0(a, 4, 0x1000, 1);
    func_002113C0(a, 5, 8, 0);
    func_002113C0(a, 5, 0x200, 1);
    v = *(s32 *)(a + 0x9B4) + 0x7530;
    *(s32 *)(a + 0x9B4) = v;
    if (100000 < v) {
        *(s32 *)(a + 0x9B4) = 100000;
    }
    func_002113C0(a, 0x10, 0x2000, 1);
    func_00206958(b, 0x1000000);
    pos = BtlChar_GetPos(a);
    func_0020E4B0(*(f32 *)(pos + 0xB4), func_0023F010(a), b);
    func_002113C0(b, 4, 0x2000, 1);
    func_00203888(b, func_0023ED70(a), 0);
    if (BtlMember_IsKiEmpty(b) != 0) {
        func_002113C0(b, 0, 0x4000, 1);
    }
    return func_001FCF88(b, func_0023E520(a));
}
