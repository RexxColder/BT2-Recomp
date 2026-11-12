#include "common.h"

s32 func_001F3758(s32 arg0);
s32 func_0020B3D0(s32 arg0);
s32 EftShot_GetAttrKind(s32 arg0, u64 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void Vec3_Sub(s32 dst, s32 a, s32 b);
s32 Vec3_Normalize(s32 arg0, s32 arg1);
s32 func_00191600(s32 arg0, s32 arg1);
s32 func_001918F8(s32 arg0, s32 arg1);

/* Builds one blast object: the source/target vectors (or a 16-byte copy when flag is set),
   a six-word parameter block, then creates the object into the next slot of the shot list
   and bumps the list count. Returns func_001918F8's result. */
s32 func_0016DB58(u8 *self, s32 arg1, s32 arg2, s32 arg3, s32 flag, f32 fa, f32 fb, f32 fc) {
    u8 fr[0xb0];   /* tamano de locales del original (antes 0x70) */
    u8 *pobj;
    u8 *cur;
    u8 *ptr_s4;
    s32 s6;
    s32 s5;
    s32 count;
    s32 attr_kind;
    u8 *slot;
    u8 *v24;
    s32 blast;
    s32 result;

    pobj = (u8 *)func_001F3758((s32)self);
    cur = *(u8 **)(self + 0x38);
    s6 = *(s32 *)(pobj + 0x38);
    ptr_s4 = *(u8 **)(cur + 0xB0);
    s5 = func_0020B3D0(*(s32 *)ptr_s4);

    count = *(s32 *)(cur + 0xAB0);
    slot = cur + 0xAC0 + 48 * count;
    attr_kind = EftShot_GetAttrKind(*(s32 *)ptr_s4, arg1);
    func_00208DE8(*(s32 *)ptr_s4, (s32)(fr + 0x20), attr_kind);

    if (flag != 0) {
        func_00129C28((s32)(fr + 0x30), (s32)(cur + 0x30));
        v24 = cur + 0x860;
    } else {
        func_00208DE8(*(s32 *)ptr_s4, (s32)fr, 17);
        func_00208DE8(s5, (s32)(fr + 0x10), 3);
        Vec3_Sub((s32)(fr + 0x30), (s32)(fr + 0x10), (s32)fr);
        if (**(s32 **)(ptr_s4 + 0x20) == 167) {
            *(s32 *)(fr + 0x34) = 0;
        }
        Vec3_Normalize((s32)(fr + 0x30), (s32)(fr + 0x30));
        *(f32 *)(fr + 0x3C) = 1.0f;
        v24 = cur + 0x860;
    }

    *(s32 *)(fr + 0x40) = (s32)ptr_s4;
    *(s32 *)(fr + 0x44) = s6;
    *(s32 *)(fr + 0x48) = (s32)v24;
    *(s32 *)(fr + 0x4C) = (s32)(fr + 0x20);
    *(s32 *)(fr + 0x50) = (s32)(fr + 0x30);
    *(s32 *)(fr + 0x54) = *(s32 *)(cur + 0xAB0);
    *(s32 *)(fr + 0x58) = 14;
    *(s32 *)(fr + 0x5C) = arg2;
    *(s32 *)(fr + 0x60) = arg3;
    *(f32 *)(fr + 0x64) = fa;
    *(f32 *)(fr + 0x68) = fb;
    *(f32 *)(fr + 0x6C) = fc;

    blast = func_00191600((s32)(fr + 0x40), (s32)(fr + 0x40));
    *(s32 *)(slot + 0x20) = blast;
    result = func_001918F8(blast, 1);
    *(s32 *)(cur + 0xAB0) = *(s32 *)(cur + 0xAB0) + 1;
    return result;
}
