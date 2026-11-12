#include "common.h"

extern s32 D_003876A0;
extern s16 D_0033F408[];
s32 func_0020A658(s32 arg0);
s32 func_0020AF80(s32 arg0);
s32 func_0020C6D0(s32 arg0);

s32 func_00105F78(s32 arg0) {
    u8 *p;
    u8 *g;
    s32 tbl[3];
    s32 cnt;
    s32 idx;
    s32 sec;
    s32 m4;
    s32 c6;
    s32 c8;
    s32 c10;
    s32 t;

    p = (u8 *)arg0;
    if (func_0020A658(0) != 0) {
        return 0;
    }
    if (func_0020A658(1) != 0) {
        return 0;
    }
    if (func_0020AF80(0) != 0) {
        return 0;
    }
    if (func_0020AF80(1) != 0) {
        return 0;
    }
    g = (u8 *)D_003876A0;
    if ((*(u64 *)(g + 0x4D8) & 0x2000) != 0) {
        return 0;
    }

    tbl[0] = 34;
    tbl[1] = 32;
    tbl[2] = 34;

    cnt = *(u32 *)p;
    idx = (s32)(cnt % 3);
    *(u32 *)p = cnt + 1;

    m4 = *(s16 *)(p + 4);
    sec = *(u16 *)(p + 0xA) + tbl[idx];
    *(s16 *)(p + 0xA) = (s16)sec;
    c10 = (s16)sec;

    if (m4 < 9) {
        c6 = *(s16 *)(p + 6);
        c8 = *(s16 *)(p + 8);
        c10 = *(s16 *)(p + 0xA);
    } else {
        c6 = *(s16 *)(p + 6);
        if (c6 < 59) {
            c8 = *(s16 *)(p + 8);
            c10 = *(s16 *)(p + 0xA);
        } else {
            c8 = *(s16 *)(p + 8);
            if (c8 < 59) {
                c10 = *(s16 *)(p + 0xA);
            } else if ((s16)sec >= 999) {
                *(s16 *)(p + 4) = 9;
                *(s16 *)(p + 8) = 59;
                *(s16 *)(p + 0xA) = 999;
                *(s16 *)(p + 6) = 59;
                goto L1110;
            } else {
                c10 = *(s16 *)(p + 0xA);
            }
        }
    }

    if (c10 >= 1000) {
        c10 = c10 - 1000;
        c8 = c8 + 1;
        *(s16 *)(p + 0xA) = (s16)c10;
        *(s16 *)(p + 8) = (s16)c8;
    }

    if ((s16)c8 >= 60) {
        *(s16 *)(p + 8) = (s16)(c8 - 60);
        c6 = c6 + 1;
        *(s16 *)(p + 6) = (s16)c6;
    }

    if ((s16)c6 >= 60) {
        *(s16 *)(p + 6) = (s16)(c6 - 60);
        *(s16 *)(p + 4) = (s16)(m4 + 1);
    }

L1110:
    g = (u8 *)D_003876A0;
    if (*(s32 *)(g + 0xC0) == 0) {
        *(s16 *)(p + 0xC) = 0;
        return 0;
    }
    idx = *(s32 *)(g + 0xC0);
    t = D_0033F408[idx];
    {
        s32 cur6 = *(s16 *)(p + 6);
        s32 cur8 = *(s16 *)(p + 8);
        s32 total = cur8 + 60 * cur6;
        if (total < t) {
            *(s16 *)(p + 0xC) = (s16)(((u16)D_0033F408[idx]) - total);
            return 0;
        }
        *(s16 *)(p + 0xC) = 0;
        return 1;
    }
}
