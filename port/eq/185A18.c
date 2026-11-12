#include "common.h"

#define NODE_F32(off) (*(f32 *)(s1 + k * 16 + (off)))

void Vu0Screen_StoreMtx(s32 arg0);
s32 func_00126598(s32 arg0);
void func_001866A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_00185A18(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[0x60];
    u8 *self;
    u8 *s0;
    u8 *s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 k;
    f32 f1;

    self = (u8 *)arg0;
    s4 = arg2 & 0xFF;
    s2 = 0;
    if ((*(s32 *)(self + 0x19C) & 0x200) != 0) {
        s2 = 1;
        if (func_00126598(*(s32 *)(self + 0x94)) == 0) {
            return;
        }
    }
    s3 = *(s32 *)self + (*(u8 *)(self + 0x198) * 0x10);
    s0 = *(u8 **)(self + 0x1A4);
    if (s0 == NULL) {
        return;
    }
    s1 = self + 8;
    f1 = *(f32 *)(s0 + 0xA8);
    do {
        k = *(u8 *)(s0 + 0xBD);
        if (f1 < 0.0f && s4 != 0) {
            *(f32 *)(sp + 0x40) = NODE_F32(0x90);
            *(f32 *)(sp + 0x44) = NODE_F32(0x94);
            *(f32 *)(sp + 0x48) = NODE_F32(0x90);
            *(f32 *)(sp + 0x4C) = NODE_F32(0x9C);
            *(f32 *)(sp + 0x50) = NODE_F32(0x98);
            *(f32 *)(sp + 0x54) = NODE_F32(0x94);
            *(f32 *)(sp + 0x58) = NODE_F32(0x98);
        } else {
            *(f32 *)(sp + 0x40) = NODE_F32(0x98);
            *(f32 *)(sp + 0x44) = NODE_F32(0x94);
            *(f32 *)(sp + 0x48) = NODE_F32(0x98);
            *(f32 *)(sp + 0x4C) = NODE_F32(0x9C);
            *(f32 *)(sp + 0x50) = NODE_F32(0x90);
            *(f32 *)(sp + 0x54) = NODE_F32(0x94);
            *(f32 *)(sp + 0x58) = NODE_F32(0x90);
        }
        *(f32 *)(sp + 0x5C) = NODE_F32(0x9C);
        Vu0Screen_StoreMtx((s32)sp);
        func_001866A8((s32)(s0 + 0x40), (s32)sp, (s32)(sp + 0x40), (s32)(sp + 0x50),
                      (s32)(s0 + 0x20), arg1, s2, s3);
        s0 = *(u8 **)(s0 + 0xC0);
        if (s0 != NULL) {
            f1 = *(f32 *)(s0 + 0xA8);
        }
    } while (s0 != NULL);
}
