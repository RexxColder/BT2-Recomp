#include "common.h"

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 D_0036C9A0[16];

#define PACK(lo, hi) ((u64)(s64)(lo) | ((u64)(s64)(hi) << 16))

/* Writes a GIF packet for a 6px marker at (px, py) into buf and returns the end pointer. flag != 0: axis aligned
   quad (8 qwords); flag == 0: rotated by `angle` and scaled by `scale` (12 qwords). */
u64 *func_00115778(u64 *buf, u64 tag, s32 py, s32 px, s32 flag, f32 angle, f32 scale) {
    f32 tbl[16];
    f32 rot[16];
    s32 q[16];
    f32 sn, cs;
    s32 i;
    u64 v0, v1, v2, v3;
    s32 x0, x1, y0, y1;

    for (i = 0; i < 16; i++) {
        tbl[i] = D_0036C9A0[i];
    }
    if (flag == 0) {
        sn = sinf(angle);
        cs = cosf(angle);
        for (i = 0; i < 4; i++) {
            rot[4 * i + 0] = tbl[4 * i + 0] * scale * cs - tbl[4 * i + 1] * scale * sn;
            rot[4 * i + 1] = tbl[4 * i + 0] * scale * sn + tbl[4 * i + 1] * scale * cs;
            q[4 * i + 0] = py << 4;
            q[4 * i + 1] = px << 4;
            q[4 * i + 0] += 4 * (s32)rot[4 * i + 0];
            q[4 * i + 1] += 4 * (s32)rot[4 * i + 1];
        }
        v0 = PACK(q[0], q[1]);
        v1 = PACK(q[4], q[5]);
        v2 = PACK(q[8], q[9]);
        v3 = PACK(q[12], q[13]);
        buf[0] = 0x6400000000008002ull;
        buf[1] = 0xF5DD10ull;
        buf[2] = 0xC4;
        buf[3] = tag;
        buf[4] = v0;
        buf[5] = v3;
        buf[6] = v2;
        buf[7] = 0;
        buf[8] = 0xC4;
        buf[9] = tag;
        buf[10] = v1;
        buf[11] = v3;
        buf[12] = v2;
        buf[13] = 0;
        buf[14] = 0x8400000000008001ull;
        buf[15] = 0x55555D10ull;
        buf[16] = 0xC2;
        buf[17] = 0x3F80000080000000ull;
        buf[18] = v1;
        buf[19] = v2;
        buf[20] = v0;
        buf[21] = v3;
        buf[22] = v1;
        buf[23] = v2;
        return buf + 24;
    }
    x0 = (py - 3) << 4;
    y0 = (px - 3) << 4;
    x1 = (py + 3) << 4;
    y1 = (px + 3) << 4;
    v0 = PACK(x0, y0);
    v1 = PACK(x0, y1);
    v2 = PACK(x1, y1);
    v3 = PACK(x1, y0);
    buf[0] = 0x4400000000008001ull;
    buf[1] = 0x5510;
    buf[2] = 0xC6;
    buf[3] = tag;
    buf[4] = v0;
    buf[5] = v2;
    buf[6] = 0x8400000000008001ull;
    buf[7] = 0xF5555D10ull;
    buf[8] = 0xC2;
    buf[9] = 0x3F80000080000000ull;
    buf[10] = v0;
    buf[11] = v1;
    buf[12] = v2;
    buf[13] = v3;
    buf[14] = v0;
    buf[15] = 0;
    return buf + 16;
}
