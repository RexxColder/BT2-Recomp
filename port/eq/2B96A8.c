#include "common.h"

void IVec3_Set(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002B56A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002B96A8(s32 arg0, s32 arg1) {
    s32 sp[6];
    u8 *src;
    u8 *dst;
    u32 s1;
    s32 t1;
    s32 half;

    src = (u8 *)arg0;
    dst = (u8 *)arg1;
    s1 = *(u32 *)(src + 0x10);
    t1 = *(s32 *)(src + 0xC);
    *(s32 *)(dst + 0x44) = t1;
    *(u32 *)(dst + 0x48) = s1;
    if (*(s32 *)(src + 8) != 3) {
        IVec3_Set((s32)(dst + 4), *(s32 *)src, t1, (s32)s1);
        return;
    }
    func_002B56A0(*(s32 *)src, t1, (s32)s1, (s32)sp);
    half = (s32)(s1 + (s1 >> 0x1F)) >> 1;
    IVec3_Set((s32)(dst + 4), sp[0], sp[3], (s32)s1);
    IVec3_Set((s32)(dst + 0x14), sp[1], sp[4], half);
    IVec3_Set((s32)(dst + 0x24), sp[2], sp[5], half);
}
