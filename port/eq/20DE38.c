#include "common.h"

u8 *BtlChar_GetPos(s32 arg0);
void Quat_FromAxisAngle(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void *memset(void *dst, s32 c, u32 n);

void func_0020DE38(u8 *arg0) {
    f32 sp[4];
    u8 *pos;

    memset(sp, 0, 0x10);
    sp[0] = 1.0f;
    pos = BtlChar_GetPos((s32)arg0);
    Quat_FromAxisAngle(*(s32 *)(arg0 + 0x1530) + 0xD20, sp[0], sp[1], sp[2], -*(f32 *)(pos + 0xD4));
}
