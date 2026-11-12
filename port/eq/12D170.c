#include "common.h"

u8 *func_0012B9B0(void);
s32 func_00129720(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_00129A50(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
s32 func_0012E840(u8 *p);
void func_0012DA70(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, u8 *arg6,
                   u8 *arg7, u8 *arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s64 arg13);

s32 func_0012D170(u8 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s64 arg5,
                  s32 arg6) {
    u8 sp[0x1C0];
    u8 *scr;
    u8 *cur;
    u8 *pts;
    u8 *v15;
    u8 *p;
    s32 k;
    s32 cnt;
    s32 idx;
    s32 off;
    s32 quot;
    s32 v16;
    s32 v24;
    s32 maxv;

    p = func_0012B9B0();
    cnt = 3;
    for (k = 4; k >= 0; k--) {
        cnt = func_00129720(arg0, arg0, p, cnt);
        p += 16;
    }
    if (cnt == 0) {
        return 0;
    }

    scr = sp + 0x30;
    cur = sp + 0xC0;
    func_00129A50(scr, cur, arg0, cnt);

    idx = 2;
    if (!(idx < cnt)) {
        return 0;
    }

    maxv = 0xFFFFFF;
    pts = sp + 0x58;
    v15 = arg0 + 0x60;
    do {
        off = idx << 4;
        v16 = *(s32 *)(pts - 0x10);
        v24 = *(s32 *)(sp + 0x38);
        quot = ((v24 + v16 + *(s32 *)pts) / 3) >> 8;
        if (arg4 != 0) {
            quot = 0x1000 - quot;
        }

        if (v24 > maxv) {
            *(s32 *)(sp + 0x38) = maxv;
        }
        if (v16 > maxv) {
            *(s32 *)(pts - 0x10) = maxv;
        }
        if (*(s32 *)pts > maxv) {
            *(s32 *)pts = maxv;
        }

        if (func_0012E840(scr) && func_0012E840(scr + off - 0x10) && func_0012E840(scr + off)) {
            idx++;
        } else {
            func_0012DA70(scr, scr + off - 0x10, scr + off, arg0 + 0x20, v15 - 0x10,
                          v15 + 0x20, cur, cur + off - 0x10, cur + off, arg2, arg3, arg1,
                          quot + arg6, arg5);
            idx++;
        }
        pts += 0x10;
        v15 += 0x30;
    } while (idx < cnt);

    return 0;
}
