#include "common.h"

s32 func_002113C0(u8 *obj, s32 a1, s32 a2, s32 a3);
u8 *BtlObjXf_Update(u8 *obj);
u32 func_001FA3A8(u8 *arg0);
u8 *func_00212320(u8 *obj);
s32 func_00241250(u8 *obj, u8 *arg1);
u32 func_002411E0(u8 *obj, u8 *arg1);
void func_00203C88(u8 *obj, s64 bits);
s32 func_00203C58(u8 *obj, s64 bits);
s32 func_00211310(u8 *obj, s32 a1, s32 a2);

/* 0x00236310: battle object state setup; clears 3 flag bits, optionally sets a flag in the owner (obj+0x1530). */
void func_00236310(u8 *obj) {
    u8 *own;

    func_002113C0(obj, 12, 0x1000, 0);
    func_002113C0(obj, 12, 0x2000, 0);
    func_002113C0(obj, 12, 0x4000, 0);
    if ((func_001FA3A8(BtlObjXf_Update(obj)) & 0x10) != 0) {
        return;
    }
    *(s32 *)(obj + 0xA34) = func_00241250(obj, func_00212320(obj));
    *(s32 *)(obj + 0x1510) = 0;
    func_00203C88(obj, 0x8000000);
    if (func_00203C58(obj, 0x10000000) != 0) {
        func_002113C0(obj, 0, 0x4000, 1);
    }
    if ((func_002411E0(obj, func_00212320(obj)) & 0x20000) == 0) {
        return;
    }
    if (func_00211310(obj, 8, 1) != 0) {
        return;
    }
    own = *(u8 **)(obj + 0x1530);
    *(u32 *)(own + 0xAF0) &= 0xFF00FFFF;
    own = *(u8 **)(obj + 0x1530);
    *(u32 *)(own + 0xAF0) |= 0x10000;
}
