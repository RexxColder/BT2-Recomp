#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387F2C;
extern s32 D_003B26B0;

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void func_002980A8(s32 arg0, s32 arg1);
s32 func_002980C0(void);
void func_00298240(s32 arg0, u8 *arg1);

s32 func_002AB488(u8 *arg0) {
    u8 *ctx;
    u8 *sub;
    s32 v5;
    s32 v6;
    s32 v8;
    s32 v9;
    s32 v12;
    s32 v14;
    s32 q;

    ctx = D_003876A0;
    switch (*(s32 *)arg0) {
    case 0:
        sub = *(u8 **)(arg0 + 0x14);
        v5 = *(s32 *)(sub + 0x24);
        v6 = 1;
        if (v5 == 0 || *(s32 *)(sub + 0x28) == v5) {
            *(s32 *)(arg0 + 0x8) = -1;
        } else {
            *(s32 *)(sub + 0x28) = v5;
            *(s32 *)(arg0 + 0x8) = v5;
        }
        if (*(s32 *)(arg0 + 0x8) > 0) {
            v8 = func_00100ED0(*(s32 *)(arg0 + 0x8), *(s32 *)(ctx + 0x14), 1);
            v6 = 0;
            *(s32 *)(ctx + 0x14) = v8;
        }

        if (D_003B26B0 == 1 && *(s32 *)(sub + 0x2C) != 0) {
            v9 = *(s32 *)(sub + 0x34);
            q = (*(s32 *)(sub + 0x2C) - 44219) / 9;
            if ((*(s32 *)(D_00387F2C + 0x1008) & 1) == 0) {
                v12 = q + 43939;
            } else {
                v12 = q + 44079;
            }
            *(s32 *)(sub + 0x30) = v12;
        } else {
            v9 = *(s32 *)(sub + 0x34);
            *(s32 *)(sub + 0x30) = v9;
        }
        v12 = *(s32 *)(sub + 0x30);
        if (v9 == v12) {
            v12 = -1;
        } else {
            *(s32 *)(sub + 0x34) = v12;
        }
        *(s32 *)(arg0 + 0xC) = v12;

        if (*(s32 *)(arg0 + 0xC) > 0) {
            v14 = func_00100ED0(*(s32 *)(arg0 + 0xC), *(s32 *)(ctx + 0xC), v6);
            v6 = 0;
            *(s32 *)(ctx + 0xC) = v14;
        }
        if (v6 != 0) {
            return 1;
        }
        func_00100FC8(1);
        *(s32 *)arg0 = *(s32 *)arg0 + 1;
        return 0;

    case 1:
        if (func_00100FC8(0) != 0) {
            *(s32 *)arg0 = *(s32 *)arg0 + 1;
        }
        return 0;

    case 2:
        if (*(s32 *)(arg0 + 0x8) <= 0) {
            *(s32 *)arg0 = 4;
            func_002980A8(3, *(s32 *)(ctx + 0xC));
        } else {
            *(s32 *)arg0 = 3;
            func_002980A8(2, *(s32 *)(ctx + 0x14));
        }
        return 0;

    case 3:
        if (func_002980C0() == 0) {
            return 0;
        }
        if (*(s32 *)(arg0 + 0xC) <= 0) {
            return 1;
        }
        *(s32 *)arg0 = 4;
        func_002980A8(3, *(s32 *)(ctx + 0xC));
        return 0;

    case 4:
        if (func_002980C0() == 0) {
            return 0;
        }
        *(u64 *)(ctx + 0xA0) = 0;
        func_00298240(*(s32 *)(ctx + 0xC), ctx + 0xA0);
        return 1;

    default:
        return 1;
    }
}
