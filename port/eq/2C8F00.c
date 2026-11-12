#include "common.h"

s32 func_002C71F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C7148(s32 arg0, s32 arg1);
s32 func_002C91B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C94B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C9540(s32 arg0);
void func_002C9658(s32 arg0, s32 arg1);
void func_002C97E8(s32 arg0, s32 arg1, s32 arg2);
void func_002C9A08(s32 arg0, s32 arg1);
void func_002CAC08(s32 arg0, s32 arg1);
void func_002CAD40(s32 arg0);
void func_002CAD50(s32 arg0);
void func_002CAD68(s32 arg0);
s32 func_002CC630(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002CE418(s32 arg0, s32 arg1, s32 arg2);
s64 func_002D2750(void);
void func_002D2858(s32 arg0, s64 arg1);
void func_002E0510(s32 arg0, s32 arg1, s32 arg2);
s32 func_00305390(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C8F00(u8 *arg0, s32 arg1) {
    u8 sp[0x50];
    u8 *s3;
    u8 *fp;
    u8 *s6;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s5;
    s32 c;
    s32 d;
    s32 sp30;
    s32 temp_a1;

    s6 = arg0 + 0x9F8;
    s3 = (u8 *)*(s32 *)(arg0 + 0x1FC0);
    fp = s3 + 0x8C;
    *(s32 *)(sp + 0x3C) = (s32)(arg0 + 0x950);
    *(s32 *)(sp + 0x40) = *(s32 *)s3;
    if (func_002C91B0((s32)arg0, (s32)fp, (s32)sp, (s32)(sp + 0x30)) != 0) {
        return 0;
    }
    sp30 = *(s32 *)(sp + 0x30);

    func_002C94B8((s32)arg0, (s32)s3, (s32)(sp + 0x34), (s32)(sp + 0x38));
    sp30 = *(s32 *)(sp + 0x30);
    func_002C9A08(*(s32 *)(sp30 + 0x54), (s32)(s3 + 0x108C));
    func_002C9540((s32)arg0);
    s2 = func_002D2750();
    s0 = func_00305390(arg1, 0, 1);
    s1 = func_002CC630(*(s32 *)(sp + 0x40), arg1, (s32)sp, (s32)arg0);
    c = func_00305390(arg1, 0, 1);
    s5 = c - s0;
    d = func_002D2750();
    func_002D2858((s32)(arg0 + (*(s32 *)(fp + 0x18) << 5) + 0x36C0), d - s2);
    *(s32 *)(s6 + 0xC) = *(s32 *)(s6 + 0xC) + *(s32 *)(sp + 0x28);
    *(s32 *)(s6 + 0x10) = *(s32 *)(s6 + 0x10) + *(s32 *)(sp + 0x2C);
    s0 = func_002C71F0((s32)arg0, s1, s5, (s32)0xFF000F06);
    func_002C7148((s32)arg0, s5);
    if (s0 != 0) {
        func_002CAD40(*(s32 *)(sp + 0x30));
        return s0;
    }

    if (s5 <= 0) {
        if (*(s32 *)(s3 + 0x168) == 0) {
            func_002CAD40(*(s32 *)(sp + 0x30));
        }
        return 0;
    }

    func_002CAC08((s32)arg0, 0);
    func_002C9658((s32)arg0, *(s32 *)(sp + 0x30));
    func_002C97E8((s32)arg0, *(s32 *)(sp + 0x30), arg1);
    sp30 = *(s32 *)(sp + 0x30);
    *(s32 *)(sp30 + 0x48) = *(s32 *)(s3 + 0x88);
    *(s32 *)(sp30 + 0x40) = *(s32 *)(sp + 0x28) + *(s32 *)(sp + 0x34) + *(s32 *)(s3 + 0x174);
    *(s32 *)(sp30 + 0x44) = *(s32 *)(sp + 0x2C) + *(s32 *)(sp + 0x38);
    temp_a1 = *(s32 *)(fp + 0x38);
    if (temp_a1 != 3 && *(s32 *)(s3 + 0x168) == 0) {
        *(s32 *)(s3 + 0x168) = sp30;
    } else {
        *(s32 *)(s3 + 0x168) = 0;
    }
    *(s32 *)(s3 + 0x16C) = 0;
    *(s32 *)(s3 + 0x170) = 0;
    if (*(s32 *)(s3 + 0x168) != 0) {
        func_002CE418((s32)arg0, 1, *(s32 *)(fp + 0x18));
        return 0;
    }

    if (*(s32 *)(arg0 + 0x38) == 3 && (u32)(*(s32 *)(fp + 0x18) - 1) < 2) {
        func_002CAD68(sp30);
    } else {
        func_002CAD50(sp30);
    }
    *(s32 *)(s3 + 0x84) = 0;
    func_002E0510(*(s32 *)(sp + 0x40), (s32)(arg0 + 0x950 + 8), (s32)(arg0 + 0x950 + 0xC));
    func_002CE418((s32)arg0, 1, *(s32 *)(fp + 0x18));
    return 0;
}
