#include "common.h"

s32 func_002C0178(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C67D0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C66E0(s32 arg0, s32 arg1);
s32 func_002C0598(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002C6520(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C6928(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C0608(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002DCE50(s32 arg0);
s32 func_002C6748(s32 arg0);

s32 func_002C62E0(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    u8 sp[0x30];
    s32 s0;
    s32 v;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 t;
    s32 r1arg;
    s32 useB4;

    *arg1 = 0;
    s0 = *(s32 *)(arg0 + 0x1FC8);
    *arg2 = 0;
    *arg3 = 0;
    v = func_002C0178((s32)arg0, s0, (s32)sp);
    if (v != 0) {
        return v;
    }
    if (*(s32 *)(sp + 4) == 0) {
        return 0;
    }

    r1 = func_002C67D0((s32)sp, 0xCE, (s32)(sp + 0x20));
    if (r1 == *(s32 *)sp) {
        *arg1 = 4;
        *arg2 = *(s32 *)(sp + 0x20);
        if ((*(s32 *)(sp + 0x20) & 0x80) != 0) {
            return 0;
        }
        func_002C0598((s32)arg0, s0, (s32)(sp + 0x24), (s32)(sp + 0x28));
        v = func_002C6520((s32)sp, *(s32 *)(sp + 0x20), *(s32 *)(sp + 0x24));
        if (v != 0) {
            *(s32 *)(sp + 0x24) = 0;
            if (*(s32 *)(sp + 0xC) != 0) {
                t = *(s32 *)(sp + 8) + *(s32 *)(sp + 0xC);
            } else {
                t = *(s32 *)sp + *(s32 *)(sp + 4);
            }
            if (*(s32 *)(sp + 0x28) != t) {
                *(s32 *)(sp + 0x28) = t;
                v = func_002C6928((s32)sp, 0xCC, (s32)(sp + 0x2C));
                func_002C0608((s32)arg0, s0, v, *(s32 *)(sp + 0x28));
                *(s32 *)(sp + 0x24) = v;
            }
        }

        if (*(s32 *)(sp + 0x24) == 0) {
            return func_002C6748((s32)arg0);
        }
        r2 = func_002DCE50(*(s32 *)(sp + 0x24));
        *(s32 *)(sp + 0x2C) = r2;
        useB4 = 0;
        r1arg = 0;
        if (r2 == 8) {
            if ((*(s32 *)(sp + 0x20) & 0x40) != 0) {
                r1arg = 8;
                useB4 = 1;
            }
        } else if (r2 == 4) {
            if ((*(s32 *)(sp + 0x20) & 0x48) != 0) {
                r1arg = 4;
                useB4 = 1;
            }
        }
        if (useB4 != 0) {
            r3 = func_002C67D0((s32)sp, r1arg, (s32)(sp + 0x20));
            if (r3 == 0 || r3 == *(s32 *)(sp + 0x24)) {
                return func_002C6748((s32)arg0);
            }
        }
        v = func_002C66E0((s32)sp, *(s32 *)(sp + 0x24));
        *arg1 = v;
        return 0;
    }

    if (r1 != 0) {
        v = func_002C66E0((s32)sp, r1);
        *arg1 = v;
    } else {
        t = *(s32 *)(sp + 4) + *(s32 *)(sp + 0xC) - 3;
        if (t < 0) {
            t = 0;
        }
        *arg1 = t;
    }
    if (*arg1 <= 0) {
        return 0;
    }
    *arg3 = 1;
    return 0;
}
