#include "common.h"

extern f32 D_003846BC;
extern f32 D_003846C0;

f32 sqrtf(f32 farg0);
s32 func_0020B3D0(s32 arg0);
s32 func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_00129B58(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_00129CD8(u8 *arg0, u8 *arg1);

/* EftSweep_InitPath (BT3 name, same semantics): radius = |owner node - opponent node| + 50, clamped to 800. */
void EftSweep_InitPath(u8 *arg0) {
    u8 buf[0x20];
    u8 *s0 = buf + 0x10;
    u8 *s3 = *(u8 **)(arg0 + 0x38);
    u8 *s1 = *(u8 **)(s3 + 0xA0);
    s32 s2;
    f32 r;

    s2 = func_0020B3D0(*(s32 *)(s1 + 0));
    func_00208DE8(*(s32 *)(s1 + 0), s0, 3);
    func_00208DE8(s2, buf, 3);
    func_00129B58(s0, buf, s0);
    r = sqrtf(func_00129CD8(s0, s0)) + 50.0f;
    *(f32 *)(s3 + 0xAA0) = r;
    if (800.0f < r) {
        *(f32 *)(s3 + 0xAA0) = 800.0f;
    }
    *(f32 *)(s3 + 0xAA8) = D_003846BC;
    *(f32 *)(s3 + 0xAA4) = D_003846C0;
}
