#include "common.h"

extern u8 *D_003876A0;
extern s32 D_00387A40;
extern f32 D_00383EB4;
extern f32 D_00383EB8;
extern f32 D_00383EBC;
extern f32 D_00383EC0;
extern f32 D_00383EC4;
extern f32 D_00383EC8;

s32 func_0010B080(s32 arg0, s32 arg1);
void memset(void *arg0, s32 arg1, s32 arg2);
s32 func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00113830(s32 arg0);
void func_001081B0(s32 arg0);
void func_00109A20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);
void func_00113CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00112B60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0029D548(void);
void func_00113598(s32 arg0);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
void func_0029D580(s32 arg0);
void Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
s32 Ramp_Step(s32 arg0);

s32 func_00111690(s32 arg0, s32 arg1) {
    u8 *s0;
    s32 sa[32];
    s32 s1;
    s32 s3;
    s32 sx;
    s32 vv;
    s32 a2;
    s32 ri;
    s32 k;
    f32 f20;
    f32 f0;
    f32 dd;
    u8 *pv;

    s0 = (u8 *)arg1;
    s1 = func_0010B080(arg0, arg1);
    memset((void *)arg0, 0, 0xC0);
    func_00114508(arg0, 2, 0, 2);

    if (*(s32 *)s0 < 4) {
        /* block B: state word below 4 */
        k = (s16)(*(u16 *)s0 + 3);
        func_00113CB8(arg0, 0, *(s32 *)(s1 + 4), k);
        *(s32 *)arg0 |= 0x100;
        func_00112B60(*(s32 *)(s1 + 4), k, (s32)&sa[16], 0);
        f0 = (f32)sa[16];
        f20 = -f0;
        vv = *(s32 *)(s0 + 4);
        if (vv == 0) {
            Ramp_Start((s32)(s0 + 0x10), D_00383EC0, 1.0f, 0.0f);
            *(s32 *)(s0 + 4) += 1;
            goto b1984;
        }
        if (vv == 1) {
            goto b1984;
        }
        if (vv == 2) {
            goto b2;
        }
        if (vv == 3) {
            goto b3;
        }
        goto btail;

    b1984:
        if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
            if (Ramp_Step((s32)(s0 + 0x10)) == 0) {
                *(f32 *)(s0 + 0x28) = f20 * *(f32 *)(s0 + 0x20);
            } else {
                Ramp_Start((s32)(s0 + 0x10), D_00383EC4, 0.0f, 1.0f);
                *(f32 *)(s0 + 0x28) = 0.0f;
                *(s32 *)(s0 + 4) += 1;
            }
        }
        goto btail;

    b2:
        if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
            if (Ramp_Step((s32)(s0 + 0x10)) != 0) {
                Ramp_Start((s32)(s0 + 0x10), D_00383EC8, 0.0f, 1.0f);
                *(s32 *)(s0 + 4) += 1;
            }
        }
        goto btail;

    b3:
        if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
            if (Ramp_Step((s32)(s0 + 0x10)) != 0) {
                return 1;
            }
            *(f32 *)(s0 + 0x28) = f20 * *(f32 *)(s0 + 0x20);
        }
        goto btail;

    btail:
        func_0029D548();
        func_00113598((s32)(s0 + 0x28));
        BtlRec_CallFlagged(arg0, 1, 2);
        func_0029D580(1);
        return 0;
    }

    /* block A: state word 4 or more */
    *(s32 *)(s0 + 0x28) = 0;
    func_00113830((s32)sa);
    s3 = 8;
    a2 = *(s32 *)(s0 + 0xC);
    if (a2 != 0) {
        s3 = 0x1F8;
    }
    vv = *(s32 *)(s0 + 8);
    f0 = *(f32 *)&sa[13] + 9.0f;
    ri = (s32)f0;
    dd = f0 - (f32)ri;
    if (dd >= 0.5f) {
        if (dd > 0.5f || (ri & 1)) {
            ri += 1;
        }
    } else if (dd <= -0.5f) {
        if (dd < -0.5f || (ri & 1)) {
            ri -= 1;
        }
    }
    sx = ri;
    pv = (u8 *)((u32)(*(s32 *)D_00387A40) + (u32)vv * 0x18580u);
    func_001081B0(*(s32 *)(pv + 0x5C));

    vv = *(s32 *)(s0 + 4);
    if (vv == 1) {
        goto a1c;
    }
    if (vv < 2) {
        if (vv == 0) {
            goto a0c;
        }
        return 0;
    }
    if (vv == 2) {
        goto a2c;
    }
    if (vv == 3) {
        goto a3c;
    }
    return 0;

a0c:
    Ramp_Start((s32)(s0 + 0x10), D_00383EB4, 0.0f, 1.0f);
    *(s32 *)(s0 + 4) += 1;

a1c:
    if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        if (Ramp_Step((s32)(s0 + 0x10)) != 0) {
            Ramp_Start((s32)(s0 + 0x10), D_00383EB8, 0.0f, 1.0f);
            func_00109A20(s3, sx, *(s32 *)s0 - 4, *(s32 *)(s0 + 0xC), 1.0f);
            *(s32 *)(s0 + 4) += 1;
            return 0;
        }
    }
    func_00109A20(s3, sx, *(s32 *)s0 - 4, *(s32 *)(s0 + 0xC), *(f32 *)(s0 + 0x20));
    return 0;

a2c:
    if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        if (Ramp_Step((s32)(s0 + 0x10)) != 0) {
            Ramp_Start((s32)(s0 + 0x10), D_00383EBC, 1.0f, 0.0f);
            *(s32 *)(s0 + 4) += 1;
        }
    }
    func_00109A20(s3, sx, *(s32 *)s0 - 4, *(s32 *)(s0 + 0xC), 1.0f);
    return 0;

a3c:
    if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        if (Ramp_Step((s32)(s0 + 0x10)) != 0) {
            return 1;
        }
    }
    func_00109A20(s3, sx, *(s32 *)s0 - 4, *(s32 *)(s0 + 0xC), *(f32 *)(s0 + 0x20));
    return 0;
}
