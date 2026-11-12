#include "common.h"
void *memset(void *arg0, s32 arg1, s32 arg2);
void *memcpy(void *arg0, void *arg1, s32 arg2);

s32 func_0026CB18(s32 arg0, s32 arg1);
s32 func_0026F180(u8 *arg0, s32 arg1);
s32 func_0026CF00(s32 arg0, s32 arg1);
s32 func_0026CF30(s32 arg0, s32 arg1);
void func_0026F200(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_0026E6D8(s32 arg0, s32 arg1);

/* 0x0026F930: walks a list of 18-byte records (u16 id + 4 words) from the
 * table returned by func_0026CB18 and emits one draw record per entry. */
void func_0026F930(s32 a0, s32 a1, s32 a2) {
    u8 frame[0x68];
    u8 *s6;
    u8 *s1;
    u8 *s3;
    u8 *vs;
    u8 *s0;
    u8 *p;
    s32 s2;
    s32 s7;
    s32 fl;
    s32 id;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;

    s6 = (u8 *)a0;
    s1 = (u8 *)a1;
    s3 = (u8 *)a2;
    vs = frame + 0x10;

    p = (u8 *)func_0026CB18(*(s32 *)s3, *(s32 *)(s6 + 4));
    frame[0x60] = p[2];
    if (frame[0x60] == 0) {
        return;
    }
    s0 = p + 3;
    s7 = 0;
    do {
        memset(vs, 0, 0x48);
        frame[0x62] = s0[0];
        frame[0x63] = s0[1];
        s0 += 2;
        memcpy(frame + 0x00, s0 + 0, 4);
        memcpy(frame + 0x08, s0 + 4, 4);
        memcpy(frame + 0x04, s0 + 8, 4);
        memcpy(frame + 0x0C, s0 + 12, 4);
        s0 += 16;
        id = frame[0x62] | (frame[0x63] << 8);

        s2 = func_0026F180(s3, id);
        if (s2 != 0) {
            f3 = (f32)*(s32 *)(frame + 0x00);
            f2 = (f32)*(s32 *)(frame + 0x04);
            f1 = (f32)*(s32 *)(frame + 0x08);
            f0 = (f32)*(s32 *)(frame + 0x0C);
            *(f32 *)(frame + 0x24) = f3;
            *(f32 *)(frame + 0x20) = f2;
            *(f32 *)(frame + 0x2C) = f1;
            *(f32 *)(frame + 0x30) = f0;
            *(f32 *)(frame + 0x14) = f3;
            *(f32 *)(frame + 0x18) = f2;
            *(f32 *)(frame + 0x1C) = f1;
            *(f32 *)(frame + 0x28) = f0;
            *(s32 *)(frame + 0x34) = 0;
            *(s32 *)(frame + 0x3C) = func_0026CF00(*(s32 *)s3, id);
            *(s32 *)(frame + 0x38) = 0;
            *(s32 *)(frame + 0x40) = func_0026CF30(*(s32 *)s3, id);
            *(s32 *)(frame + 0x44) = 0;
            *(s32 *)(frame + 0x48) = 128;
            *(s32 *)(frame + 0x4C) = 128;
            *(s32 *)(frame + 0x50) = 128;
            *(s32 *)(frame + 0x54) = 128;

            func_0026F200((s32)vs, (s32)(s6 + 8), (s32)(s6 + 0x20), (s32)s1,
                          *(s32 *)(s3 + 0xC), *(s32 *)(s3 + 0x10));

            if (s1 != 0) {
                fl = *(s32 *)s1;
                if (fl & 4) {
                    *(s32 *)(frame + 0x34) = *(s32 *)(s1 + 0x1C);
                    *(s32 *)(frame + 0x3C) = *(s32 *)(s1 + 0x24);
                    *(s32 *)(frame + 0x38) = *(s32 *)(s1 + 0x20);
                    *(s32 *)(frame + 0x40) = *(s32 *)(s1 + 0x28);
                    *(s32 *)(frame + 0x44) = 0;
                }
                if (fl & 1) {
                    *(s32 *)(frame + 0x44) = *(s32 *)(s1 + 0x2C);
                }
                if (fl & 0x40) {
                    *(s32 *)vs |= 1;
                }
                if (fl & 0x80) {
                    *(s32 *)vs |= 2;
                }
                if (fl & 0x100) {
                    *(s32 *)vs |= 4;
                }
                if (fl & 0x400) {
                    *(s32 *)vs |= 8;
                }
                if (fl & 0x800) {
                    *(s32 *)vs |= 0x10;
                }
            }
            func_0026E6D8(s2, (s32)vs);
        }
        s7++;
    } while (s7 < (s32)frame[0x60]);
}
