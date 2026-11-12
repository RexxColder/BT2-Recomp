#include "common.h"

s32 BtlScene_IsStageChangeRequested(void);
void BtlScene_ClearStageChangeRequest(void);
s32 func_00105A98(void);
s32 func_00106198(void *arg0);
s32 func_001272E0(void);
s32 func_001272E8(s32 arg0);
s32 func_001279C0(u8 *arg0);
s32 func_0020AE40(s32 arg0);
s32 func_0020B2B8(s32 arg0);
s32 func_0020B3D0(s32 arg0);
s32 func_0020C688(s32 arg0);
void func_00274E48(void);
extern u8 *D_003876A0;
extern u8 *D_00387F2C;

void func_001268E8(void) {
    s32 s0;
    s32 s1;
    s32 s4;
    s32 s6;
    s32 a;
    s32 b;
    s32 v1;
    u8 *s2;
    u8 *s3;
    u8 *s5;

    s6 = 0;
    s5 = (u8 *)func_001272E0();
    if (s5 == 0) {
        return;
    }
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 3) == 0) {
        return;
    }
    if ((*(s32 *)(D_00387F2C + 0x808) & 1) != 0) {
        return;
    }
    if (*(s32 *)(D_003876A0 + 0xB8) == 6) {
        return;
    }
    if (*(s32 *)(D_003876A0 + 0xC0) != 0 && func_00106198(D_003876A0) < 10) {
        return;
    }
    s4 = 0;
    if (func_00105A98() == 0) {
        return;
    }
    s3 = s5;
    while (s4 < *(s32 *)(s5 + 0x6000)) {
        s2 = s3;
        s3 += 0x180;
        s1 = func_0020B3D0(*(s32 *)s2);
        if (func_001279C0(s2) == 0) {
            s4 += 1;
            continue;
        }
        s0 = func_001272E8(s4);
        if (func_0020AE40(s1) != 0) {
            s6 = 0;
            break;
        }
        if ((s0 & 4) != 0) {
            s6 = 1;
            *(s32 *)(s2 + 0x50) = *(s32 *)(s2 + 0x50) | 0xA;
            break;
        }
        if ((s0 & 3) != 1) {
            s4 += 1;
            continue;
        }
        a = func_0020C688(*(s32 *)s2);
        b = func_0020C688(s1);
        if (a == 0 || b == 0) {
            s4 += 1;
            continue;
        }
        if (func_0020B2B8(s1) == 0) {
            s4 += 1;
            continue;
        }
        if (func_0020AE40(s1) != 0) {
            s4 += 1;
            continue;
        }
        if ((*(s32 *)(*(u8 **)(s2 + 0x60) + 4) & 0x4000) == 0) {
            s6 = 1;
            *(s32 *)(s2 + 0x50) = *(s32 *)(s2 + 0x50) | 0xA;
            break;
        }
        v1 = *(s32 *)(s2 + 0x50);
        if ((v1 & 0x10) != 0) {
            s6 = 1;
            *(s32 *)(s2 + 0x50) = v1 | 0xA;
        }
        break;
    }
    if (BtlScene_IsStageChangeRequested() != 0) {
        s6 = 1;
        BtlScene_ClearStageChangeRequest();
    }
    if (s6 != 0) {
        func_00274E48();
    }
}
