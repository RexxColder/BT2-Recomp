#include "common.h"

extern f32 D_003848E0;
extern f32 D_003848E4;

f32 sqrtf(f32 farg0);
s32 func_0020B3D0(s32 arg0);
s32 func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_00129B58(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_00129CD8(u8 *arg0, u8 *arg1);

void func_001725F8(u8 *arg0) {
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
    r = sqrtf(func_00129CD8(s0, s0));
    *(f32 *)(s3 + 0xAA0) = r;
    if (700.0f < r) {
        *(f32 *)(s3 + 0xAA0) = 700.0f;
    }
    *(f32 *)(s3 + 0xAA8) = D_003848E0;
    *(f32 *)(s3 + 0xAA4) = D_003848E4;
}
