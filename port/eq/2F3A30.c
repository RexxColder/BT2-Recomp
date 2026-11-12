#include "common.h"

void func_002EA050(s32 arg0);
void func_002E93C0();
void func_002E93D8();
s32 func_002EFD88(s32 arg0, s32 arg1);
s32 func_002F01B8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F1B30(s32 arg0, s32 arg1);
void func_002F3E90(s32 arg0);
void func_002F55C8(s32 arg0, s32 arg1);
void func_002F6878(s32 arg0, s32 arg1);
s32 func_002FFA00(s32 arg0);
void func_002FFBC0(s32 arg0, s32 arg1);
s32 func_00304760();
void *memset(void *arg0, s32 arg1, s32 arg2);
extern u8 D_0034AEE0[] __attribute__((section(".data")));
extern u8 D_0037C710[] __attribute__((section(".data")));
extern u8 D_0037C738[] __attribute__((section(".data")));
extern s32 D_00354ED0 __attribute__((section(".data")));

s32 func_002F3A30(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 s2v;
    s32 a0;
    s32 i;
    s32 v0;
    s32 v1;
    s32 a1;
    s32 a3;
    s32 vb;
    s32 ti;
    u8 *s1;
    u8 *s2;
    f32 fr;
    f32 f0;

    s0 = (arg1 + 0x3F) & ~0x3F;
    s2v = arg2 - (s0 - arg1);
    if (arg0 < 0 || arg1 == 0 || arg2 < 0) {
        goto L_callA;
    }

    a0 = 0;
    while (a0 < 0x10 && D_0034AEE0[a0 * 0xC8] != 0) {
        a0 += 1;
    }
    if (a0 == 0x10) {
        goto L_callB;
    }

    s1 = D_0034AEE0 + a0 * 0xC8;
    memset(s1, 0, 0xC8);
    s1[3] = (u8)arg0;
    v0 = arg0 * 0x40C0;
    *(s32 *)(s1 + 0x2C) = s0;
    a1 = s2v - v0;
    v0 = s0 + v0;
    v1 = a1 - 0x124;
    *(s32 *)(s1 + 0x20) = v0;
    *(s32 *)(s1 + 0x30) = 0x2000;
    *(s32 *)(s1 + 0x34) = 0x2060;
    vb = ((v1 < 0) ? (a1 + 0x6DB) : v1) >> 11;
    v1 = vb << 11;
    *(s32 *)(s1 + 0x24) = v1;
    a3 = v1 + 0x24;
    *(s32 *)(s1 + 0xB0) = v0 + a3;
    *(s32 *)(s1 + 0x28) = 0x24;
    *(s32 *)(s1 + 0x14) = 0;
    v0 = func_00304760(v0, v1, 0x24, a3);
    *(s32 *)(s1 + 0x10) = v0;
    if (v0 == 0) {
        goto L_fail;
    }
    v0 = func_002F1B30(v0, 0);
    *(s32 *)(s1 + 0x08) = v0;
    if (v0 == 0) {
        goto L_fail;
    }

    if (arg0 > 0) {
        i = 0;
        s2 = s1 + 0x18;
        do {
            a0 = *(s32 *)(s1 + 0x34) * i;
            i += 1;
            v0 = *(s32 *)(s1 + 0x2C);
            a1 = *(s32 *)(s1 + 0x30) * 2;
            a3 = (*(s32 *)(s1 + 0x34) - *(s32 *)(s1 + 0x30)) * 2;
            v0 = func_00304760(v0 + a0 * 2, a1, a3);
            *(s32 *)s2 = v0;
            s2 += 4;
            if (v0 == 0) {
                goto L_fail;
            }
        } while (i < arg0);
    }

    /* L3BF0 */
    s2 = s1 + 0x18;
    v0 = func_002F01B8(*(s32 *)(s1 + 0x10), arg0, (s32)s2);
    *(s32 *)(s1 + 0x04) = v0;
    if (v0 == 0) {
        goto L_fail;
    }
    v0 = func_002EFD88((s32)s2, arg0);
    *(s32 *)(s1 + 0x0C) = v0;
    if (v0 == 0) {
        goto L_fail;
    }
    v0 = func_002FFA00(*(s32 *)(s1 + 0x10));
    *(s32 *)(s1 + 0x94) = v0;
    if (v0 == 0) {
        goto L_fail;
    }
    func_002FFBC0(v0, *(s32 *)(s1 + 0x08));
    func_002E93C0();

    v0 = *(s32 *)(s1 + 0x24);
    if (v0 < 0) {
        v0 = v0 + 0x7FF;
    }
    v0 = v0 >> 11;
    *(s16 *)(s1 + 0x40) = 0;
    *(s16 *)(s1 + 0x3C) = (s16)v0;
    *(s32 *)(s1 + 0x38) = D_00354ED0;
    f0 = (f32)(s16)v0 * 0.84999996f;
    ti = (s32)f0;
    fr = f0 - (f32)ti;
    if (fr > 0.5f || (fr == 0.5f && (ti & 1))) {
        ti += 1;
    } else if (fr < -0.5f || (fr == -0.5f && (ti & 1))) {
        ti -= 1;
    }
    *(s16 *)(s1 + 0x3E) = (s16)ti;
    if (arg0 > 0) {
        for (i = 0; i < arg0; i++) {
            *(s16 *)(s1 + 0x42 + 2 * i) = -0x80;
        }
    }

    /* L3CD4 */
    *(s16 *)(s1 + 0x46) = 0;
    s1[0x6C] = 1;
    *(s32 *)(s1 + 0x54) = 0;
    *(s32 *)(s1 + 0x58) = 0;
    *(s32 *)(s1 + 0x5C) = 0;
    *(s16 *)(s1 + 0x60) = 0;
    *(s32 *)(s1 + 0x64) = 0;
    *(s16 *)(s1 + 0x68) = 0;
    *(s16 *)(s1 + 0x6A) = 0;
    s1[0x6D] = 1;
    s1[0x72] = 0;
    *(s32 *)(s1 + 0x88) = 0;
    func_002F6878((s32)s1, 0);
    func_002F55C8((s32)s1, 1);
    s1[0] = 1;
    func_002E93D8();
    return (s32)s1;

L_fail:
    func_002F3E90((s32)s1);
    return 0;

L_callA:
    func_002EA050((s32)D_0037C710);
    return 0;

L_callB:
    func_002EA050((s32)D_0037C738);
    return 0;
}
