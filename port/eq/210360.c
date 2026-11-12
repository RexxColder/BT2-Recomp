#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 BtlChar_GetPos(s32 arg0, s32 arg1, s32 arg2);
void func_0020FAD0(s32 arg0, void *arg1, void *arg2, f32 farg0, f32 farg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern f32 D_00385A04;

void func_00210360(s32 arg0) {
    s32 sp[2];
    u8 *base;
    s32 s0;
    s32 s2;
    s32 v0;
    s32 pos;

    v0 = func_001FA3A8(BtlObjXf_Update(arg0));
    s2 = -1;
    if (v0 & 0x20000000) {
        s2 = 0x25;
    }
    if (v0 & 0x40000000) {
        s2 = 0x29;
    }
    if (s2 >= 0) {
        base = (u8 *)arg0;
        s0 = *(s32 *)(base + 0x1534);
        pos = BtlChar_GetPos(arg0, 0x25, 0x40000000);
        s0 = s0 + 3;
        func_0020FAD0(pos, sp, &sp[1], 200.0f, D_00385A04);
        v0 = *(s32 *)(base + 0x36C);
        if (v0 >= 0) {
            func_00297FE0(s0, s2 + v0, sp[0], sp[1], 0);
        }
    }
}
