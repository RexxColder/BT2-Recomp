#include "common.h"

s32 func_002DFBC8(s32 arg0);
s32 func_002E2730(s32 arg0, s32 arg1);
s32 func_002E2F08(s32 arg0, s32 arg1);
s32 func_002E3028(s32 arg0, s32 arg1);
s32 func_002E33F8(s32 arg0, s32 arg1);
s32 func_002E63D8(s32 arg0, s32 arg1);
s32 func_002E6940(s32 arg0, s32 arg1);
void func_003061A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002E23A0(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 sp10[4];
    s32 s0;
    s32 v1;
    s32 vt;
    u8 *s3;

    s3 = (u8 *)arg0 + 0x160;
    *(s32 *)(s3 + 0x494) = 0;
    *(s32 *)(s3 + 0x498) = 0;
    *(s32 *)(s3 + 0x308) = 0;
    *(s32 *)(s3 + 0x30C) = 0;
    for (;;) {
        s0 = func_002DFBC8(arg1);
        if (s0 == 0) {
            break;
        }
        vt = *(s32 *)arg1;
        ((void (*)(s32, s32, s32, s32))(*(s32 *)(vt + 0x18)))(arg1, 1, 0x7FFFFFFF, (s32)sp);
        v1 = 0;
        if (s0 == 0x10) {
            v1 = func_002E33F8(arg0, sp[0]);
        } else if (s0 < 0x11) {
            if (s0 == 4) {
                v1 = func_002E6940(arg0, sp[0]);
            } else if (s0 == 8) {
                v1 = func_002E63D8(arg0, sp[0]);
            }
        } else if (s0 == 0x40) {
            v1 = func_002E2730(arg0, sp[0]);
        } else if (s0 < 0x41) {
            if (s0 == 0x20) {
                v1 = func_002E3028(arg0, sp[0]);
            }
        } else if (s0 == 0x80) {
            v1 = func_002E2F08(arg0, sp[0]);
        }
        if (v1 != 0) {
            func_003061A8((s32)sp, v1 - sp[0], (s32)sp, (s32)sp10);
            vt = *(s32 *)arg1;
            ((void (*)(s32, s32, s32))(*(s32 *)(vt + 0x20)))(arg1, 0, (s32)sp);
            vt = *(s32 *)arg1;
            ((void (*)(s32, s32, s32))(*(s32 *)(vt + 0x1C)))(arg1, 1, (s32)sp10);
            if (*(s32 *)(s3 + 0x494) != 0) {
                break;
            }
        } else {
            vt = *(s32 *)arg1;
            ((void (*)(s32, s32, s32))(*(s32 *)(vt + 0x1C)))(arg1, 1, (s32)sp);
            break;
        }
    }
    *(s32 *)(s3 + 0x49C) = *(s32 *)(s3 + 0x49C) + *(s32 *)(s3 + 0x494);
    *(s32 *)(s3 + 0x4A0) = *(s32 *)(s3 + 0x4A0) + *(s32 *)(s3 + 0x498);
    return (*(s32 *)(s3 + 0x494) == 0) ? 0 : -2;
}
