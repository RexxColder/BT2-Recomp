#include "common.h"

extern s32 gMcCardCmd;
extern s32 gMcCardStep;
extern s32 gMcCardPort[];
extern s32 D_003B0AA8[];

s32 sceMcOpen(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 sceMcSync(s32 arg0, s32 arg1, void *arg2);
s32 sceMcRead(s32 arg0, void *arg1, s32 arg2);
s32 sceMcClose(s32 arg0);

/* 0x00289628 (McCard_ReadFile): memory-card read state machine, states 0..5 on gMcCardStep, per-port record 36 bytes. */
s32 McCard_ReadFile(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 st;
    s32 result;
    s32 ret;
    s32 a2;
    u8 *p;
    s32 *dp;
    s32 *flag;

    if (gMcCardCmd != 0) {
        st = gMcCardStep;
        if (gMcCardCmd != 0x10) {
            st = 0;
        }
        gMcCardStep = st;
    } else {
        st = gMcCardStep;
    }

    result = 1;
    if ((u32)st >= 6) {
        return result;
    }

    switch (st) {
    case 0:
        p = (u8 *)gMcCardPort + 36 * arg0;
        *(s32 *)p = 0;
        gMcCardCmd = 0x10;
        *(s32 *)(p + 8) = 0;
        ret = sceMcOpen(arg0, 0, arg3 + 0x298, 1);
        *(s32 *)(p + 4) = ret;
        if (ret >= 0) {
            gMcCardStep += 1;
            return 0;
        }
        if (ret == -200) {
            sceMcSync(1, 0, NULL);
        }
        return 0;
    case 1:
        dp = &D_003B0AA8[9 * arg0];
        result = sceMcSync(1, 0, dp);
        if (result != 0) {
            a2 = dp[0];
            if (a2 < 0) {
                gMcCardStep = 0;
                return 0;
            }
            D_003B0AA8[9 * arg0 + 4] = a2;
            gMcCardStep += 1;
            return 0;
        }
        return result;
    case 2:
        p = (u8 *)gMcCardPort + 36 * arg0;
        ret = sceMcRead(*(s32 *)(p + 0x18), arg1, arg2);
        *(s32 *)(p + 4) = ret;
        if (ret >= 0) {
            gMcCardStep += 1;
        }
        return 0;
    case 3:
        dp = &D_003B0AA8[9 * arg0];
        result = sceMcSync(1, 0, dp);
        if (result != 0) {
            a2 = dp[0];
            if (a2 < 0) {
                gMcCardStep = 0;
                return 0;
            }
            flag = (s32 *)((u8 *)D_003B0AA8 - 8 + 36 * arg0);
            if (a2 == arg2) {
                *flag = *flag | 2;
            } else {
                *flag = *flag | 1;
            }
            gMcCardStep += 1;
            return 0;
        }
        return result;
    case 4:
        p = (u8 *)gMcCardPort + 36 * arg0;
        ret = sceMcClose(*(s32 *)(p + 0x18));
        *(s32 *)(p + 4) = ret;
        if (ret >= 0) {
            gMcCardStep += 1;
        }
        return 0;
    case 5:
        dp = &D_003B0AA8[9 * arg0];
        result = sceMcSync(1, 0, dp);
        if (result != 0) {
            if (dp[0] >= 0) {
                gMcCardStep += 1;
                return 1;
            }
            gMcCardStep = 0;
            return 0;
        }
        return result;
    default:
        return result;
    }
}
