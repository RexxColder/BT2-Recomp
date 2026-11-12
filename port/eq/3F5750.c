#include "common.h"

extern u8 *D_0042A578 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

/* 0x003F5750: S = D_0042A578. Clears S+0x104..0x130 (12 words), then for i = 0..2 and finally for S->0x1A4 copies
 * resource words (entry+0x10) into S+0x104.. slots depending on the type of the current entry. */
static u8 *ent(u8 *s, s32 id) {
    u8 *b = *(u8 **)(s + 8);
    return b + (*(u32 *)(b + 4 * id + 4) >> 2 << 2);
}

/* index of first id (x) and second (y); y valid only when two = 1 */
static void pick(u8 *s, s32 cur, s32 cnt, s32 k, s32 *x, s32 *y) {
    if (*(s8 *)(D_387F2C + cur + 0x2C0) == 0 && k != cnt - 1) {
        *x = 0x83;
        *y = 0x83;
        return;
    }
    *x = *(s32 *)(*(u8 **)(s + 0x1C8) + cur * 80 + k * 4);
    *y = *(s32 *)(*(u8 **)(s + 0x1C8) + cur * 80 + k * 4 + 0x28);
}

void func_003F5750(void) {
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

    s = D_0042A578;
    *(s32 *)(s + 0x104) = 0;
    *(s32 *)(s + 0x108) = 0;
    *(s32 *)(s + 0x10C) = 0;
    *(s32 *)(s + 0x110) = 0;
    *(s32 *)(s + 0x114) = 0;
    *(s32 *)(s + 0x118) = 0;
    *(s32 *)(s + 0x11C) = 0;
    *(s32 *)(s + 0x120) = 0;
    *(s32 *)(s + 0x124) = 0;
    *(s32 *)(s + 0x128) = 0;
    *(s32 *)(s + 0x12C) = 0;
    *(s32 *)(s + 0x130) = 0;

    for (i = 0; i < 3; i++) {
        s = D_0042A578;
        cur = *(s32 *)(s + 0x14C + 4 * *(s32 *)(s + 0x140));
        e = *(u8 **)(s + 0x1C4) + cur * 56;
        k = *(s32 *)(s + 0x1A0) + i;
        cnt = *(s32 *)(e + 8);
        if (k >= cnt || k == -1) {
            continue;
        }
        type = *(s32 *)(e + 0xC);
        if (type == 2 || type == 4) {
            pick(s, cur, cnt, k, &x, &y);
            p = ent(D_0042A578, x);
            q = ent(D_0042A578, y);
            s = D_0042A578;
            if (i == 1) {
                *(s32 *)(s + 0x114) = *(s32 *)(p + 0x10);
                *(s32 *)(s + 0x118) = *(s32 *)(q + 0x10);
            } else if (i == 0) {
                *(s32 *)(s + 0x108) = *(s32 *)(p + 0x10);
                *(s32 *)(s + 0x10C) = *(s32 *)(q + 0x10);
            } else if (i == 2) {
                *(s32 *)(s + 0x120) = *(s32 *)(p + 0x10);
                *(s32 *)(s + 0x124) = *(s32 *)(q + 0x10);
            }
        } else if (type == 1) {
            x = *(s32 *)(*(u8 **)(s + 0x1C8) + cur * 80 + k * 4);
            p = ent(s, x);
            if (i == 1) {
                *(s32 *)(s + 0x110) = *(s32 *)(p + 0x10);
            } else if (i == 0) {
                *(s32 *)(s + 0x104) = *(s32 *)(p + 0x10);
            } else if (i == 2) {
                *(s32 *)(s + 0x11C) = *(s32 *)(p + 0x10);
            }
        } else {
            pick(s, cur, cnt, k, &x, &y);
            p = ent(D_0042A578, x);
            if (i == 1) {
                *(s32 *)(s + 0x110) = *(s32 *)(p + 0x10);
            } else if (i == 0) {
                *(s32 *)(s + 0x104) = *(s32 *)(p + 0x10);
            } else if (i == 2) {
                *(s32 *)(s + 0x11C) = *(s32 *)(p + 0x10);
            }
        }
    }

    s = D_0042A578;
    cur = *(s32 *)(s + 0x14C + 4 * *(s32 *)(s + 0x140));
    e = *(u8 **)(s + 0x1C4) + cur * 56;
    cnt = *(s32 *)(e + 8);
    k = *(s32 *)(s + 0x1A4);
    if (k >= cnt || k == -1) {
        return;
    }
    type = *(s32 *)(e + 0xC);
    if (type == 2 || type == 4) {
        pick(s, cur, cnt, k, &x, &y);
        p = ent(D_0042A578, x);
        q = ent(D_0042A578, y);
        s = D_0042A578;
        *(s32 *)(s + 0x12C) = *(s32 *)(p + 0x10);
        *(s32 *)(s + 0x130) = *(s32 *)(q + 0x10);
    } else if (type == 1) {
        x = *(s32 *)(*(u8 **)(s + 0x1C8) + cur * 80 + k * 4);
        p = ent(s, x);
        *(s32 *)(s + 0x128) = *(s32 *)(p + 0x10);
    } else {
        pick(s, cur, cnt, k, &x, &y);
        p = ent(D_0042A578, x);
        *(s32 *)(D_0042A578 + 0x128) = *(s32 *)(p + 0x10);
    }
}
