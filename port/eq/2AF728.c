#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
f32 cosf(f32 arg0);
f32 sinf(f32 arg0);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_00312650(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00312680(f32 farg0, u8 *arg1, u8 *arg2);
f32 sceVu0InnerProduct(u8 *arg0, u8 *arg1);
extern f32 D_0038747C;

void func_002AF728(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x80];
    f32 f20;
    f32 sinv;
    f32 cosv;
    f32 cos0;
    f32 t;
    f32 v;
    f32 res1;
    f32 res2;
    f32 tmp;

    func_00208DE8(*(s32 *)(arg0 + 0x4), sp + 0x10, 0x30);
    f20 = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x8)) * D_0038747C;
    sinv = sinf(*(f32 *)(arg2 + 0x4));
    cosv = cosf(*(f32 *)(arg2 + 0x4));
    *(f32 *)(sp + 0x20) = sinv;
    *(s32 *)(sp + 0x24) = 0;
    *(f32 *)(sp + 0x28) = cosv;
    *(s32 *)(sp + 0x2C) = 0;
    *(f32 *)(sp + 0x00) = sinv;
    *(s32 *)(sp + 0x04) = *(s32 *)(sp + 0x24);
    *(f32 *)(sp + 0x08) = cosv;
    res1 = sceVu0InnerProduct(sp + 0x20, sp + 0x10);
    t = -res1;
    *(f32 *)(sp + 0x0C) = t;
    cos0 = cosf(*(f32 *)(arg2 + 0x0));
    v = (t + f20 * (cos0 + 1.0f)) + 10.0f;
    *(f32 *)(sp + 0x0C) = v;
    res2 = sceVu0InnerProduct(sp, arg1);
    tmp = res2 + v;
    if (0.0f < tmp) {
        func_00312680(tmp, sp + 0x30, sp);
        func_00312650(arg1, arg1, sp + 0x30);
        *(f32 *)(arg1 + 0xC) = 1.0f;
    }
}
