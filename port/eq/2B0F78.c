#include "common.h"

f32 atan2f(f32 farg0, f32 farg1);
s32 func_002B0DB0(s32 arg0, s32 arg1);
extern f32 D_0038756C;
extern f32 D_00387570;
extern f32 D_00387574;
extern f32 D_00387578;
extern f32 D_0038757C;
extern f32 D_00387580;
extern f32 D_00387584;
extern f32 D_00387588;
extern f32 D_0038758C;
extern f32 D_00387590;
extern f32 D_00387594;
extern f32 D_00387598;
extern f32 D_0038759C;
extern f32 D_003875A0;
extern f32 D_003875A4;
extern f32 D_003875A8;
extern f32 D_003875AC;
extern f32 D_003875B0;
extern f32 D_003875B4;
extern f32 D_003875B8;
extern f32 D_003875BC;
extern f32 D_003875C0;
extern f32 D_003875C4;
extern f32 D_003875C8;
extern f32 D_003875CC;
extern f32 D_003875D0;
extern f32 D_003875D4;
extern f32 D_003875D8;

#define ABSF(x) (((x) < 0.0f) ? -(x) : (x))

void func_002B0F78(s32 arg0, s32 arg1, f32 farg0) {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f20;

    f4 = *(f32 *)(arg0 + 0x15C);
    f20 = f4;
    if (arg1 == 1) {
        if (func_002B0DB0(arg0, 0x05000000) != 0) {
            f0 = atan2f(*(f32 *)(arg0 + 0x9C), -*(f32 *)(arg0 + 0xA0));
            f20 = f0 + *(f32 *)(arg0 + 0x70);
            if (f20 < D_0038756C) {
                f20 = f20 + D_00387570;
            }
            if (D_00387574 < f20) {
                f20 = f20 - D_00387578;
            }
        }
    } else if (arg1 == 2) {
        f0 = farg0 * *(f32 *)(arg0 + 0x9C);
        f20 = f4 + f0;
        if (f20 < D_0038757C) {
            f20 = f20 + D_00387580;
        }
        if (D_00387584 < f20) {
            f20 = f20 - D_00387588;
        }
    }
    f3 = f20 - f4;

    if (f3 < D_0038758C) {
        f3 = f3 + D_00387590;
    }
    f1 = f3;
    if (D_00387594 < f3) {
        f3 = f3 - D_00387598;
        f1 = f3;
    }
    f2 = ABSF(f1);
    if (farg0 < f2) {
        if (0.0f < f1) {
            f1 = farg0;
        } else {
            f1 = -farg0;
        }
        f2 = ABSF(f1);
    }
    f0 = ABSF(f3);
    if (f2 < f0) {
        f1 = f4 + f1;
        *(f32 *)(arg0 + 0x15C) = f1;
        if (f1 < D_0038759C) {
            *(f32 *)(arg0 + 0x15C) = f1 + D_003875A0;
        }
        f4 = *(f32 *)(arg0 + 0x15C);
        if (D_003875A4 < f4) {
            f4 = f4 - D_003875A8;
            *(f32 *)(arg0 + 0x15C) = f4;
        }
    } else {
        *(f32 *)(arg0 + 0x15C) = f20;
        f4 = f20;
    }

    f6 = *(f32 *)(arg0 + 0xE4);
    f2 = f4 - f6;
    if (f2 < D_003875AC) {
        f2 = f2 + D_003875B0;
    }
    if (D_003875B4 < f2) {
        f2 = f2 - D_003875B8;
    }
    f3 = f2 * D_003875BC;
    f1 = ABSF(f3);
    f5 = D_003875C0;
    if (f1 < f5) {
        if (0.0f < f3) {
            f3 = D_003875C0;
        } else {
            f3 = D_003875C4;
        }
        f1 = D_003875C8;
        f0 = ABSF(f2);
    } else {
        f0 = ABSF(f2);
    }
    if (f1 < f0) {
        f1 = f6 + f3;
        *(f32 *)(arg0 + 0xE4) = f1;
        if (f1 < D_003875CC) {
            *(f32 *)(arg0 + 0xE4) = f1 + D_003875D0;
        }
        f1 = *(f32 *)(arg0 + 0xE4);
        if (D_003875D4 < f1) {
            *(f32 *)(arg0 + 0xE4) = f1 - D_003875D8;
        }
    } else {
        *(f32 *)(arg0 + 0xE4) = f4;
    }
}
