#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))

void sceVu0Normalize(f32 *out, f32 *in);
f32 sceVu0InnerProduct(f32 *a, f32 *b);

/* 0x0012A4B0: for 256 RGB triples at arg1 (4 bytes each, 3 used): the vector (r-100, g-100, b-100, 1) is
 * normalized, dotted with the 3-float vector at arg2 and scaled by 100; the result (truncated, clamped at 0,
 * halved, plus 0x20, at most 0x80) is added to byte 3 of the output at arg0, and the three bytes arg3, arg4
 * and arg5 are added to bytes 0..2 of every output entry (4 bytes each). */
void func_0012A4B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *out;
    u8 *in;
    f32 vec[4];
    f32 dot;
    s32 t;
    s32 i;
    u8 add0;
    u8 add1;
    u8 add2;

    out = PTR(arg0);
    in = PTR(arg1);
    add0 = (u8)(arg3 & 0xFF);
    add1 = (u8)(arg4 & 0xFF);
    add2 = (u8)(arg5 & 0xFF);

    i = 0;
    do {
        vec[0] = (f32)in[0] - 100.0f;
        vec[1] = (f32)in[1] - 100.0f;
        vec[2] = (f32)in[2] - 100.0f;
        vec[3] = 1.0f;
        in += 4;
        i++;

        sceVu0Normalize(vec, vec);
        dot = sceVu0InnerProduct((f32 *)PTR(arg2), vec) * 100.0f;

        out[0] = (u8)(out[0] + add0);
        out[1] = (u8)(out[1] + add1);
        out[2] = (u8)(out[2] + add2);

        t = (s32)dot;
        if (t < 0) {
            t = 0;
        }
        t = t / 2 + 0x20;
        if (t > 0x80) {
            t = 0x80;
        }
        out[3] = (u8)(out[3] + t);
        out += 4;
    } while (i < 256);
}
