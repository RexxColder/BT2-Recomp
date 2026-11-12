#include "m2c_macros.h"

void *memcpy(void *dst, void *src, u32 n);
extern u8 D_0036C820[] __attribute__((section(".data")));
extern u8 D_0036C840[] __attribute__((section(".data")));

s32 func_00111328(u8 *out, u32 num, s32 k) {
    s32 buf[8];
    u8 *tbl = D_0036C840;
    s32 idx;
    s32 cnt = 0;
    s32 flag = 0;
    u32 rem = num;
    u8 *e;
    u8 *dst;
    u32 d;
    u32 q;

    if (k <= 0) {
        return 0;
    }
    memcpy(buf, D_0036C820, 0x20);
    idx = k - 1;
    do {
        d = (u32)buf[idx];
        q = rem / d;
        if (q == 0 && flag != 0) {
            e = tbl;
        } else if (k != 1 || num != 0) {
            if (q == 0) {
                e = tbl + 0x64;
            } else {
                flag = 1;
                e = tbl + (s32)q * 10;
                rem -= d * q;
            }
        } else {
            e = tbl;
        }
        dst = out + cnt * 0x60;
        *(u16 *)(dst + 0xC) = *(u16 *)(e + 0);
        *(u16 *)(dst + 0xE) = *(u16 *)(e + 2);
        *(u16 *)(dst + 0x10) = *(u16 *)(e + 4);
        *(u16 *)(dst + 0x12) = *(u16 *)(e + 6);
        *(u16 *)(dst + 0x14) = 0;
        k--;
        cnt++;
        idx--;
    } while (k > 0);
    return cnt;
}
