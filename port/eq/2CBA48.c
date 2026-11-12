#include "common.h"

s32 func_002CB288(s32 arg0, s32 arg1);
void func_002CB2D8(s32 arg0);
void func_002CB340(s32 arg0);
void func_0032EC80(s32 arg0);
void func_0032ECA0(s32 arg0);

#define FW(o) (*(s32 *)(s0 + (o)))
#define FU(o) (*(u32 *)(s0 + (o)))

s32 func_002CBA48(s32 arg0) {
    u8 *s0 = (u8 *)arg0;
    u32 w38;
    u32 t1;
    u32 t2;
    u32 a3;
    u32 v1;
    u32 s2;
    u32 s3;
    u32 s4;
    u32 s5;
    u32 s6;
    u32 t0;
    u32 t0o;
    u32 a2u;
    u32 t3;
    s32 a2;
    s32 hi;
    s32 hi2;
    s32 s1;
    s32 t6;
    s32 t4;
    s32 a0c;
    s32 t5;
    s32 a0v;
    s32 a3m;
    s32 a1v;
    s32 v1_2;

    func_0032ECA0(FW(0x40));
    w38 = FU(0x38);
    t1 = FU(0x1C);
    v1 = ((w38 >> 16) & 3) + ((w38 >> 8) & 0xF);
    a3 = FU(0x00);
    s2 = t1 - (v1 * 0x10);
    t2 = FU(0x28);
    s5 = FU(0x24) + v1;
    s4 = FU(0x20);
    s3 = t2 | 0x100;
    s6 = w38 & 0x7F;

    if (s2 < a3) {
        a2 = FW(0x08);
        t0 = (u32)a2 << 11;
        s4 = FU(0x04) & 0x0FFFFFFF;
        s5 = (a3 - s2) >> 4;
        s2 += t0;
        a0v = ((t1 == a3) || (t1 == a3 + t0)) ? 0 : 3;
        hi = (a2 - FW(0x0C)) % a2;
        s3 = (t2 & 0x0FFFFFFF) | ((u32)a0v << 28) | 0x100;
        if (hi < 0 || hi >= FW(0x10)) {
            FW(0x0C) = a2 - 1;
            FW(0x10) = FW(0x10) + 1;
        }
    } else {
        s1 = func_002CB288(arg0, (s32)t1);
        t6 = func_002CB288(arg0, (s32)s2);
        if (s1 != t6) {
            t4 = FW(0x08);
            t0o = FU(0x00);
            a0c = FW(0x0C);
            t5 = FW(0x10);
            a2u = t0o + ((FU(0x1C) - t0o) % ((u32)t4 << 11));
            s5 = ((t0o + ((u32)s1 << 11)) - s2) >> 4;
            s4 = (((u32)s1 * 0x10) + FU(0x04)) & 0x0FFFFFFF;
            a1v = t6 + t4 - a0c;
            hi2 = a1v % t4;
            a3m = (a0c + t5) % t4;
            t0 = t0o + ((u32)a3m << 11);
            t3 = ((a2u ^ t0) == 0) ? 0 : 3;
            s3 = (FU(0x28) & 0x0FFFFFFF) | (t3 << 28) | 0x100;
            if (hi2 < 0 || hi2 >= t5) {
                FW(0x0C) = t6;
                FW(0x10) = t5 + 1;
            }
        }
    }

    v1_2 = FW(0x2C);
    if (v1_2 != 0 && FW(0x30) != 0) {
        *(s32 *)0x1000B010 = v1_2;
        *(s32 *)0x1000B020 = FW(0x30);
        func_002CB2D8(FW(0x34) | 0x100);
    }
    while (*(s32 *)0x10002010 < 0) {
    }
    *(s32 *)0x10002000 = (s32)s6;
    while (*(s32 *)0x10002010 < 0) {
    }
    *(u32 *)0x1000B410 = s2;
    *(u32 *)0x1000B430 = s4;
    *(u32 *)0x1000B420 = s5;
    if (FW(0x10) != 0) {
        func_002CB340((s32)s3);
    }
    *(s32 *)0x10002010 = FW(0x3C);
    FW(0x44) = 1;
    func_0032EC80(FW(0x40));
    return 1;
}
