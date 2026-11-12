#include "common.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlChar_GetPos(s32 arg0);
void func_00206958(s32 arg0, s32 arg1);
f32 func_0023F010(s32 arg0);
void func_0020E4B0(s32 arg0, f32 farg0, f32 farg1);
s32 func_0023ED70(s32 arg0);
s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
s32 BtlMember_IsKiEmpty(s32 arg0);
s32 func_0023E520(s32 arg0);
void func_001FCF88(s32 arg0, s32 arg1);

/* battle setup for one fighter (arg0) and its member (arg1): flag calls, the +0x9B4 counter raised by 0x7530 and
 * capped at 0x186A0, then the tail call func_001FCF88(arg1, func_0023E520(arg0)) */
void func_001FE9F0(s32 arg0, s32 arg1) {
    s32 s0;
    func_002113C0(arg0, 4, 0x1000, 1);
    func_002113C0(arg0, 5, 8, 0);
    func_002113C0(arg0, 5, 0x200, 1);
    {
        s32 v = *(s32 *)((u8 *)arg0 + 0x9B4) + 0x7530;
        *(s32 *)((u8 *)arg0 + 0x9B4) = v;
        if (v > 0x186A0) {
            *(s32 *)((u8 *)arg0 + 0x9B4) = 0x186A0;
        }
    }
    func_002113C0(arg0, 0x10, 0x2000, 1);
    func_00206958(arg1, 0x01000000);
    s0 = BtlChar_GetPos(arg0);
    {
        f32 f = func_0023F010(arg0);
        func_0020E4B0(arg1, *(f32 *)((u8 *)s0 + 0xB4), f);
    }
    func_002113C0(arg1, 4, 0x2000, 1);
    {
        s32 v = func_0023ED70(arg0);
        func_00203888(arg1, v, 0);
    }
    if (BtlMember_IsKiEmpty(arg1) != 0) {
        func_002113C0(arg1, 0, 0x4000, 1);
    }
    func_001FCF88(arg1, func_0023E520(arg0));
}
