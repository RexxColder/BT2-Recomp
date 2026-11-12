#include "m2c_macros.h"

void *memcpy(void *dst, void *src, u32 n);
void func_002FD518(u8 *p);
extern u8 D_00356CF0[] __attribute__((section(".data")));

/* Splits str into lines ('\n'), strips a trailing '\r' and copies each line to dst0 + k * stride.
 * Returns the number of lines; the first line/count/stride are also stored in D_00356CF0 when it is empty. */
s32 func_002FE128(u8 *dst0, u8 *str, s32 lim, s32 count, s32 stride) {
    s32 s2 = 0;
    s32 s5 = 0;
    s32 prev = 0;
    s32 s1 = 0;
    s32 nxt = 0;
    s32 nc = 0;
    s32 c = 0;
    u8 *dst = 0;
    u8 *a1 = 0;
    u8 *vp = 0;

    if (str[0] == 0) {
        goto end;
    }
    dst = dst0 + count * 8;
    a1 = str;
    c = (s8)str[0];

L198:
    if (c == 10) {
        nc = (s8)a1[1];
        goto L1AC;
    }
    /* c is not '\n' and not 0 */
    nxt = s2 + 1;
    goto L23C;

L1AC:
    if (nc == 10) {
        s2 = s2 + 1;
        goto L1C0;
    }
    if (nc != 0) {
        vp = a1 - 1;
        goto L1C8;
    }
    vp = a1 - 1;
    s2 = s2 + 1;

L1C0:
    a1 = str + s2;
    vp = a1 - 1;

L1C8:
    c = (s8)*vp;
    s1 = s2 - prev;
    if (c == 10 || c == 13) {
        *vp = 0;
    }
    /* position a1 - 2: its char is cleared when it is '\n' or '\r' */
    c = (s8)*(a1 - 2);
    if (c == 10 || c == 13) {
        *(a1 - 2) = 0;
    }
    a1 = str + prev;

    memcpy(dst, a1, s1);
    func_002FD518(dst);
    if (dst[s1 - 1] != 0) {
        dst[s1] = 0;
    }
    nxt = s2 + 1;
    dst = dst + stride + 1;
    s5 = s5 + 1;
    if (s5 == count) {
        goto end;
    }
    prev = nxt;

L23C:
    if (lim < nxt) {
        goto end;
    }
    s2 = nxt;
    a1 = str + s2;
    c = (s8)*a1;
    if (c != 0) {
        goto L198;
    }

end:
    if (*(s32 *)D_00356CF0 == 0) {
        *(s32 *)(D_00356CF0 + 0xC) = stride;
        *(s32 *)(D_00356CF0 + 0x8) = count;
        *(s32 *)(D_00356CF0 + 0x0) = (s32)(long)dst0;
        *(s32 *)(D_00356CF0 + 0x4) = s5;
    }
    return s5;
}
