#include "common.h"

extern u8 *D_0042A590 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

/* 0x003FF340: S = D_0042A590. Clears S+0x104..0x130 (12 words), then for i = 0..2 and finally for S->0x1A4 copies
 * resource words (entry+0x10) into S+0x104.. slots depending on the type of the current entry. */
static u8 *ent(u8 *s, s32 id) {
    u8 *b = *(u8 **)(s + 0x18);
    return b + (*(u32 *)(b + 4 * id + 4) >> 2 << 2);
}

/* index of first id (x) and second (y); y valid only when two = 1 */
static void pick(u8 *s, s32 cur, s32 cnt, s32 k, s32 *x, s32 *y) {
    if (*(s8 *)(D_387F2C + cur + 0x2C0) == 0 && k < *(s32 *)(s + 0x23C)) {
        *x = 0x83;
        *y = 0x83;
        return;
    }
    *x = *(s32 *)(*(u8 **)(s + 0x278) + cur * 80 + k * 4);
    *y = *(s32 *)(*(u8 **)(s + 0x278) + cur * 80 + k * 4 + 0x28);
}

void func_003FF340(void) {
    u8 *s;
    s32 i;
    s32 cur;
    u8 *e;
    s32 k;
    s32 cnt;
    s32 type;
    s32 x;
    s32 y;
    u8 *p;
    u8 *q;

    s = D_0042A590;
    *(s32 *)(s + 0x17C) = 0;
    *(s32 *)(s + 0x180) = 0;
    *(s32 *)(s + 0x184) = 0;
    *(s32 *)(s + 0x188) = 0;
    *(s32 *)(s + 0x18C) = 0;
    *(s32 *)(s + 0x190) = 0;
    *(s32 *)(s + 0x194) = 0;
    *(s32 *)(s + 0x198) = 0;
    *(s32 *)(s + 0x19C) = 0;
    *(s32 *)(s + 0x1A0) = 0;
    *(s32 *)(s + 0x1A4) = 0;
    *(s32 *)(s + 0x1A8) = 0;

    for (i = 0; i < 3; i++) {
        s = D_0042A590;
        cur = *(s32 *)(D_3876A4 + 0x64);
        e = *(u8 **)(s + 0x274) + cur * 56;
        k = *(s32 *)(s + 0x240) + i;
        cnt = *(s32 *)(e + 8);
        if (k >= cnt || k == -1) {
            continue;
        }
        type = *(s32 *)(e + 0xC);
        if (type == 2 || type == 4) {
            pick(s, cur, cnt, k, &x, &y);
            p = ent(D_0042A590, x);
            q = ent(D_0042A590, y);
            s = D_0042A590;
            if (i == 1) {
                *(s32 *)(s + 0x18C) = *(s32 *)(p + 0x10);
                *(s32 *)(s + 0x190) = *(s32 *)(q + 0x10);
            } else if (i == 0) {
                *(s32 *)(s + 0x180) = *(s32 *)(p + 0x10);
                *(s32 *)(s + 0x184) = *(s32 *)(q + 0x10);
            } else if (i == 2) {
                *(s32 *)(s + 0x198) = *(s32 *)(p + 0x10);
                *(s32 *)(s + 0x19C) = *(s32 *)(q + 0x10);
            }
        } else if (type == 1) {
            x = *(s32 *)(*(u8 **)(s + 0x278) + cur * 80 + k * 4);
            p = ent(s, x);
            if (i == 1) {
                *(s32 *)(s + 0x188) = *(s32 *)(p + 0x10);
            } else if (i == 0) {
                *(s32 *)(s + 0x17C) = *(s32 *)(p + 0x10);
            } else if (i == 2) {
                *(s32 *)(s + 0x194) = *(s32 *)(p + 0x10);
            }
        } else {
            pick(s, cur, cnt, k, &x, &y);
            p = ent(D_0042A590, x);
            if (i == 1) {
                *(s32 *)(s + 0x188) = *(s32 *)(p + 0x10);
            } else if (i == 0) {
                *(s32 *)(s + 0x17C) = *(s32 *)(p + 0x10);
            } else if (i == 2) {
                *(s32 *)(s + 0x194) = *(s32 *)(p + 0x10);
            }
        }
    }

    s = D_0042A590;
    cur = *(s32 *)(D_3876A4 + 0x64);
    e = *(u8 **)(s + 0x274) + cur * 56;
    cnt = *(s32 *)(e + 8);
    k = *(s32 *)(s + 0x244);
    if (k >= cnt || k == -1) {
        return;
    }
    type = *(s32 *)(e + 0xC);
    if (type == 2 || type == 4) {
        pick(s, cur, cnt, k, &x, &y);
        p = ent(D_0042A590, x);
        q = ent(D_0042A590, y);
        s = D_0042A590;
        *(s32 *)(s + 0x1A4) = *(s32 *)(p + 0x10);
        *(s32 *)(s + 0x1A8) = *(s32 *)(q + 0x10);
    } else if (type == 1) {
        x = *(s32 *)(*(u8 **)(s + 0x278) + cur * 80 + k * 4);
        p = ent(s, x);
        *(s32 *)(s + 0x1A0) = *(s32 *)(p + 0x10);
    } else {
        pick(s, cur, cnt, k, &x, &y);
        p = ent(D_0042A590, x);
        *(s32 *)(D_0042A590 + 0x1A0) = *(s32 *)(p + 0x10);
    }
}
