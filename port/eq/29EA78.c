#include "common.h"
#include "vu0_state.h"

s32 func_0029D548(void);
void func_0029D580(s32 arg0);
void func_0029D5C8(s32 arg0);
void func_0029C980(s32 arg0, s32 arg1, s32 arg2);
void Vu0Cur_StoreMtx(s32 arg0);

/* Integer time key as float: negative keys use the halved-unsigned trick (doubled). */
#define KEY_TIME(v) ((v) < 0 ? (((f32)(((v) & 1) | ((u32)(v) >> 1))) * 2.0f) : (f32)(v))

/* 0x0029EA78: walks a list of 32-byte keyframe pairs (time at +0xC), finds the segment
 * around time t, and writes two interpolated vectors (VU0 xyz lerp) into the output block. */
s32 func_0029EA78(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    u8 *out;
    u8 *list;
    u8 *s1;
    u8 *s0;
    u8 *prev;
    u8 *next;
    s32 count;
    s32 i;
    s32 tpRaw;
    s32 tnRaw;
    s32 d;
    s32 k;
    f32 tp;
    f32 tn;
    f32 delta;
    f32 ratio;

    out = arg0;
    list = arg1;

    func_0029D5C8((s32)arg2);
    for (;;) {
        func_0029D548();
        s1 = out + 0x10;
        s0 = out + 0x20;

        if (list != 0) {
            count = *(u16 *)(list + 0x0A);
            for (i = 1; i < count; i++) {
                prev = list + 0x10 + ((i - 1) << 5);
                next = prev + 0x20;
                tpRaw = *(s32 *)(prev + 0x0C);
                tp = KEY_TIME(tpRaw);
                if (tp == arg3) {
                    __builtin_memcpy(s1, prev, 16);
                    __builtin_memcpy(s0, prev + 0x10, 16);
                    break;
                }
                if (tp < arg3) {
                    tnRaw = *(s32 *)(next + 0x0C);
                    tn = KEY_TIME(tnRaw);
                    if (arg3 < tn) {
                        d = (s32)((u32)tnRaw - (u32)tpRaw);
                        delta = KEY_TIME(d);
                        ratio = (arg3 - tp) / delta;

                        gVu0.vf[1][0] = ratio;
                        __builtin_memcpy(gVu0.vf[2], prev, 16);
                        __builtin_memcpy(gVu0.vf[3], prev + 0x10, 16);
                        __builtin_memcpy(gVu0.vf[4], next, 16);
                        __builtin_memcpy(gVu0.vf[5], next + 0x10, 16);
                        for (k = 0; k < 3; k++) {
                            gVu0.vf[6][k] = gVu0.vf[4][k] - gVu0.vf[2][k];
                            gVu0.vf[7][k] = gVu0.vf[5][k] - gVu0.vf[3][k];
                        }
                        for (k = 0; k < 3; k++) {
                            gVu0.vf[8][k] = gVu0.vf[6][k] * ratio;
                            gVu0.vf[9][k] = gVu0.vf[7][k] * ratio;
                        }
                        for (k = 0; k < 3; k++) {
                            gVu0.vf[6][k] = gVu0.vf[8][k] + gVu0.vf[2][k];
                            gVu0.vf[7][k] = gVu0.vf[9][k] + gVu0.vf[3][k];
                        }
                        __builtin_memcpy(s1, gVu0.vf[6], 16);
                        __builtin_memcpy(s0, gVu0.vf[7], 16);
                        break;
                    }
                }
                tnRaw = *(s32 *)(next + 0x0C);
                tn = KEY_TIME(tnRaw);
                if (tn == arg3) {
                    __builtin_memcpy(s1, next, 16);
                    __builtin_memcpy(s0, next + 0x10, 16);
                    break;
                }
            }
        }

        *(f32 *)(out + 0x2C) = 1.0f;
        *(f32 *)(out + 0x1C) = 1.0f;
        Vu0Cur_StoreMtx((s32)(out + 0x50));
        func_0029C980((s32)s1, (s32)s0, *(u16 *)(list + 0x08));
        Vu0Cur_StoreMtx((s32)(out + 0x90));
        __builtin_memcpy(out + 0xD0, out + 0x30, 16);
        __builtin_memcpy(out + 0xE0, out + 0x40, 16);
        if (*(s32 *)(out + 0x04) != 0) {
            func_0029D580(*(s32 *)(out + 0x04));
        }
        if (*(s32 *)(out + 0x08) != 0) {
            return *(s32 *)(out + 0x08);
        }
        out = out + *(s32 *)(out + 0x00);
        if (list != 0) {
            list = list + 0x10 + (*(u16 *)(list + 0x0A) << 5);
        }
    }
}
