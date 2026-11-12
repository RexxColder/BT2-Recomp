#include "common.h"

s32 func_002E7AB8(s32 arg0);
void func_002E7E70(s32 arg0, s32 arg1, s32 arg2);
void func_002E7EF0(s32 arg0);
s32 func_002E9F00(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F1510(s32 arg0);
s32 func_002F1540(s32 arg0);
s32 func_002F17A8(s32 arg0);
void func_003061A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#define S32A(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define VFN(obj, off) (*(s32 *)(*(s32 *)(obj) + (off)))

void func_002F08D8(s32 arg0) {
    u8 *s2;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 v1;
    s32 a1;
    s32 n;
    s32 s0;
    s32 r;
    s32 sp[8];
    s16 *sp10;
    u8 *p;
    void (*fn)(s32);

    s2 = (u8 *)arg0;
    sp10 = (s16 *)(sp + 4);
    s4 = S32A(s2, 4);
    s1 = S32A(s2, 8);
    s3 = (s32)(s2 + 0x14);

    v1 = S32A(s2, 0x3C);
    if (v1 >= 0 && !(S32A(s2, 0x40) < v1)) {
        fn = (void (*)(s32))S32A(s2, 0x48);
        if (fn != 0) {
            fn(S32A(s2, 0x4C));
        }
    }
    v1 = (signed char)s2[3];

    if (v1 == 1) {
        if (((s32 (*)(s32, s32))VFN(s1, 0x24))(s1, 1) == 0) {
            s2[1] = 3;
            return;
        }
    }

L968:
    ((void (*)(s32, s32, s32, s32))VFN(s1, 0x18))(s1, 1, 0x7FFFFFFF, s3);
    if (func_002E7AB8(s4) != 0) {
        goto B18;
    }
    n = S32A(s2, 0x18);
    if (n < 4) {
        goto B18;
    }
    p = (u8 *)S32A(s2, 0x14);
    if ((((s32)p[1]) | ((s32)p[0] << 8)) != 0x8001) {
        goto B18;
    }

    s2[1] = 3;
    r = func_002E9F00(S32A(s2, 0x14), n, (s32)sp10);
    if (r != 0) {
        if (S32A(s2, 0x9C) == 0) {
            return;
        }
        s4 = s3;
        goto AE4;
    }
    if (S32A(s2, 0x18) < (s32)*sp10) {
        ((void (*)(s32, s32, s32))VFN(s1, 0x1C))(s1, 1, s3);
        return;
    }
    func_003061A8(s3, (s32)*sp10, s3, (s32)sp);
    ((void (*)(s32, s32, s32))VFN(s1, 0x20))(s1, 0, s3);
    ((void (*)(s32, s32, s32))VFN(s1, 0x1C))(s1, 1, (s32)sp);
    if (S32A(s2, 0x9C) == 0) {
        return;
    }
    s4 = s3;
    goto AE4;

AE4:
    for (;;) {
        ((void (*)(s32, s32, s32, s32))VFN(s1, 0x18))(s1, 1, 0x7FFFFFFF, s3);
        n = S32A(s2, 0x18);
        if (n == 0) {
            return;
        }
        a1 = 0;
        p = (u8 *)S32A(s2, 0x14);
        s0 = (a1 < n);
        if (s0 && (signed char)p[0] == 0) {
            a1 = a1 + 1;
            while (a1 < n && (signed char)p[a1] == 0) {
                a1 = a1 + 1;
            }
            s0 = (a1 < n);
        }
        func_003061A8(s4, a1, s4, (s32)sp);
        ((void (*)(s32, s32, s32))VFN(s1, 0x20))(s1, 0, s4);
        ((void (*)(s32, s32, s32))VFN(s1, 0x1C))(s1, 1, (s32)sp);
        if (s0 != 0) {
            return;
        }
    }

B18:
    r = func_002F1540((s32)s2);
    if (S32A(s2, 0x34) < r) {
        goto B80;
    }
    s0 = func_002E7AB8(s4);
    if (s0 != 1 || func_002F17A8((s32)s2) != s0) {
        s2[1] = 3;
        ((void (*)(s32, s32, s32))VFN(s1, 0x1C))(s1, 1, s3);
        return;
    }

B80:
    s0 = func_002F1510((s32)s2);
    {
        s32 a0c = S32A(s2, 0xC);
        s32 v0 = ((s32 (*)(s32, s32))VFN(a0c, 0x24))(a0c, 0);
        if ((v0 / 2) < s0) {
            ((void (*)(s32, s32, s32))VFN(s1, 0x1C))(s1, 1, s3);
            return;
        }
    }
    if (func_002E7AB8(s4) == 0xA) {
        ((void (*)(s32, s32, s32))VFN(s1, 0x1C))(s1, 1, s3);
    }
    if (func_002E7AB8(s4) == 0xF) {
        ((void (*)(s32, s32, s32))VFN(s1, 0x1C))(s1, 1, s3);
    }
    func_002E7E70(s4, S32A(s2, 0x14), S32A(s2, 0x18));
    func_002E7EF0(s4);
}
