#include "common.h"

s32 func_00240FA0(u8 *arg0, s32 arg1, s32 arg2);
u8 *BtlChar_GetPos(u8 *arg0);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
void func_00312680(u8 *arg0, u8 *arg1, f32 farg0);
void func_0026A2B0(u8 *arg0, f32 *arg1, f32 farg0);

void func_002310B8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 v;
    s32 flag = 0;
    u8 *pos;
    f32 sp[4];

    v = func_00240FA0(arg0, arg1, arg2);
    if ((u32)v < 8) {
        switch (v) {
        case 0:
        case 7:
            flag = 1;
            break;
        case 1:
        case 2:
        case 3:
        case 6:
            flag = (arg2 == 0);
            break;
        default:
            break;
        }
    }
    if (flag == 0) {
        return;
    }
    pos = BtlChar_GetPos(arg0);
    sp[0] = -sinf(*(f32 *)(pos + 0x14));
    sp[1] = 0.0f;
    pos = BtlChar_GetPos(arg0);
    sp[2] = -cosf(*(f32 *)(pos + 0x14));
    func_00312680((u8 *)sp, (u8 *)sp, 0.5f);
    func_0026A2B0(*(u8 **)(arg0 + 0x1530), sp, 4.0f);
}
