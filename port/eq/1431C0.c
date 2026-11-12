#include "m2c_macros.h"

void func_003126C8(void *arg0, u8 *arg1);
void func_00312638(void *arg0, u8 *arg1, s32 arg2);
void func_00142608(s32 *arg0, u8 *arg1, s32 *arg2);

/* GS packet emitter: for arg3 records (0x20 bytes apart from arg2) two vectors are built, and when either
 * of the two word groups holds a valid 16-bit size, a 0x40-byte GIF block is written at the cursor arg0.
 * Returns the cursor after the last block. */
u8 *GsPkt_EmitBox(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4) {
    s32 f[16];
    u64 *q;
    s32 cond;

    q = (u64 *)arg0;
    if (arg3 <= 0) {
        return (u8 *)q;
    }
    do {
        func_003126C8(&f[8], arg2);
        func_00312638(&f[12], arg2, arg4);
        func_00142608(&f[0], arg1, &f[8]);
        func_00142608(&f[4], arg1, &f[12]);

        cond = (f[2] > 0 && f[0] > 0 && f[0] <= 0xFFFF && f[1] > 0 && f[1] <= 0xFFFF)
            || (f[6] > 0 && f[4] > 0 && f[4] <= 0xFFFF && f[5] > 0 && f[5] <= 0xFFFF);
        if (cond) {
            q[0] = 0x4400000000000001ULL;
            q[1] = 0x5510;
            q[2] = 0x41;
            q[3] = 0x3F80000010606060ULL;
            q[4] = ((s64)f[0] | ((s64)f[1] << 16)) | ((s64)f[2] << 32);
            q[5] = ((s64)f[4] | ((s64)f[5] << 16)) | ((s64)f[6] << 32);
            q += 6;
        }
        arg3 -= 1;
        arg2 += 0x20;
    } while (arg3 != 0);
    return (u8 *)q;
}
