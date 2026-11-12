#include "common.h"

extern u8 *D_003876A0;
extern u8 D_002C3630[] __attribute__((section(".data")));

void func_00202BC8(s32 arg0);
s32 func_00211270(void);
s32 func_0020A658(s32 arg0);
u8 *func_00211288(s32 arg0);
void func_002115D0(u8 *arg0);
u8 *BtlChar_GetPos(u8 *arg0);
void func_0020E9A0(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_00206F90(u8 *arg0);
void BtlFx_UpdateAfterHits(u8 *arg0);
void func_00212AD8(u8 *arg0);
void BtlChar_GetSnapDelta(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void BtlChar_GetMoveSince(u8 *arg0, u8 *arg1, s32 arg2);
u8 *BtlMember_GetActiveGauge(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023F430(u8 *arg0);
void func_003126C8(u8 *arg0, u8 *arg1);
s32 BtlCharApi_IsInTechnique(s32 arg0);
s32 func_00210DD8(u8 *arg0);
void func_001FBF58(u8 *arg0);

void func_001F7FE0(s32 arg0) {
    s64 flag;
    s32 s2;
    s32 r;
    u8 *s1;
    u8 *p1;
    u8 *p2;
    u8 *wp;
    u8 *g;
    u8 *src;
    u8 *dst;
    u8 *end;

    flag = *(s64 *)(D_003876A0 + 0x4D8);
    if ((flag & 0x100) != 0) {
        return;
    }
    if ((flag & 0x2000) != 0) {
        return;
    }
    /* arg0 is not written before the first jal: the function's own parameter, passed on (GUESS arity) */
    func_00202BC8(arg0);

    /* loop A: refresh every live entry */
    s2 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            func_002115D0(func_00211288(s2));
        }
        s2 += 1;
    }

    /* loop B: positions into func_0020E9A0 */
    s2 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            s1 = func_00211288(s2);
            p1 = BtlChar_GetPos(s1);
            p2 = BtlChar_GetPos(s1);
            func_0020E9A0(s1, p1, p2 + 0x10, 6);
        }
        s2 += 1;
    }

    /* loop C: per-entry update and state flags */
    s2 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            s1 = func_00211288(s2);
            func_00206F90(s1);
            BtlFx_UpdateAfterHits(s1);
            func_00212AD8(s1);
            p1 = BtlChar_GetPos(s1);
            BtlChar_GetSnapDelta(s1, p1 + 0x40, 0, 1);
            p2 = BtlChar_GetPos(s1);
            BtlChar_GetMoveSince(s1, p2 + 0x50, 0);

            g = BtlMember_GetActiveGauge(s1);
            if (*(s32 *)g < 0x4E20) {
                g = BtlMember_GetActiveGauge(s1);
                g[0x2B] = 1;
                if (func_00211310(s1, 6, 0x10) != 0) {
                    if (BtlMember_GetActiveGauge(s1)[0x28] == 0) {
                        g = BtlMember_GetActiveGauge(s1);
                        g[0x28] = 1;
                        *(u32 *)(*(u8 **)(s1 + 0x1530) + 0xAF0) |= 0x10000000;
                    }
                }
                r = func_0023F430(s1);
                if (((r & 0x80) == 0) && (*(s32 *)(s1 + 0xAD8) <= 0) && (*(s32 *)(s1 + 0xADC) <= 0)
                    && (func_00211310(s1, 0, 0x800) == 0)) {
                    g = BtlMember_GetActiveGauge(s1);
                    g[0x29] = 1;
                } else {
                    g = BtlMember_GetActiveGauge(s1);
                    g[0x29] = 0;
                }
            } else {
                g = BtlMember_GetActiveGauge(s1);
                g[0x29] = 0;
                g = BtlMember_GetActiveGauge(s1);
                g[0x2B] = 0;
            }

            func_002113C0(s1, 0xB, 0x3F, 0);

            /* 0x5F0..0x6CF copied to 0x6D0.. in 32-byte blocks */
            src = s1 + 0x5F0;
            dst = s1 + 0x6D0;
            end = s1 + 0x6D0;
            do {
                *(s64 *)(dst + 0x00) = *(s64 *)(src + 0x00);
                *(s64 *)(dst + 0x08) = *(s64 *)(src + 0x08);
                *(s64 *)(dst + 0x10) = *(s64 *)(src + 0x10);
                *(s64 *)(dst + 0x18) = *(s64 *)(src + 0x18);
                src += 0x20;
                dst += 0x20;
            } while (src != end);

            /* 0x378..0x437 copied to 0x440.., then the single doubleword at 0x438 */
            src = s1 + 0x378;
            dst = s1 + 0x440;
            end = s1 + 0x438;
            do {
                *(s64 *)(dst + 0x00) = *(s64 *)(src + 0x00);
                *(s64 *)(dst + 0x08) = *(s64 *)(src + 0x08);
                *(s64 *)(dst + 0x10) = *(s64 *)(src + 0x10);
                *(s64 *)(dst + 0x18) = *(s64 *)(src + 0x18);
                src += 0x20;
                dst += 0x20;
            } while (src != end);
            *(s64 *)dst = *(s64 *)src;
        }
        s2 += 1;
    }

    /* loop D: target position per entry, then the sprite/snap call */
    s2 = 0;
    while (s2 < func_00211270()) {
        if (func_0020A658(s2) == 0) {
            s1 = func_00211288(s2);
            if (func_00211310(s1, 6, 2) != 0) {
                if (func_00211310(s1, 9, 0x100000) == 0) {
                    if (BtlCharApi_IsInTechnique(*(s32 *)(s1 + 0x1534)) != 0) {
                        wp = func_00211288(func_00210DD8(s1));
                        BtlChar_GetSnapDelta(s1, wp + 0xBE0, 1, 3);
                    } else {
                        wp = func_00211288(func_00210DD8(s1));
                        BtlChar_GetSnapDelta(s1, wp + 0xBE0, 1, 4);
                    }
                } else {
                    wp = func_00211288(func_00210DD8(s1));
                    func_003126C8(wp + 0xBE0, D_002C3630);
                }
            } else {
                /* a1 = 9 is set in the delay slot of the beqz: passed on (GUESS arity of func_00210DD8) */
                wp = func_00211288(((s32 (*)(u8 *, s32))func_00210DD8)(s1, 9));
                func_003126C8(wp + 0xBE0, D_002C3630);
            }
            func_001FBF58(s1);
        }
        s2 += 1;
    }
}
