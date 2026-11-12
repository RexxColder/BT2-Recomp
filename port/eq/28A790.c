#include "common.h"

extern s32 gMcCardCmd;
extern s32 gMcCardStep;
extern u8 gMcCardPort[];
extern u8 D_003B0AA4[];
extern u8 D_003B0AA8[];

s32 sceMcOpen(s32 port, s32 slot, s32 name, s32 mode);
s32 sceMcSync(s32 mode, s32 cmd, s32 *result);
s32 sceMcSeek(s32 fd, s32 offset, s32 origin);
s32 sceMcClose(s32 fd);

/* 0x0028A790: memory-card write state machine (24 steps on gMcCardStep, per-port record of 36 bytes).
   Opens/seeks/closes a file in three passes; steps that wait use sceMcSync and a result of 1 = still ok. */
s32 func_0028A790(s32 port, s32 name) {
    u8 *rec;
    s32 *res;
    s32 ret;
    s32 a2;
    s32 st;
    s32 *cnt;

    if (gMcCardCmd != 0) {
        st = gMcCardStep;
        if (gMcCardCmd != 0x1A) {
            st = 0;
        }
        gMcCardStep = st;
    } else {
        st = gMcCardStep;
    }

    if ((u32)st >= 0x18) {
        return 1;
    }

    switch (st) {
    case 0:
    case 8:
    case 16:
        if (st == 0) {
            rec = gMcCardPort + 36 * port;
            *(s32 *)(rec + 0x1C) = 0;
            gMcCardCmd = 0x1A;
            *(s32 *)(rec + 8) = 0;
            ret = sceMcOpen(port, 0, name + 0x298, 1);
            *(s32 *)(rec + 4) = ret;
        } else if (st == 8) {
            ret = sceMcOpen(port, 0, name + 0x98, 1);
            *(s32 *)(D_003B0AA4 + 36 * port) = ret;
        } else {
            ret = sceMcOpen(port, 0, name + 0x118, 1);
            *(s32 *)(D_003B0AA4 + 36 * port) = ret;
        }
        if (ret < 0) {
            if (ret == -200) {
                sceMcSync(1, 0, 0);
            }
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;

    case 1:
    case 9:
    case 17:
        res = (s32 *)(D_003B0AA8 + 36 * port);
        if (sceMcSync(1, 0, res) != 1) {
            return 0;
        }
        a2 = res[0];
        if (a2 < 0) {
            return 0;
        }
        *(s32 *)(D_003B0AA8 + 36 * port + 0x10) = a2;
        gMcCardStep = gMcCardStep + 1;
        return 0;

    case 2:
    case 10:
    case 18:
        rec = gMcCardPort + 36 * port;
        ret = sceMcSeek(*(s32 *)(rec + 0x18), 0, 2);
        *(s32 *)(rec + 4) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;

    case 3:
    case 11:
    case 19:
        res = (s32 *)(D_003B0AA8 + 36 * port);
        if (sceMcSync(1, 0, res) == 0) {
            return 0;
        }
        a2 = res[0];
        if (a2 < 0) {
            return 0;
        }
        cnt = (s32 *)(D_003B0AA8 + 36 * port + 0x14);
        if (st == 3) {
            *cnt = *cnt - (a2 + 0x3FF) / 0x400 + 0x10;
        } else if (st == 11) {
            *cnt = *cnt - (a2 + 0x3FF) / 0x400 + 1;
        } else {
            *cnt = *cnt - (a2 + 0x3FF) / 0x400 + 0x36;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;

    case 4:
    case 12:
    case 20:
        rec = gMcCardPort + 36 * port;
        ret = sceMcSeek(*(s32 *)(rec + 0x18), 0, 0);
        *(s32 *)(rec + 4) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;

    case 5:
    case 7:
    case 13:
    case 15:
    case 21:
        res = (s32 *)(D_003B0AA8 + 36 * port);
        if (sceMcSync(1, 0, res) == 0) {
            return 0;
        }
        if (res[0] < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;

    case 6:
    case 14:
    case 22:
        rec = gMcCardPort + 36 * port;
        ret = sceMcClose(*(s32 *)(rec + 0x18));
        *(s32 *)(rec + 4) = ret;
        if (ret < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 0;

    case 23:
        res = (s32 *)(D_003B0AA8 + 36 * port);
        if (sceMcSync(1, 0, res) == 0) {
            return 0;
        }
        if (res[0] < 0) {
            return 0;
        }
        gMcCardStep = gMcCardStep + 1;
        return 1;
    }
    return 1;
}
