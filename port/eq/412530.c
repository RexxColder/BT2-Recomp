#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 a0);
u8 *func_002B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);

/* 0x00412530: state machine step. G = D_0042BB7C, state = G->0x373C (1..6, others do nothing).
   G->0x234 is the current half (0/1); per-half tables live at G+0x22C, G+0x224, G+0x23C and so on. */
void func_00412530(void) {
    u8 *G;
    s32 st;
    s32 cur, o, f, m, sh, k, idx, a0v, t1, val, sp[4];
    u8 *t2;
    s32 off, v;

    G = D_0042BB7C;
    st = *(s32 *)(G + 0x373C) - 1;
    if ((u32)st >= 6) {
        return;
    }

    switch (st) {
    case 0: /* state 1 */
        cur = *(s32 *)(G + 0x234);
        sh = *(s32 *)(G + 0x224 + 4 * cur);
        t2 = *(u8 **)(G + 0x2D8 + 4 * cur);
        k = 2 * cur + sh;
        a0v = *(s32 *)(G + 0x24C + 4 * k);
        t1 = *(s32 *)(G + 0x23C + 4 * k);
        idx = 7 * a0v + t1;
        val = *(s32 *)(t2 + 44 * idx);
        func_00100ED0(val + 0x5EE, *(s32 *)(G + 8 + 4 * k), 1);
        func_00100FC8(1);
        *(s32 *)(G + 0x373C) = 2;
        break;

    case 1: /* state 2 */
        if (func_00100FC8(0) != 0) {
            G = D_0042BB7C;
            *(s32 *)(G + 0x373C) = 3;
        }
        break;

    case 2: /* state 3 */
        cur = *(s32 *)(G + 0x234);
        sh = *(s32 *)(G + 0x224 + 4 * cur);
        k = 2 * cur + sh;
        func_002B24C8(*(u8 **)(G + 0x8 + 4 * k), *(u8 **)(G + 0x18 + 4 * k), 0);

        G = D_0042BB7C;
        cur = *(s32 *)(G + 0x234);
        sh = *(s32 *)(G + 0x224 + 4 * cur);
        k = 2 * cur + sh;
        v = *(s32 *)(G + 0x18 + 4 * k);
        sp[0] = v;
        Res_RelocateOffsets((s32)sp, v, v);

        G = D_0042BB7C;
        cur = *(s32 *)(G + 0x234);
        if (cur == 0) {
            off = (*(s32 *)(G + 0x224) == 0) ? 0x124 : 0x140;
        } else {
            off = (*(s32 *)(G + 0x224 + 4 * cur) == 0) ? 0x128 : 0x144;
        }
        *(s32 *)(G + off + 0xC) = *(s32 *)((u8 *)sp[0] + 0x10);

        G = D_0042BB7C;
        cur = *(s32 *)(G + 0x234);
        sh = *(s32 *)(G + 0x224 + 4 * cur);
        if (sh == 0) {
            *(s32 *)(G + 0x22C + 4 * cur) |= 0x40;
        } else if (*(s32 *)(G + 0x29C + 4 * cur) > 0) {
            *(s32 *)(G + 0x22C + 4 * cur) |= (0x40 << (sh & 31));
        }

        G = D_0042BB7C;
        cur = *(s32 *)(G + 0x234);
        o = cur ^ 1;
        f = *(s32 *)(G + 0x22C + 4 * o) & 3;
        if (f != 0) {
            *(s32 *)(G + 0x234) = o;
            *(s32 *)(G + 0x373C) = 6;
            m = *(s32 *)(G + 0x22C + 4 * o);
            if ((m & 1) != 0) {
                *(s32 *)(G + 0x224 + 4 * o) = 0;
            } else {
                *(s32 *)(G + 0x224 + 4 * o) = 1;
            }
        } else {
            *(s32 *)(G + 0x373C) = 4;
        }
        break;

    case 3: /* state 4 */
        m = *(s32 *)(G + 0x22C);
        if ((m & 1) != 0) {
            *(s32 *)(G + 0x234) = 0;
            *(s32 *)(G + 0x224) = 0;
            *(s32 *)(G + 0x373C) = 6;
        } else {
            v = *(s32 *)(G + 0x230);
            if ((v & 1) != 0) {
                *(s32 *)(G + 0x234) = 1;
                *(s32 *)(G + 0x228) = 0;
                *(s32 *)(G + 0x373C) = 6;
            } else if ((m & 2) != 0) {
                *(s32 *)(G + 0x234) = 0;
                *(s32 *)(G + 0x224) = 1;
                *(s32 *)(G + 0x373C) = 6;
            } else if ((v & 2) != 0) {
                *(s32 *)(G + 0x234) = 1;
                *(s32 *)(G + 0x228) = 1;
                *(s32 *)(G + 0x373C) = 6;
            }
        }
        break;

    case 4: /* state 5 */
        cur = *(s32 *)(G + 0x234);
        o = cur ^ 1;
        f = *(s32 *)(G + 0x22C + 4 * o) & 3;
        if (f != 0) {
            *(s32 *)(G + 0x234) = o;
            cur = o;
        }
        m = *(s32 *)(G + 0x22C + 4 * cur);
        if ((m & 1) != 0) {
            *(s32 *)(G + 0x224 + 4 * cur) = 0;
        } else if ((m & 2) != 0) {
            *(s32 *)(G + 0x224 + 4 * cur) = 1;
        }
        *(s32 *)(G + 0x373C) = 6;
        break;

    case 5: /* state 6 */
        cur = *(s32 *)(G + 0x234);
        sh = *(s32 *)(G + 0x224 + 4 * cur);
        m = *(s32 *)(G + 0x22C + 4 * cur);
        if (((m >> (sh & 31)) & 1) != 0) {
            *(s32 *)(G + 0x22C + 4 * cur) = m ^ (1 << (sh & 31));
        }
        *(s32 *)(G + 0x373C) = 1;
        break;
    }
}
