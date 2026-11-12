#include "common.h"

void Mtx_StoreIdentity(s32 arg0);
void Vec3_Cross(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129C38(s32 arg0, s32 arg1);

void func_001A3928(void *arg0, s32 arg1, void *arg2, void *arg3) {
    f32 sp[4];
    f32 sp10[4];
    f32 sp20[4];
    u8 *out;

    out = (u8 *)arg0;

    func_00129C38((s32)sp20, arg1);
    sp20[3] = 1.0f;
    Vec3_Normalize((s32)sp20, (s32)sp20);
    func_00129C38((s32)sp, (s32)arg2);
    sp[3] = 1.0f;
    Vec3_Normalize((s32)sp, (s32)sp);
    Vec3_Cross((s32)sp10, (s32)sp20, (s32)sp);
    Vec3_Normalize((s32)sp10, (s32)sp10);
    Mtx_StoreIdentity((s32)out);

    *(f32 *)(out + 0x00) = sp[0];
    *(f32 *)(out + 0x10) = sp10[0];
    *(f32 *)(out + 0x20) = sp20[0];
    *(f32 *)(out + 0x04) = sp[1];
    *(f32 *)(out + 0x14) = sp10[1];
    *(f32 *)(out + 0x24) = sp20[1];
    *(f32 *)(out + 0x08) = sp[2];
    *(f32 *)(out + 0x18) = sp10[2];
    *(f32 *)(out + 0x28) = sp20[2];
    *(f32 *)(out + 0x30) = *(f32 *)((u8 *)arg3 + 0x00);
    *(f32 *)(out + 0x34) = *(f32 *)((u8 *)arg3 + 0x04);
    *(f32 *)(out + 0x38) = *(f32 *)((u8 *)arg3 + 0x08);
}
