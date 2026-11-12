#include "common.h"

f32 Stg_CalcYaw(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_00260A50(s32 arg0);
void memset(void *arg0, s32 arg1, u32 arg2);

void func_002A98A8(u8 *arg0, u8 *arg1) {
    f32 sp[4];
    f32 yaw;
    u8 *s1;

    s1 = arg0 + 0x9A0;
    memset(sp, 0, 0x10);
    yaw = Stg_CalcYaw(*(f32 *)(arg0 + 0x9A0), *(f32 *)(arg0 + 0x9A8),
                      *(f32 *)(arg1 + 0x9A0), *(f32 *)(arg1 + 0x9A8));
    *(f32 *)(s1 + 0x10) = sp[0];
    *(f32 *)(s1 + 0x18) = sp[2];
    *(f32 *)(s1 + 0x14) = yaw;
    func_00260A50((s32)arg0);
}
