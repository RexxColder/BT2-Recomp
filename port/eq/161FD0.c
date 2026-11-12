#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void BtlTask_SetDead(u8 *arg0);
s32 EftShot_GetAttrKind(s32 arg0, u64 arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(s32 arg0, u8 *arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00161858(u8 *arg0);
void func_00161A00(s32 arg0, u8 *arg1, s32 arg2);
void func_00161B10(u8 *arg0);
void func_00161B78(u8 *arg0);
void func_00161C80(u8 *arg0);
void func_00161E50(u8 *arg0);
u8 *func_001F3758(u8 *arg0);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
s32 func_0020A758(s32 arg0);

void func_00161FD0(u8 *arg0) {
    u8 *p;
    u8 *s1;
    u8 *s2;
    u8 *s0;
    s32 s4;
    s32 hit;
    s32 v1;

    p = func_001F3758(arg0);
    s1 = *(u8 **)(arg0 + 0x38);
    s4 = *(s32 *)(p + 0x38);
    s2 = *(u8 **)(s1 + 0x70);
    if (BtlScene_IsCharStopped(*(s32 *)s2) == 0) {
        func_00161E50(arg0);
        if (*(s32 *)s1 & 0x20) {
            *(s32 *)(s1 + 8) = *(s32 *)(s1 + 8) + 1;
        }
        func_00152530(s2, s1 + 0x820);
        if (EftShot_TestBits(*(s32 *)s2, 0x10) != 0) {
            *(s32 *)s1 = *(s32 *)s1 | 0x40;
            *(s32 *)(s1 + 4) = *(s32 *)(s1 + 4) | 9;
        }
        if (EftShot_TestBits(*(s32 *)s2, 0x20) != 0) {
            *(s32 *)s1 = *(s32 *)s1 & ~0x40;
            *(s32 *)(s1 + 4) = *(s32 *)(s1 + 4) & ~9;
        }
        if (*(s32 *)s1 & 0x40) {
            func_00208DE8(*(s32 *)s2, s1 + 0x40, EftShot_GetAttrKind(*(s32 *)s2, 0x10));
        }
        func_00161858(arg0);
        s0 = s1 + 0x74;
        if (EftShot_TestBits(*(s32 *)s2, 0x80) != 0) {
            v1 = *(s32 *)s1;
            if (!(v1 & 8)) {
                v1 = v1 | 4;
            }
            *(s32 *)s1 = v1 | 1;
            s0 = s1 + 0x74;
        }
        func_00151FB0(s0);
        func_00161A00(*(s32 *)s2, arg0, s4);
        hit = func_00152200(s4, s0) != 0;
        if (func_0020A758(*(s32 *)s2) != 0) {
            func_00161B10(arg0);
            func_00161B78(arg0);
            func_00161C80(arg0);
        }
        v1 = *(s32 *)s1;
        if (hit == 0 && (v1 & 2)) {
            BtlTask_SetDead(arg0);
            return;
        }
        if (v1 & 1) {
            *(s32 *)s1 = v1 | 2;
        }
    }
}
