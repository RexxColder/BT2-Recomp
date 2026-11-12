#include "m2c_macros.h"

extern s32 func_00129C28(s32 arg0, s32 arg1);
extern void func_00129C38(s32 arg0, s32 arg1);
extern void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
extern void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
extern void sceVu0DivVectorXYZ(f32 farg0, s32 arg1, s32 arg2);

void func_001C5130(s32 unused_a0, s32 arg1, u8 *arg2, s32 arg3) {
    s32 sp[4];
    s32 sp10[4];
    u8 *s0;
    u8 *s3;
    u8 *s5;
    u8 *s6;
    u8 *next;
    s32 s2;

    s2 = 0;
    s3 = arg2 + 0x90;
    s6 = (u8 *)arg1;
    func_00129C28((s32)sp, arg3 + 0x10);
    Vec3_Sub((s32)sp10, (s32)s3, (s32)sp);
    sceVu0DivVectorXYZ((f32)*(s32 *)(arg2 + 0x64), (s32)sp10, (s32)sp10);
    s0 = *(u8 **)arg2;
    if (s0 == NULL) {
        return;
    }
    s5 = arg2 + 0xA0;
    do {
        func_00129C38((s32)(s0 + 0x10), (s32)sp);
        if (s2 != 0) {
            if (s2 >= *(s32 *)(arg2 + 0x64) - 2) {
                *(s8 *)(s0 + 4) = 2;
            } else {
                *(s8 *)(s0 + 4) = 1;
            }
        } else {
            *(s8 *)(s0 + 4) = 0;
        }
        func_00129C28((s32)(s0 + 0x20), (s32)s5);
        if (*(s32 *)(arg2 + 0x50) & 0x10) {
            func_00129C28((s32)(s0 + 0x30), (s32)(s6 + 0x10));
            if (s2 == 0 || *(u8 **)(s0 + 0x40) == NULL) {
                *(s32 *)(s0 + 0x3C) = 0;
            }
        }
        if (s2 < *(s32 *)(arg2 + 0x64) - 2) {
            Vec3_Add((s32)sp, (s32)sp, (s32)sp10);
        } else {
            func_00129C38((s32)sp, (s32)s3);
        }
        next = *(u8 **)(s0 + 0x40);
        s2 += 1;
        s0 = next;
    } while (next != NULL);
}
