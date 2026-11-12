#include "common.h"

u8 *BtlChar_GetPos(s32 arg0);
f32 cosf(f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
f32 sceVu0InnerProduct(s32 arg0, s32 arg1);
extern f32 D_00385B2C;
extern f32 D_00385B30;

s32 func_002183F0(u8 *arg0, s32 arg1, f32 farg0) {
    s32 sp[4];
    f32 f22;
    f32 f21;
    f32 f0;
    f32 f20;
    f32 ip;
    s32 s0;
    s32 s2;
    s32 s3;
    u8 *a1p;
    s32 v1;

    f22 = D_00385B2C;
    f21 = farg0;
    s3 = arg1 & 0xFF;

    for (s2 = 0; s2 < 2; s2++) {
        s0 = 0;
        if (s2 == 0) {
            if (func_00211310((s32)arg0, 0, 4) != 0) {
                s0 = 1;
                func_003126C8((s32)sp, (s32)(*(u8 **)(arg0 + 0x1530) + 0xE70));
            }
        } else if (s2 == 1) {
            a1p = *(u8 **)(arg0 + 0x1530);
            v1 = *(s32 *)(a1p + 0xE54);
            if ((v1 & 0x20) && !(v1 & 0x40)) {
                s0 = 1;
                func_003126C8((s32)sp, (s32)(a1p + 0xEE0));
            }
        }
        if (s0 == 0) {
            continue;
        }
        f0 = *(f32 *)&sp[1];
        if (f22 < f0) {
            if (s3 != 0) {
                continue;
            }
        } else {
            if (s3 == 0) {
                continue;
            }
        }
        /* block_16 */
        if (f21 == D_00385B30) {
            return 1;
        }
        ip = sceVu0InnerProduct((s32)sp, (s32)(BtlChar_GetPos((s32)arg0) + 0x20));
        f20 = -ip;
        if (cosf(f21) < f20) {
            return 1;
        }
    }
    return 0;
}
