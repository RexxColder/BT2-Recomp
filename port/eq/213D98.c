#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00385A6C;

#define S32(p, off) (*(s32 *)((u8 *)(p) + (off)))

void *BtlChar_GetPos(void *a0);
void BtlChar_SetSmallVibration(f32 f, void *a0);
void *BtlMember_GetActiveGauge(void *a0);
s32 BtlMember_IsHealthEmpty_2127F8(void *a0);
s32 BtlObjXf_Update(void *a0);
s32 BtlPad_Test4C(void *a0, s32 a1);
s32 func_001FA3A0(void *a0);
s32 func_001FA3A8(s32 a0);
s32 func_00203C58(void *a0, s64 a1);
s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_00211328(void *a0, s32 a1, s32 a2);
void func_002113C0(void *a0, s32 a1, s32 a2, s32 a3);
s32 func_00217488(void *a0);

void func_00213D98(void *arg0) {
    u8 *p;
    s32 n;
    s32 c;

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x3800) && (func_00211310(arg0, 0, 0x100000) == 0)) {
        if (func_00211310(arg0, 5, 1) == 0) {
            S32(arg0, 0x998) = 0;
            if (!(func_001FA3A8(BtlObjXf_Update(arg0)) & 2)) {
                func_002113C0(arg0, 5, 0x200, 0);
            }
        }
        if (func_00211310(arg0, 5, 0x40) == 0) {
            S32(arg0, 0x9A0) = 0;
            S32(arg0, 0x9A8) = 0;
        }
        if (func_00211310(arg0, 6, 4) == 0) {
            n = S32(arg0, 0xBC8);
            S32(arg0, 0xBC0) = 0;
            S32(arg0, 0xBC4) = 0;
            if (n > 0) {
                S32(arg0, 0xBC8) = n - 1;
            }
            p = (u8 *)arg0 + 0xBBF;
            if (func_00211328(arg0, 6, 4) != 0) {
                c = 0x27;
                do {
                    c -= 1;
                    *p = 0;
                    p -= 1;
                } while (c >= 0);
            }
        }
        if (S32(arg0, 0xB74) > 0) {
            if (func_00211310(arg0, 0xD, 8) == 0) {
                S32(arg0, 0xB74) = S32(arg0, 0xB74) - 1;
                BtlChar_SetSmallVibration(D_00385A6C, arg0);
                func_002113C0(arg0, 0xF, 1, 1);
                if (BtlPad_Test4C(arg0, 0x18) != 0) {
                    n = S32(arg0, 0xB74) - 2;
                    S32(arg0, 0xB74) = (n < 0) ? 0 : n;
                }
            }
            if (BtlMember_IsHealthEmpty_2127F8(arg0) != 0) {
                S32(arg0, 0xB74) = 0;
            }
        }
        n = S32(arg0, 0xB8C);
        if (n > 0) {
            S32(arg0, 0xB8C) = n - 1;
            func_002113C0(arg0, 9, 0x20000000, 1);
            func_002113C0(arg0, 6, 8, 1);
        }
        n = S32(arg0, 0xB90);
        if (n > 0) {
            S32(arg0, 0xB90) = n - 1;
        }
        n = S32(arg0, 0xB7C);
        if (n > 0) {
            S32(arg0, 0xB7C) = n - 1;
            if (BtlMember_IsHealthEmpty_2127F8(arg0) != 0) {
                S32(arg0, 0xB7C) = 0;
            }
        }
        n = S32(arg0, 0xB78);
        if (n > 0) {
            S32(arg0, 0xB78) = n - 1;
        }
        n = S32(arg0, 0xA14);
        if (n <= 0) {
            S32(arg0, 0xA10) = 0;
        } else {
            S32(arg0, 0xA14) = n - 1;
        }
        n = S32(arg0, 0xA34);
        if (n > 0) {
            S32(arg0, 0xA34) = n - 1;
            if (func_00203C58(arg0, (s64)0x8000 << 22) != 0) {
                n = S32(arg0, 0xA34);
                if (n > 0) {
                    S32(arg0, 0xA34) = n - 1;
                }
            }
        }
        n = S32(arg0, 0xB84);
        if (n > 0) {
            S32(arg0, 0xB84) = n - 1;
        }
        if ((func_00211310(arg0, 1, 0x800000) == 0) && (func_00211310(arg0, 0, 0x120) == 0) &&
            (func_00211310(arg0, 0, 2) != 0)) {
            u8 *pos = (u8 *)BtlChar_GetPos(arg0);
            S32(pos, 0xDC) = S32(pos, 0xDC) + 1;
        } else {
            S32(BtlChar_GetPos(arg0), 0xDC) = 0;
        }
        if (func_00217488(arg0) != 0xE4) {
            n = S32(arg0, 0xA40) - 1;
            S32(arg0, 0xA40) = n;
            if (n < 0) {
                S32(arg0, 0xA40) = 0;
                S32(arg0, 0xA3C) = 0;
            }
        }
        if (!(func_001FA3A8(BtlObjXf_Update(arg0)) & 0x100000)) {
            S32(arg0, 0xB94) = 0;
        } else if (*(u8 *)((u8 *)BtlMember_GetActiveGauge(arg0) + 0x29) == 0) {
            S32(arg0, 0xB94) = 0;
        } else if (!(func_001FA3A8(func_001FA3A0(arg0)) & 0x100000)) {
            S32(arg0, 0xB94) = 4;
        }
        n = S32(arg0, 0x1528);
        S32(arg0, 0x1510) = S32(arg0, 0x1510) + 1;
        if (n > 0) {
            S32(arg0, 0x1528) = n - 1;
        }
    }
}
