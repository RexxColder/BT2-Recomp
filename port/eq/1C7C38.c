#include "common.h"

void Vec4_Set(void *out, f32 x, f32 y, f32 z, f32 w);
void Vu0Screen_StoreMtx(void *m);
void func_001C85F8(void *a0, s32 a1);
void func_001C7F20(s32 a0, s32 a1, void *a2, void *a3, void *t0, void *t1, s32 t2, s32 t3, s32 st0, s32 st1);
extern s32 D_003878AC;

void func_001C7C38(void *arg0) {
    u8 frame[0x80];
    u8 *p;
    u8 *s0;
    u8 *s2;
    u8 *mtx;
    u8 *sp50;
    u8 *sp60;
    u8 *sp70;
    f32 f20;
    f32 f21;
    f32 f0;
    s32 n;
    s32 i;
    s32 s4;

    p = (u8 *)arg0;
    mtx = frame + 0x10;
    sp50 = frame + 0x50;
    sp60 = frame + 0x60;
    sp70 = frame + 0x70;
    f20 = 0.984375f;
    f21 = 0.015625f;

    func_001C85F8(sp70, *(s32 *)(p + 0x380));
    f0 = *(f32 *)(p + 0x3C0);
    Vec4_Set(sp70, 128.0f, 128.0f, 128.0f, f0);
    Vu0Screen_StoreMtx(mtx);
    n = *(s32 *)(p + 0x390);
    if (n - 1 > 0) {
        i = 0;
        s0 = p;
        do {
            s2 = s0 + 0x50;
            if (i != 0 && i != n - 2) {
                s4 = 7;
            } else {
                s4 = 0;
            }
            if (i == n - 2) {
                Vec4_Set(sp50, f21, f21, f21, f20);
                Vec4_Set(sp60, f20, f21, f20, f20);
            } else {
                Vec4_Set(sp50, f20, f21, f20, f20);
                Vec4_Set(sp60, f21, f21, f21, f20);
            }
            func_001C7F20((s32)s0, (s32)s2, mtx, sp50, sp60, sp70, 0, D_003878AC, s4,
                          *(s32 *)(p + 0x380));
            n = *(s32 *)(p + 0x390);
            i += 1;
            s0 += 0x50;
        } while (i < n - 1);
    }
}
