#include "common.h"

extern s32 D_003876A0;

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void EftStage_ResetAll(void);
void func_002720B8(void);
void func_00280BB0(s32 arg0);
void func_00134688(void);
void func_002980A8(s32 arg0, s32 arg1);
s32 func_002980C0(void);
s32 EftBurst_IsBusy(void);
void func_00284E68(s32 arg0, s32 arg1, f32 farg0);
s32 func_00284E08(s32 arg0);
void EftBurst_End(void);
void func_00272070(void);
void func_001F6B00(void);
void func_0011E7F8(void);
void _InitSys(void);
void func_00280BC0(void);
void func_0028BB60(s32 arg0);

/* Scripted boot/shutdown sequencer: a0[0] is the step, each step either acts and advances, or waits
 * until its condition holds (returns 0 while waiting). Step 11 returns 1 when the sequence is done. */
s32 func_00103CB0(s32 *a1) {
    s32 result = 1;
    s32 p;
    s32 v7;

    switch (*a1) {
    case 0:
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x2000LL;
        *a1 = *a1 + 1;
        return 0;

    case 1:
        if (a1[1] == 3) {
            p = 0x3E0A;
        } else {
            p = 0x3E09;
        }
        *(s32 *)(D_003876A0 + 0x2C) = func_00100ED0(p, 0, 1);
        func_00100FC8(1);
        EftStage_ResetAll();
        func_002720B8();
        func_00280BB0(1);
        *a1 = *a1 + 1;
        return 0;

    case 2:
        result = func_00100FC8(0);
        if (result == 0) {
            return result;
        }
        *a1 = *a1 + 1;
        return 0;

    case 3:
        if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100LL) != 0) {
            return 0;
        }
        func_00134688();
        *a1 = *a1 + 1;
        return 0;

    case 4:
        *(s32 *)(D_003876A0 + 4) = func_00100ED0(*(s32 *)(D_003876A0 + 0xD4) + 0x3DE7,
                                                 *(s32 *)(D_003876A0 + 4), 1);
        *(s32 *)(D_003876A0 + 0xC) = func_00100ED0(*(s32 *)(D_003876A0 + 0xD4) + 0x33D4,
                                                   *(s32 *)(D_003876A0 + 0xC), 0);
        func_00100FC8(1);
        *a1 = *a1 + 1;
        return 0;

    case 5:
        result = func_00100FC8(0);
        if (result == 0) {
            return result;
        }
        *a1 = *a1 + 1;
        func_002980A8(2, *(s32 *)(D_003876A0 + 0xC));
        *a1 = *a1 + 1;
        return 0;

    case 6:
        func_002980A8(2, *(s32 *)(D_003876A0 + 0xC));
        *a1 = *a1 + 1;
        return 0;

    case 7:
        if (func_002980C0() == 0) {
            return 0;
        }
        *a1 = *a1 + 1;
        return 0;

    case 8:
        if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100LL) != 0) {
            return 0;
        }
        if (EftBurst_IsBusy() != 0) {
            return 0;
        }
        func_00284E68(2, 0, 1.0f);
        *a1 = *a1 + 1;
        return 0;

    case 9:
        if (func_00284E08(2) == 0) {
            return 0;
        }
        EftBurst_End();
        *a1 = *a1 + 1;
        return 0;

    case 10:
        v7 = D_003876A0;
        if ((*(s64 *)(v7 + 0x4D8) & 0x100LL) != 0) {
            return 0;
        }
        *(s64 *)(v7 + 0x4D8) = *(s64 *)(v7 + 0x4D8) & ~0x2000LL;
        func_00272070();
        func_001F6B00();
        func_0011E7F8();
        _InitSys();
        func_00280BC0();
        func_0028BB60(*(s32 *)(v7 + 0x2C));
        *(s32 *)(v7 + 0x2C) = 0;
        *a1 = *a1 + 1;
        return 0;

    case 11:
        func_00284E68(2, 1, 1.0f);
        return 1;

    default:
        return result;
    }
}
