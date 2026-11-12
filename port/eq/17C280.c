#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_00384A28;
extern f32 D_00384A2C;
extern f32 D_00384A30;
extern f32 D_00384A34;
extern f32 D_00384A38;
extern f32 D_00384A3C;
extern f32 D_00384A40;
extern f32 D_00384A44;
extern f32 D_00384A48;
extern f32 D_00384A4C;
extern u8 *D_0038777C;

void func_00129BB8(f32 farg0, void *arg0, void *arg1);

void EftAura_SetType(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 flags;
    s32 v0;
    s32 temp_a0;
    s32 temp_v1;
    s32 s3;
    s32 s4;
    s32 temp_s0_2;
    s32 temp_v1_3;
    s32 stride;
    f32 var_f12;
    u8 *var_a0;
    u8 *var_a1;
    u8 *s2;

    var_a2 = arg2;
    W(arg0, 0x10) = arg3;
    flags = W(arg0, 0x0) & ~0x80;
    W(arg0, 0x0) = flags;
    if (arg3 & 0x5E) {
        var_a2 = 8;
        W(arg0, 0x0) = flags | 0x80;
        W(arg0, 0x24) = 1;
        W(arg0, 0x20) = 8;
        if (arg3 & 0x46) {
            W(arg0, 0x24) = 2;
        } else {
            v0 = 0xA;
            if ((arg3 & 8) || (v0 = 0xC, (arg3 & 0x10) != 0)) {
                W(arg0, 0x20) = v0;
                W(arg0, 0x24) = 2;
            }
        }
    } else if (var_a2 >= 8) {
        W(arg0, 0x0) = flags | 0x80;
        W(arg0, 0x20) = 8;
        W(arg0, 0x24) = 2;
    }

    temp_a0 = W(arg0, 0x0);
    W(arg0, 0x18) = var_a2;
    W(arg0, 0x1C) = 1;
    W(arg0, 0x14) = var_a2;
    if (temp_a0 & 0x80) {
        W(arg0, 0x1C) = 2;
    }

    s3 = 0;
    if (!(arg3 & 2)) {
        s3 = 1;
        if (!(arg3 & 4)) {
            s3 = 2;
            if (!(arg3 & 8)) {
                s3 = 3;
                if (!(arg3 & 0x10)) {
                    s3 = (arg3 & 0x40) ? 4 : 0;
                }
            }
        }
    }

    if (temp_a0 & 0x80) {
        stride = s3 * 0xD0;
        func_00129BB8(D_00384A28, (u8 *)arg0 + 0x3F0, D_0038777C + stride + 0xC60);
        var_f12 = D_00384A2C;
        var_a0 = (u8 *)arg0 + 0x400;
        var_a1 = D_0038777C + stride + 0xC60;
    } else {
        temp_v1 = W(arg0, 0x14);
        func_00129BB8(D_00384A30, (u8 *)arg0 + 0x3F0, D_0038777C + temp_v1 * 0xD0 + 0x510);
        var_a0 = (u8 *)arg0 + 0x400;
        var_f12 = D_00384A34;
        var_a1 = D_0038777C + W(arg0, 0x14) * 0xD0 + 0x510;
    }

    s4 = 0;
    func_00129BB8(var_f12, var_a0, var_a1);
    W(arg0, 0x40C) = 0;
    s2 = arg0;
    s3 = s3 * 0xD0;
    do {
        if (W(arg0, 0x0) & 0x80) {
            func_00129BB8(D_00384A38, s2 + 0x410, D_0038777C + s3 + 0xC70);
            func_00129BB8(D_00384A3C, s2 + 0x450, D_0038777C + s3 + 0xCB0);
            func_00129BB8(D_00384A40, s2 + 0x490, D_0038777C + s3 + 0xCF0);
        } else {
            temp_v1_3 = W(arg0, 0x14);
            temp_s0_2 = (temp_v1_3 >= 8) ? s4 : 0;
            func_00129BB8(D_00384A44, s2 + 0x410, D_0038777C + (((temp_v1_3 * 0xD) + temp_s0_2) * 0x10) + 0x520);
            func_00129BB8(D_00384A48, s2 + 0x450, D_0038777C + (((W(arg0, 0x14) * 0xD) + temp_s0_2) * 0x10) + 0x560);
            func_00129BB8(D_00384A4C, s2 + 0x490, D_0038777C + (((W(arg0, 0x14) * 0xD) + temp_s0_2) * 0x10) + 0x5A0);
        }
        s4 += 1;
        s2 += 0x10;
        s3 += 0x10;
    } while (s4 < 4);
}
