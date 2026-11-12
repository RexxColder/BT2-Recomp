#include "common.h"

extern u8 *D_003876A0;

void EftStage_ResetAll(void);
void func_002720B8();
void func_00280BB0(s32 arg0);
s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void func_002980A8(s32 arg0, s32 arg1);
s32 func_002980C0();
void func_00272070(s64 arg0);
void func_001F6B00(void);
void func_0011E7F8();
void _InitSys();
void func_00280BC0(void);

s32 func_00103F50(s32 *arg0) {
    s64 flags;

    if ((u32)arg0[0] >= 6) {
        return 1;
    }
    switch (arg0[0]) {
        case 0:
            *(s64 *)(D_003876A0 + 0x4D8) |= 0x2000;
            arg0[0]++;
            return 0;
        case 1:
            EftStage_ResetAll();
            func_002720B8();
            func_00280BB0(1);
            *(s32 *)(D_003876A0 + 0x4) =
                func_00100ED0(*(s32 *)(D_003876A0 + 0xD4) + 0x3DE7, *(s32 *)(D_003876A0 + 0x4), 1);
            *(s32 *)(D_003876A0 + 0xC) =
                func_00100ED0(*(s32 *)(D_003876A0 + 0xD4) + 0x33D4, *(s32 *)(D_003876A0 + 0xC), 0);
            func_00100FC8(1);
            arg0[0]++;
            return 0;
        case 2:
            if (func_00100FC8(0) != 0) {
                arg0[0]++;
            }
            return 0;
        case 3:
            func_002980A8(2, *(s32 *)(D_003876A0 + 0xC));
            arg0[0]++;
            return 0;
        case 4:
            if (func_002980C0() != 0) {
                arg0[0]++;
            }
            return 0;
        case 5:
            flags = *(s64 *)(D_003876A0 + 0x4D8);
            if ((flags & 0x100) != 0) {
                return 0;
            }
            *(s64 *)(D_003876A0 + 0x4D8) = flags & (s64)-0x2001;
            func_00272070(flags);
            func_001F6B00();
            func_0011E7F8();
            _InitSys();
            func_00280BC0();
            return 1;
    }
    return 0;
}
