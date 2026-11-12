#include "common.h"

extern u8 *D_003876A4;
extern u8 *D_00387F2C;

extern s32 func_00249288(s32 a0, s32 inCount, u8 *in);

/* flag of table entry `item`: s16 at +2 of a 4-byte record (two bases depending on the id range) */
#define ITEM_FLAG(base, item) \
    (*(s16 *)((base) + (item) * 4 + ((item) >= 98 ? 0x25E4 : 0x25E8) + 2))

#define ENTRY(arr, i) ((arr) + (i) * 44)

/* Filters a list of 44-byte command entries into out[] (dropping entries by game mode and per-id flags),
   pads the count to a multiple of 7, mirrors the list +0x1810 bytes up and appends 10 per-slot entries. */
void func_00248708(s32 *outCnt, u8 *out, s32 *inCnt, u8 **inPtr) {
    u8 *cam = D_003876A4;
    u8 *tblA = *(u8 **)(cam + 0x4C8);
    u8 *tblB = *(u8 **)(cam + 0x4CC);
    s32 mode = *(s32 *)(cam + 0x1C);
    u32 F = 0;
    s32 i;
    s32 j;
    s32 n;
    s32 rem;
    s32 pad;
    u8 *e;
    u8 *o;
    u8 *in;
    s32 item;
    s32 cmd;
    s32 idx;

    if ((u32)(mode - 10) < 0xC) {
        F = 6;
    }
    if ((u32)(mode - 53) < 6) {
        F |= 6;
        if (mode != 0x37) {
            F |= 8;
        } else {
            F |= 0x10;
        }
    }
    *outCnt = 0;
    if ((u32)(mode - 38) < 4) {
        F |= 0xC;
    }

    if (*inCnt > 0) {
        for (i = 0; i < *inCnt; i++) {
            in = *inPtr;
            e = in + i * 44;
            if (*(s32 *)(e + 4) != 0) {
                /* a list entry: keep the ids that pass the flags */
                o = ENTRY(out, *outCnt);
                *(s32 *)(o + 4) = 0;
                in = *inPtr;
                for (j = 0; j < *(s32 *)(in + i * 44 + 4); j++) {
                    item = *(s32 *)(in + i * 44 + 8 + j * 4);
                    if (F & 0x10) {
                        /* keep */
                    } else if (ITEM_FLAG(D_00387F2C, item) != 0) {
                        /* keep */
                    } else if (*(s32 *)(D_003876A4 + 0x4C8) == 0 || *(s32 *)(D_003876A4 + 0x4CC) == 0) {
                        in = *inPtr;
                        continue;
                    } else if (ITEM_FLAG(tblA, item) != 0) {
                        /* keep */
                    } else if (ITEM_FLAG(tblB, item) == 0) {
                        in = *inPtr;
                        continue;
                    }
                    o = ENTRY(out, *outCnt);
                    *(s32 *)(o + 8 + *(s32 *)(o + 4) * 4) = item;
                    o = ENTRY(out, *outCnt);
                    *(s32 *)(o + 4) = *(s32 *)(o + 4) + 1;
                    in = *inPtr;
                }
                o = ENTRY(out, *outCnt);
                n = *(s32 *)(o + 4);
                if (n < 2) {
                    if (n != 1) {
                        *(s32 *)o = 0x83;
                        *outCnt = *outCnt + 1;
                        continue;
                    }
                    *(s32 *)(o + 4) = 0;
                } else if (!(F & 8)) {
                    *(s32 *)o = *(s32 *)(o + 8);
                    *outCnt = *outCnt + 1;
                    continue;
                } else {
                    *(s32 *)(o + 4) = 0;
                }
                o = ENTRY(out, *outCnt);
                *(s32 *)o = *(s32 *)(o + 8);
                *outCnt = *outCnt + 1;
                continue;
            }

            /* single command */
            cmd = *(s32 *)e;
            if (cmd == 0x82) {
                if (F & 4) {
                    *(s32 *)ENTRY(out, *outCnt) = 0x85;
                } else {
                    __builtin_memcpy(ENTRY(out, *outCnt), e, 44);
                }
                *outCnt = *outCnt + 1;
            } else if (cmd == 0x84) {
                if (F & 2) {
                    *(s32 *)ENTRY(out, *outCnt) = 0x85;
                } else {
                    __builtin_memcpy(ENTRY(out, *outCnt), e, 44);
                }
                *outCnt = *outCnt + 1;
            } else {
                if (F & 0x10) {
                    __builtin_memcpy(ENTRY(out, *outCnt), e, 44);
                    *outCnt = *outCnt + 1;
                } else if (ITEM_FLAG(D_00387F2C, cmd) != 0) {
                    __builtin_memcpy(ENTRY(out, *outCnt), e, 44);
                    *outCnt = *outCnt + 1;
                } else if (*(s32 *)(D_003876A4 + 0x4C8) == 0 || *(s32 *)(D_003876A4 + 0x4CC) == 0) {
                    *(s32 *)ENTRY(out, *outCnt) = 0x83;
                    *outCnt = *outCnt + 1;
                } else if (ITEM_FLAG(tblA, *(s32 *)e) != 0 || ITEM_FLAG(tblB, *(s32 *)e) != 0) {
                    __builtin_memcpy(ENTRY(out, *outCnt), e, 44);
                    *outCnt = *outCnt + 1;
                } else {
                    *(s32 *)ENTRY(out, *outCnt) = 0x83;
                    *outCnt = *outCnt + 1;
                }
            }
            if (*(s32 *)(*inPtr + i * 44) == 0x7C) {
                if (F & 1) {
                    *(s32 *)(out + *outCnt * 44 - 44) = 0x85;
                }
            }
        }
    }

    /* pad to a multiple of 7 with empty entries */
    rem = *outCnt % 7;
    if (rem != 0) {
        pad = 7 - rem;
        for (j = 0; j < pad; j++) {
            *(s32 *)ENTRY(out, *outCnt) = 0x83;
            *(s32 *)(ENTRY(out, *outCnt) + 4) = 0;
            *outCnt = *outCnt + 1;
        }
    }
    /* mirror the list */
    for (i = 0; i < *outCnt; i++) {
        __builtin_memcpy(ENTRY(out, i) + 0x1810, ENTRY(out, i), 44);
    }

    if (F & 2) {
        return;
    }
    /* ten per-slot entries */
    {
        u8 *slot = out + 0xCB8;
        s32 so = 0x1DE4;
        s32 fo = 0x9D4;
        for (j = 9; j >= 0; j--) {
            if (*(s32 *)(D_003876A4 + 0x4C8) != 0 && *(s32 *)(D_003876A4 + 0x4CC) != 0) {
                u8 *src;
                s32 hw;
                if (*(u16 *)(tblA + fo + 0x1428) & 1) {
                    idx = func_00249288(*(s16 *)(tblA + so + 0x14), *inCnt, *inPtr);
                    src = ENTRY(out, idx);
                    __builtin_memcpy(slot, src, 44);
                    hw = *(s16 *)(tblA + 0x14 + so);
                    *(s32 *)slot = hw;
                    *(s32 *)(slot + 8) = hw;
                    if (hw == 0x7C && (F & 1)) {
                        *(s32 *)slot = 0x85;
                        *(s32 *)(slot + 4) = 0;
                    }
                }
                if (*(u16 *)(tblB + fo + 0x1428) & 1) {
                    idx = func_00249288(*(s16 *)(tblB + so + 0x14), *inCnt, *inPtr);
                    src = ENTRY(out, idx);
                    __builtin_memcpy(slot + 0x1810, src + 0x1810, 44);
                    hw = *(s16 *)(tblB + 0x14 + so);
                    *(s32 *)(slot + 0x1810) = hw;
                    *(s32 *)(slot + 0x1818) = hw;
                    if (hw == 0x7C && (F & 1)) {
                        *(s32 *)(slot + 0x1810) = 0x85;
                        *(s32 *)(slot + 0x1814) = 0;
                    }
                }
            } else {
                u8 *src;
                s32 hw;
                if (*(u16 *)(D_00387F2C + fo + 0x1428) & 1) {
                    idx = func_00249288(*(s16 *)(D_00387F2C + so + 0x14), *inCnt, *inPtr);
                    src = ENTRY(out, idx);
                    __builtin_memcpy(slot, src, 44);
                    __builtin_memcpy(slot + 0x1810, src + 0x1810, 44);
                    *(s32 *)slot = *(s16 *)(D_00387F2C + so + 0x14);
                    *(s32 *)(slot + 8) = *(s16 *)(D_00387F2C + so + 0x14);
                    *(s32 *)(slot + 0x1810) = *(s16 *)(D_00387F2C + so + 0x14);
                    *(s32 *)(slot + 0x1818) = *(s16 *)(D_00387F2C + so + 0x14);
                    if (*(s16 *)(D_00387F2C + so + 0x14) == 0x7C && (F & 1)) {
                        *(s32 *)slot = 0x85;
                        *(s32 *)(slot + 4) = 0;
                        *(s32 *)(slot + 0x1810) = 0x85;
                        *(s32 *)(slot + 0x1814) = 0;
                    }
                }
            }
            slot += 0x2C;
            so += 0x22;
            fo += 0x22;
        }
    }
}
