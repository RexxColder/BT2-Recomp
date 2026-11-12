#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387930;
s32 func_00105A48(void);
void func_001F5A98(void);
s32 func_00211270(void);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_001F6980(s32 arg0);
void BtlScene_Reset(s32 arg0);
void func_001F6D40(void);
s32 func_0020A658(s32 arg0);
void func_00211028(s32 arg0);
void func_00207630(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002115D0(s32 arg0);
void func_0020E998(s32 arg0);
void func_001F9D68(s32 arg0, f32 farg0);
void func_001FA360(s32 arg0, f32 farg0);
void func_001FA380(s32 arg0, f32 farg0);
u8 *BtlChar_GetPos(s32 arg0);
s32 func_0023FC78(s32 arg0);
s32 func_0023FC88(s32 arg0);
s32 func_00203C58(s32 arg0, s64 arg1);
u8 *func_00202DC0(s32 arg0);
void func_0020E9A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020E0E8(void);
void func_0020DBC0(s32 arg0);

/* 0x001F71B0: battle start/reset of every character slot. */
void func_001F71B0(void) {
    s32 s0, s1, s2, i, r;
    u8 *v1;
    u32 v0;
    u8 *p, *q;

    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x2000) {
        return;
    }
    v1 = D_00387930;
    v0 = *(u32 *)(v1 + 8) & ~0x18u;
    *(u32 *)(v1 + 8) = v0;
    s0 = 0;
    r = func_00105A48();
    if (r == 3 || func_00105A48() == 2) {
        if ((*(u64 *)(D_003876A0 + 0x4D8) & 0x3800) == 0) {
            *(s32 *)(D_00387930 + 0x20) = *(s32 *)(D_00387930 + 0x20) + 1;
            *(u32 *)(D_00387930 + 0x20) = *(u32 *)(D_00387930 + 0x20) & 0x3FFFFFFF;
        }
        v1 = D_00387930;
        v0 = *(u32 *)(v1 + 0x24);
        if ((s32)v0 > 0) {
            *(s32 *)(v1 + 0x24) = (s32)v0 - 1;
            v1 = D_00387930;
        }
        v0 = *(u32 *)(v1 + 8);
        if ((v0 & 2) == 0) {
            func_001F5A98();
            v1 = D_00387930;
            v0 = *(u32 *)(v1 + 8);
        }
        *(u32 *)(v1 + 8) = v0 | 2;
        s0 = 0;
    }

    s2 = 0;
    while (1) {
        s32 n = func_00211270();
        i = s2;
        s2++;
        if (!(i < n)) {
            break;
        }
        if (func_00211310(func_00211288(i), 0xB, 0x80) != 0) {
            s0 = 1;
            break;
        }
    }
    if (s0 != 0) {
        s2 = 0;
        while (1) {
            s32 n = func_00211270();
            i = s2;
            s2++;
            if (!(i < n)) {
                break;
            }
            func_001F6980(func_00211288(i));
        }
        BtlScene_Reset(4);
    }

    func_001F6D40();
    s2 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            func_00211028(func_00211288(s2));
        }
        s2++;
    }

    s2 = 0;
    s0 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            s1 = func_00211288(s2);
            p = (u8 *)s1 + 0x510;
            q = (u8 *)s1 + 0x5F0;
            do {
                u64 a1 = *(u64 *)(p + 0), a2 = *(u64 *)(p + 8), a3 = *(u64 *)(p + 0x10), t0 = *(u64 *)(p + 0x18);
                *(u64 *)(q + 0) = a1;
                *(u64 *)(q + 8) = a2;
                *(u64 *)(q + 0x10) = a3;
                *(u64 *)(q + 0x18) = t0;
                p += 0x20;
                q += 0x20;
            } while (p != (u8 *)s1 + 0x5F0);
            p = (u8 *)s1 + 0x2B0;
            q = (u8 *)s1 + 0x378;
            do {
                u64 a1 = *(u64 *)(p + 0), a2 = *(u64 *)(p + 8), a3 = *(u64 *)(p + 0x10), t0 = *(u64 *)(p + 0x18);
                *(u64 *)(q + 0) = a1;
                *(u64 *)(q + 8) = a2;
                *(u64 *)(q + 0x10) = a3;
                *(u64 *)(q + 0x18) = t0;
                p += 0x20;
                q += 0x20;
            } while (p != (u8 *)s1 + 0x370);
            *(u64 *)q = *(u64 *)p;
            func_00207630(s1, *(s32 *)((u8 *)s1 + 0x153C));
            func_002113C0(s1, 2, 0x1C02, 0);
            func_002113C0(s1, 3, 0x3FEBFF, 0);
            func_002113C0(s1, 1, 0x7F234C0, 0);
            func_002113C0(s1, 5, 0xD61, 0);
            func_002113C0(s1, 6, 0x1E, 0);
            func_002113C0(s1, 7, 0x80320, 0);
            func_002113C0(s1, 8, 6, 0);
            func_002113C0(s1, 9, 0x3DEF5E64, 0);
            func_002113C0(s1, 0xB, 0x80, 0);
            func_002113C0(s1, 0xD, 0x3F, 0);
            func_002113C0(s1, 0xE, 0x3FEF, 0);
            func_002113C0(s1, 0xF, 0x7FFC7F, 0);
            __builtin_memset((u8 *)s1 + 0x2F4, 0, 0x44);
            func_002113C0(s1, 0, 0x100000, 0);
            func_002113C0(s1, 0, 0x200000, 0);
            func_002113C0(s1, 0, 0x400000, 0);
            r = func_00105A48();
            if (r == 2) {
                func_002113C0(s1, 0, 0x200000, 1);
            } else if (r < 3) {
                if (r >= 0) {
                    func_002113C0(s1, 0, 0x100000, 1);
                }
            } else if (r == 3) {
                func_002113C0(s1, 0, 0x400000, 1);
            }
            func_002115D0(s1);
            func_0020E998(s1);
            *(u64 *)((u8 *)s1 + 0x338) = 0;
            *(s32 *)((u8 *)s1 + 0x370) = 0;
            *(s32 *)((u8 *)s1 + 0x36C) = -1;
            *(s32 *)((u8 *)s1 + 0x368) = -1;
            __builtin_memset((u8 *)s1 + 0x340, 0, 0x10);
            *(s32 *)((u8 *)s1 + 0x360) = 0;
            *(s32 *)((u8 *)s1 + 0x364) = 0;
            func_001F9D68(s1, 0.0f);
            func_001FA360(s1, 2.0f);
            *(f32 *)(BtlChar_GetPos(s1) + 0xD4) = 0.0f;
            *(s32 *)((u8 *)s1 + 0xC04) = *(s32 *)((u8 *)s1 + 0xC00);
            func_001FA380(s1, 1.0f);
            *(u8 *)((u8 *)s1 + 0xBD4) = 0;
            if (func_00211310(s1, 0, 0x800) != 0) {
                *(s32 *)((u8 *)s1 + 0x9A4) = func_0023FC78(s1);
                *(s32 *)((u8 *)s1 + 0x9AC) = func_0023FC88(s1);
            } else {
                *(s32 *)((u8 *)s1 + 0x9AC) = 1;
                *(s32 *)((u8 *)s1 + 0x9A4) = 1;
            }
            if (func_00203C58(s1, 2) != 0) {
                *(s32 *)((u8 *)s1 + 0x9A4) = *(s32 *)((u8 *)s1 + 0x9A4) + 2;
            } else if (func_00203C58(s1, 1) != 0) {
                *(s32 *)((u8 *)s1 + 0x9A4) = *(s32 *)((u8 *)s1 + 0x9A4) + 1;
            }
            func_002113C0(s1, 1, 0x100, 1);
            if (func_00203C58(s1, 0x800) != 0) {
                *(u32 *)(D_00387930 + 8) |= 8;
            }
            if (func_00203C58(s1, 0x1000) != 0) {
                *(u32 *)(D_00387930 + 8) |= 0x10;
            }
            if (*(s32 *)(D_003876A0 + 0xB8) == 5) {
                u8 *r2 = func_00202DC0(s1);
                *(s32 *)(r2 + 0x30) = *(s32 *)(D_003876A0 + s0 + 0xF0);
            }
        }
        s0 += 0x1D0;
        s2++;
    }

    s2 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            s1 = func_00211288(s2);
            s0 = (s32)BtlChar_GetPos(s1);
            func_0020E9A0(s1, s0, (s32)BtlChar_GetPos(s1) + 0x10, 0);
        }
        s2++;
    }
    func_0020E0E8();
    s2 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            func_0020DBC0(func_00211288(s2));
        }
        s2++;
    }
}
