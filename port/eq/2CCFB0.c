#include "common.h"

void func_002CD0C8(s32 arg0);
s32 func_002CD108(s32 arg0);
s32 func_002CD138(s32 arg0);
s32 func_002CD4D0(s32 arg0);
s32 func_002CD570(s32 arg0);
s32 func_002CD5E0(s32 arg0);
s64 func_002D2750(void);
s32 func_002D2858(s32 arg0, s64 arg1);

/* 0x002CCFB0: state step of the record at arg0. Only runs while the state word at +0x48 is in
 * 1..4 and the pending flag at +0x44 is set: clears the flag, takes a reference value, runs
 * func_002CD0C8 for states 2..4, then dispatches on the state (0..6) to one of the
 * func_002CD1xx/4xx/5xx/5E0 handlers (states 1, 2, 3, 4, 6; states 0 and 5 keep it) and stores
 * the new state. Ends with a tail call to func_002D2858 with the sub-record at +0x3760 and the
 * difference of the two reference values. Early exits return 0. */
s32 func_002CCFB0(u8 *arg0) {
    s32 s0 = *(s32 *)(arg0 + 0x48);
    s32 s2;

    if ((u32)(s0 - 1) >= 4) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x44) == 0) {
        return 0;
    }

    *(s32 *)(arg0 + 0x44) = 0;
    s2 = func_002D2750();
    if ((u32)(s0 - 2) < 3) {
        func_002CD0C8((s32)arg0);
    }
    s0 = *(s32 *)(arg0 + 0x48);

    if ((u32)s0 < 7) {
        switch (s0) {
            case 1:
                s0 = func_002CD108((s32)arg0);
                break;
            case 2:
                s0 = func_002CD138((s32)arg0);
                break;
            case 3:
                s0 = func_002CD4D0((s32)arg0);
                break;
            case 4:
                s0 = func_002CD570((s32)arg0);
                break;
            case 6:
                s0 = func_002CD5E0((s32)arg0);
                break;
            default:
                break;
        }
    }
    *(s32 *)(arg0 + 0x48) = s0;

    s0 = func_002D2750();
    return func_002D2858((s32)(arg0 + 0x3760), s0 - s2);
}
