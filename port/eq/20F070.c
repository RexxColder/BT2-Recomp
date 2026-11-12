#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void func_001FC3B0(f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17,
                   s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                   s32 s9, s32 s10, s32 s11, s32 s12, s32 s13);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
u8 *func_00211288(s32 arg0);
void sceVu0InterVector(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_003859DC;
extern f32 D_003859E0;
extern u8 *D_00387930;

void func_0020F070(void) {
    s32 buf[28];
    u8 *s1;
    u8 *v;
    f32 f20;
    f32 fa;
    f32 fb;
    f32 f22;
    f32 f;

    s1 = D_00387930 + 0x60;
    f20 = D_003859DC;
    v = func_00211288(0);
    func_00208DE8(*(s32 *)(v + 0x1534), (s32)&buf[12], 3);
    v = func_00211288(1);
    func_00208DE8(*(s32 *)(v + 0x1534), (s32)&buf[16], 3);
    sceVu0InterVector((s32)&buf[20], (s32)&buf[12], (s32)&buf[16], 0.5f);

    fa = BtlCharApi_GetHeight(0) * f20;
    fb = BtlCharApi_GetHeight(1) * f20;
    f22 = (fb < fa) ? fa : fb;

    f = BtlUtil_WrapAngle(*(f32 *)(s1 + 8) + D_003859E0);
    *(f32 *)(s1 + 8) = f;
    v = func_00211288(0);
    func_001FC3B0(f, 0.0f, 0.0f, 0.0f, f22, 0.0f,
                  (s32)v, (s32)&buf[20], (s32)D_002C3630, (s32)&buf[12],
                  (s32)D_002C3630, (s32)&buf[20], (s32)D_002C3630,
                  -1, -1, -1, -1, 1, 0x47);
}
