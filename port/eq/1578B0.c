#include "common.h"

s32 BtlCharApi_ObjGetParamFlags0(s32 arg0);
void func_0014EAE8(s32 arg0, s32 arg1);
/* GUESS arity: a0/a1 are not written before this call, passed through */
u8 *func_001F3758(s32 arg0, s32 arg1);
s32 func_0020B3D0(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001578B0(u8 *arg0, s32 *arg1) {
    s32 temp_s0;
    u8 *temp_s2;
    u8 *temp_v0;

    temp_s2 = (u8 *)*(s32 *)(arg0 + 0x38);
    temp_s0 = *(s32 *)(func_001F3758((s32)arg0, (s32)arg1) + 0x38);
    memset(temp_s2, 0, 0xF50);
    *(s32 *)(temp_s2 + 0xA0) = (s32)arg1;
    temp_v0 = (u8 *)*(s32 *)((u8 *)arg1 + 0x24);
    *(f32 *)(temp_s2 + 0x18) = *(f32 *)(temp_v0 + 8);
    *(f32 *)(temp_s2 + 0x1C) = *(f32 *)(temp_v0 + 4);
    func_0014EAE8(temp_s0, (s32)(temp_s2 + 0xA4));
    if (BtlCharApi_ObjGetParamFlags0(func_0020B3D0(*(s32 *)(temp_s2 + 0xA0))) & 0x80) {
        *(s32 *)temp_s2 = *(s32 *)temp_s2 | 0x100;
    }
}
