#include "common.h"

extern u8 *D_0042A588 __attribute__((section(".data")));

void func_26E9E8(u8 *p);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003FD610: G = D_0042A588. Three calls func_26E9E8(p + 0x10) with p = G, then p += off (off = 0, 0x28, 0x50);
 Then six records: bit
 * (4 << i) of G->0xFC adds 0xD to G[4 + 4i + 0x168] and clamps it to G[4 + 4i + 0x150] (clearing the bit when
 * clamped); G->0x184 sums G[0x16C + 4i]. Finally the 0x118 one-shot calls func_297FE0(2,6,0x40,0x40,1) and the
 * 0x234 countdown reloads 5 and calls func_297FE0(2,5,0x20,0x20,1). */
void func_003FD610(void) {
    u8 *g;
    u8 *p;
    s32 off;
    s32 cnt;
    s32 s1;
    s32 mask;
    s32 a2;
    s32 t1;
    s32 v;
    s32 temp;

    off = 0;
    cnt = 2;
    do {
        cnt -= 1;
        p = D_0042A588 + off; /* asm reloads G each pass: G+0x10/0x38/0x60 (was cumulative -> 0x88, G+0x60 never ran: UB result hang B18) */
        off += 0x28;
        func_26E9E8(p + 0x10);
    } while (cnt >= 0);

    g = D_0042A588;
    *(s32 *)(g + 0x184) = 0;
    t1 = 0;
    a2 = 0x168;
    s1 = 0;
    do {
        mask = 4 << s1;
        s1 += 1;
        if (*(s32 *)(g + 0xFC) & mask) {
            *(s32 *)(g + 4 + a2) += 0xD;
            if (*(s32 *)(g + 4 + a2) >= *(s32 *)(g + 4 + t1 + 0x150)) {
                *(s32 *)(g + 4 + a2) = *(s32 *)(g + 4 + t1 + 0x150);
                *(s32 *)(g + 0xFC) ^= mask;
            }
        }
        t1 += 4;
        *(s32 *)(g + 0x184) += *(s32 *)(g + a2 + 4);
        a2 += 4;
    } while (s1 < 6);

    v = *(s32 *)(g + 0xFC);
    if (*(s32 *)(g + 0x118) == 0) {
        if ((v & 0xFC) != 0) {
            goto block_11;
        }
        *(s32 *)(g + 0x118) = 1;
        func_297FE0(2, 6, 0x40, 0x40, 1);
        v = *(s32 *)(g + 0xFC);
    }
    if ((v & 0xFC) == 0) {
        return;
    }
block_11:
    temp = *(s32 *)(g + 0x234) - 1;
    *(s32 *)(g + 0x234) = temp;
    if (temp == -1) {
        *(s32 *)(g + 0x234) = 5;
        func_297FE0(2, 5, 0x20, 0x20, 1);
    }
}
