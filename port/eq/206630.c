#include "common.h"

extern f32 D_0038594C;

void *BtlChar_GetPos(u8 *chr);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_00211328(u8 *a0, s32 a1, s32 a2);
s32 EftWater_GetSurfaceY(f32 *out);
void func_0013B458(u8 *a0, f32 *a1, s32 a2, f32 f12);
s32 func_0013B370(u8 *a0, s32 a1);
void func_0012F208(u8 *a0);
void func_0020FC38(u8 *a0, s32 a1);
f32 sqrtf(f32 x);
f32 fabsf(f32 x);

s32 func_00206630(u8 *arg0) {
    f32 sp[8];
    s32 s0;
    s32 s2;
    s32 r2;
    s32 r3;
    s32 r5;
    s32 r6;
    u8 *p;
    u8 *pa;
    u8 *pb;
    f32 f20;
    f32 f0;
    f32 sum;
    f32 dist;

    s2 = 0;
    s0 = func_00211310(arg0, 0, 0x100);
    r2 = func_00211328(arg0, 0, 0x100);
    s0 = (s0 ^ r2) & 0xFF;

    if (s0 == 1) {
        r3 = func_00211310(arg0, 1, 0x20000);
        if (r3 == 0 && EftWater_GetSurfaceY(&sp[4]) != 0) {
            p = BtlChar_GetPos(arg0);
            sp[1] = sp[4];
            sp[0] = *(f32 *)p;
            p = BtlChar_GetPos(arg0);
            sp[2] = *(f32 *)(p + 0x8);
            sp[3] = 1.0f;
            p = BtlChar_GetPos(arg0);
            func_0013B458(*(u8 **)(arg0 + 0x1534), sp, 0, *(f32 *)(p + 0x54));

            if (func_00211310(arg0, 0, 0x100) == 0) {
                func_0020FC38(arg0, 0x3B);
            } else {
                func_0020FC38(arg0, 0x3A);
            }
            r5 = func_00211310(arg0, 0, 0x100);
            if (r5 != 0) {
                func_0012F208(*(u8 **)(arg0 + 0x1534));
            }
        }
    }

    r6 = func_00211310(arg0, 0, 0x200);
    if (r6 != 0) {
        pa = BtlChar_GetPos(arg0);
        pb = BtlChar_GetPos(arg0);
        f20 = *(f32 *)(pa + 0x50) * *(f32 *)(pa + 0x50);
        f0 = *(f32 *)(pb + 0x58) * *(f32 *)(pb + 0x58);
        sum = f20 + f0;
        dist = sqrtf(fabsf(sum));
        if (dist != dist) {
            dist = sqrtf(sum);
        }
        if (D_0038594C < dist) {
            s2 = 1;
        }
    }

    if (s2 == 0) {
        /* a0 = *(arg0+0x1534): delay slot (lw $a0,0x1534($s1)) of the beqz at 0x1067B8 runs on both paths */
        return func_0013B370(*(u8 **)(arg0 + 0x1534), 1);
    }
    return func_0013B370(*(u8 **)(arg0 + 0x1534), 0);
}
