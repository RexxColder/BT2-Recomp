#include "common.h"

#define SPS32(o) (*(s32 *)(sp + (o)))

extern s32 D_00354F1C __attribute__((section(".data")));
extern u8 D_0037D020[] __attribute__((section(".data")));

void func_002F7950(void);
void func_002F7700(void);
void func_002F7A80(void);
s32 func_002F1ED0(s32 arg0);
void func_002F4238(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002F0388(s32 arg0);
s32 func_002F14E0(s32 arg0);
void func_002EA268(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002EA0C8(s32 arg0, s32 arg1);
void func_002F44A0(s32 arg0);
s32 func_002F14C8(s32 arg0);
s32 func_002F1570(s32 arg0);
s32 func_002F1510(s32 arg0);
void func_002F03E0(s32 arg0);
s32 func_002F1600(s32 arg0);
void func_002F2280(s32 arg0, s32 arg1);
void func_002F2220(s32 arg0, s32 arg1, s32 arg2);
void func_002F15E8(s32 arg0);
s32 func_002F15A0(s32 arg0);
void func_002F1480(s32 arg0, s32 arg1);
void func_002F14A0(s32 arg0, s32 arg1);
void func_002F1490(s32 arg0, s32 arg1);
void func_002F1470(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F1540(s32 arg0);
s32 func_002F14F8(s32 arg0);
void func_002EFF60(s32 arg0, s32 arg1);
void func_002EFF00(s32 arg0, s32 arg1);
void func_002EFEE8(s32 arg0, s32 arg1);
void func_002F0048(s32 arg0, s32 arg1);
void func_002F52A8(s32 arg0, s32 arg1);
void func_002F64F0(s32 arg0, s32 arg1, s32 arg2);
void func_002F64A0(s32 arg0, s32 arg1, s32 arg2);
void func_002F7A18(s32 arg0);
void func_003083C8(s32 arg0, s32 arg1);
s32 func_002F14B0(s32 arg0);
s32 func_002F1768(s32 arg0);
void func_002F0058(s32 arg0, s32 arg1);
void func_002EFE08(s32 arg0, s32 arg1);

void func_002F7D68(s32 arg0) {
    u8 sp[0x30];
    u8 *s0;
    s32 s1;
    s32 s2;
    s32 s4;
    s32 s5;
    s32 v;
    s32 q;
    s32 r;
    s32 dd;
    s32 tt;
    s32 rem1;
    s32 q2;
    s32 a1v;

    s0 = (u8 *)arg0;
    SPS32(0x20) = 0;
    SPS32(0x24) = 0;
    s1 = *(s32 *)(s0 + 4);
    *(s32 *)(s0 + 0xA8) = 0;

    if (*(u8 *)(s0 + 2) < 2) {
        if (*(s8 *)(s0 + 0xAC) == 1) {
            v = func_002F1ED0(*(s32 *)(s0 + 8));
            if (v == 2) {
                return;
            }
            if (*(s32 *)(s0 + 0x10) != 0) {
                s32 o = *(s32 *)(s0 + 0x10);
                ((void (*)(s32))(*(s32 *)(*(s32 *)o + 0x14)))(o);
            }
            func_002F4238(arg0, *(s32 *)(s0 + 0xB4), *(s32 *)(s0 + 0xB8), *(s32 *)(s0 + 0xBC), *(s32 *)(s0 + 0xC0));
            *(s8 *)(s0 + 0xAC) = 0;
        }
    }

    v = func_002F0388(s1);
    if (v != 2) {
        if (v == 4) {
            s0[1] = 6;
        }
        return;
    }

    s4 = func_002F14E0(s1);
    if (*(s8 *)(s0 + 3) < s4) {
        a1v = *(s8 *)(s0 + 3);
        func_002EA268(s4, a1v, (s32)sp, 0x10);
        func_002EA0C8((s32)D_0037D020, (s32)sp);
        func_002F44A0(arg0);
        return;
    }

    /* s2 = result of func_002F14C8 (the delay slot of the next jal reads it) */
    s2 = func_002F14C8(s1);
    s4 = func_002F1570(s1);
    if (s4 > 0) {
        dd = *(s32 *)(s0 + 0x38);
        q = s2 / dd;
        *(s32 *)(s0 + 0x48) = 3 * q;
    } else {
        dd = *(s32 *)(s0 + 0x38);
        q = s2 / dd;
        *(s32 *)(s0 + 0x48) = (3 * q) / 2;
    }

    r = func_002F1510(s1);
    dd = r << 1;
    a1v = *(s32 *)(s0 + 0x48) + dd;
    tt = (a1v / dd) * dd;
    *(s32 *)(s0 + 0x48) = tt;
    func_002F03E0(s1);

    if (s4 > 0) {
        if (*(s8 *)(s0 + 2) == 2) {
            *(s32 *)(s0 + 0x50) = 0;
        } else {
            r = func_002F1600(s1);
            rem1 = r % 0x800;
            q2 = (r + 0x7FF) / 0x800;
            *(s32 *)(s0 + 0x50) = 0x800 - rem1;
            *(s32 *)(s0 + 0x50) = (0x800 - rem1) % 0x800;
            *(s32 *)(s0 + 0x8C) = q2;
            func_002F2280(*(s32 *)(s0 + 8), q2);
            func_002F2220(*(s32 *)(s0 + 8), (s32)func_002F7950, (s32)s0);
        }
        func_002F15E8(s1);
        *(s32 *)(s0 + 0x90) = func_002F15A0(s1);
        func_002F1480(s1, *(s32 *)(s0 + 0x90));
        func_002F14A0(s1, 0);
        func_002F1490(s1, 0);
        func_002F1470(s1, (s32)func_002F7700, (s32)s0);
    } else {
        if (*(s32 *)(s0 + 8) != 0) {
            func_002F2280(*(s32 *)(s0 + 8), 0x7FFFFFFF);
        }
        r = func_002F1540(s1);
        func_002F1480(s1, r);
        func_002F14A0(s1, 0);
        func_002F1490(s1, 0);
        func_002F1470(s1, (s32)func_002F7A80, (s32)s0);
    }

    /* L8034 */
    {
        s32 r14c8 = func_002F14C8(s1);
        s32 r14e0 = func_002F14E0(s1);
        s32 r1540 = func_002F1540(s1);
        s32 r14f8 = func_002F14F8(s1);
        s2 = r14c8;
        s4 = r14e0;
        s5 = r1540;
        func_002EFF60(*(s32 *)(s0 + 0xC), r14f8);
        func_002EFF00(*(s32 *)(s0 + 0xC), s2);
        func_002EFEE8(*(s32 *)(s0 + 0xC), s4);
        func_002F0048(*(s32 *)(s0 + 0xC), s5);
    }
    func_002F52A8(arg0, *(s16 *)(s0 + 0x40));
    func_002F64F0(arg0, (s32)(sp + 0x20), (s32)(sp + 0x24));
    if (SPS32(0x20) != 0 || SPS32(0x24) != 0) {
        func_002F64A0(arg0, SPS32(0x20), SPS32(0x24));
    }
    func_002F7A18(arg0);
    if (*(s32 *)(s0 + 0x74) != 0) {
        func_003083C8(*(s32 *)(s0 + 0x74), s2);
    }
    if (func_002F14B0(s1) == 2) {
        s32 r1768 = func_002F1768(s1);
        func_002F0058(*(s32 *)(s0 + 0xC), r1768);
    }
    func_002EFE08(*(s32 *)(s0 + 0xC), 1);
    if (D_00354F1C != 0) {
        ((void (*)(s32, s32, s32, s32))D_00354F1C)(arg0, s2, s4, s5);
    }
    s0[1] = 2;
}
