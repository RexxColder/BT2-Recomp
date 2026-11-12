#include "common.h"

extern u8 *D_003879A0;
extern u8 *D_003876A4;

u8 *func_0024C148(void);

/* index into the per-player record table: 4 * G[0x1DC] + 34 * (G[0x1C8] + 7 * G[0x1CC]) (G = D_003879A0) */
#define ROW(G) (4 * *(s32 *)((G) + 0x1DC) + 34 * (*(s32 *)((G) + 0x1C8) + 7 * *(s32 *)((G) + 0x1CC)))

/* 0x0024C7A8: updates the menu cursor record table. (1) when the current row's slot is non-zero, bumps the counter
   of the slot's entry in the table at func_0024C148()+0x1F2E (capped against the item array at G+0x334C), (2) always
   decrements the counter for H[0x49C], (3) snapshots the cursor state G+0x3314.. into the row, (4) for each of the 7
   items at G+0x3330 bumps/caps its counter, (5) latches the current item pointers G[0x3234] / G[0x3238] from the
   table selected by H[0x48C] & 2. Returns the last value loaded. */
s32 func_0024C7A8(void) {
    u8 *G = D_003879A0;
    u8 *H;
    u8 *t;
    u16 *cnt;
    s32 slot;
    s32 slotB;
    s32 lim;
    s32 k;
    s32 idx;
    s32 M;
    s32 off;
    u8 *rec;
    s32 result;

    slot = *(s16 *)(func_0024C148() + ROW(G) + 0x1408);
    if (slot != 0) {
        t = func_0024C148();
        slot = *(s16 *)(func_0024C148() + ROW(G) + 0x1408);
        cnt = (u16 *)(t + slot * 4 + 0x1F2E);
        *cnt = *cnt + 1;
        rec = *(u8 **)(G + 0x334C);
        slot = *(s16 *)(func_0024C148() + ROW(G) + 0x1408);
        rec = rec + slot * 48;
        t = func_0024C148();
        lim = *(s32 *)(rec - 0x30 + 0x10);
        slot = *(s16 *)(func_0024C148() + ROW(G) + 0x1408);
        if (lim < *(s16 *)(t + slot * 4 + 0x1F2E)) {
            u8 *tA = func_0024C148();
            u8 *tB = func_0024C148();
            u8 *tC = func_0024C148();
            s32 sA = *(s16 *)(tC + ROW(G) + 0x1408);
            s32 sB = *(s16 *)(tB + ROW(G) + 0x1408);
            *(u16 *)(tA + sB * 4 + 0x1F2E) = *(u16 *)(*(u8 **)(G + 0x334C) + sA * 48 - 0x20);
        }
    }
    H = D_003876A4;
    cnt = (u16 *)(*(s32 *)(H + 0x49C) * 4 + func_0024C148() + 0x1F2E);
    *cnt = *cnt - 1;
    __builtin_memcpy(func_0024C148() + 34 * (*(s32 *)(G + 0x1C8) + 7 * *(s32 *)(G + 0x1CC)) + 0x1408, G + 0x3314, 28);
    *(s32 *)(G + 0x321C) = *(s32 *)(G + 0x3220);
    __builtin_memcpy(G + 0x326C, G + 0x328C, 32);
    __builtin_memset(G + 0x3240, 0, 0x2C);
    k = 6;
    off = 0x3330;
    do {
        idx = *(s32 *)(G + off);
        if (idx != 0) {
            cnt = (u16 *)(func_0024C148() + idx * 4 + 0x1F2E);
            *cnt = *cnt + 1;
            idx = *(s32 *)(G + off);
            rec = *(u8 **)(G + 0x334C) + idx * 48;
            t = func_0024C148();
            lim = *(s32 *)(rec - 0x30 + 0x10);
            if (lim < *(s16 *)(t + *(s32 *)(G + off) * 4 + 0x1F2E)) {
                t = func_0024C148();
                *(u16 *)(t + *(s32 *)(G + off) * 4 + 0x1F2E) =
                    *(u16 *)(*(u8 **)(G + 0x334C) + *(s32 *)(G + off) * 48 - 0x20);
            }
        }
        k = k - 1;
        off = off + 4;
    } while (k >= 0);
    M = *(s32 *)(G + 0x1C8) + 7 * *(s32 *)(G + 0x1CC);
    off = ((*(s32 *)(H + 0x48C) & 2) == 0) ? 0x1E0 : 0x1E4;
    idx = *(s32 *)(*(u8 **)(G + off + 8) + 44 * M);
    *(s32 *)(G + 0x3234) = *(s32 *)(*(u8 **)(G + 0x3354) + idx * 16);
    idx = *(s32 *)(*(u8 **)(G + off + 8) + 44 * M);
    result = *(s32 *)(*(u8 **)(G + 0x3354) + idx * 16 + 4);
    *(s32 *)(G + 0x3238) = result;
    return result;
}
