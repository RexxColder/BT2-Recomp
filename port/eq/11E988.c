#include "common.h"

s32 func_00105A48(s64 arg0);
s8 func_0011F7D8(void *arg0);
void func_0011FE80(void *arg0);
void func_00120FF0(void *arg0);
void func_00121550(void *arg0);
void func_001215F8(void *arg0);
void func_00124768(void *arg0);
s32 func_00126040(void *arg0);
void *func_00202DC0(s32 arg0);
s32 func_0020A5C0(s32 arg0);
s32 func_0020A658(s32 arg0);
s32 func_0023FCE8(s32 arg0, s32 arg1);
s32 func_0023FD38(s32 arg0, s32 arg1);
s32 func_0023FD58(s32 arg0, s32 arg1);
s32 func_0023FD78(s32 arg0, s32 arg1);
s32 func_0023FD98(s32 arg0, s32 arg1);
extern u8 *D_003876A0;
extern u8 *D_003876FC;

void func_0011E988(void) {
    u8 *p;
    u8 *q;
    u8 *s0;
    s64 flags;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 old;
    s32 r;
    s32 c;
    s32 s1;
    u8 *v;

    p = D_003876A0;
    flags = *(s64 *)(p + 0x4D8);
    if (flags & 2) {
        return;
    }
    if (flags & 0x2000) {
        return;
    }
    if (flags & 0x100) {
        return;
    }
    if (func_00105A48(flags) < 2) {
        return;
    }
    q = D_003876FC;
    *(s32 *)(q + 8) = *(s32 *)(q + 8) + 1;
    if (*(s32 *)(q + 8) < 0x17) {
        return;
    }
    s2 = 0;
    if (*(s32 *)(q + 4) > 0) {
        s4 = 0;
        s3 = 0;
        do {
            old = s3;
            s3 += 0x1D0;
            if (*(u8 *)(p + old + 0x2A4) != 0) {
                if (func_0020A658(s2) == 0) {
                    s0 = *(u8 **)D_003876FC + s4;
                    r = func_00126040(s0);
                    s1 = r;
                    v = (u8 *)func_00202DC0(s1);
                    *(s32 *)(s0 + 8) = *(s32 *)(v + 0x30);
                    v = (u8 *)func_00202DC0(s1);
                    *(s32 *)(s0 + 0xC) = *(s32 *)(v + 0x34);
                    if (func_0020A5C0(s2) != 0) {
                        c = *(s32 *)(s0 + 0xC);
                        *(s32 *)(s0 + 0x11D8) = func_0023FCE8(s1, c);
                        c = *(s32 *)(s0 + 0xC);
                        *(s32 *)(s0 + 0x11DC) = func_0023FD38(s1, c);
                        c = *(s32 *)(s0 + 0xC);
                        *(s32 *)(s0 + 0x11E0) = func_0023FD58(s1, c);
                        c = *(s32 *)(s0 + 0xC);
                        *(s32 *)(s0 + 0x11E4) = func_0023FD78(s1, c);
                        c = *(s32 *)(s0 + 0xC);
                        *(s32 *)(s0 + 0x11E8) = func_0023FD98(s1, c);
                    }
                    func_00120FF0(s0);
                    func_00124768(s0);
                    func_0011FE80(s0);
                    *(s8 *)(s0 + 0x158) = func_0011F7D8(s0);
                    func_00121550(s0);
                    func_001215F8(s0);
                }
            }
            s2 += 1;
            s4 += 0x11F0;
        } while (s2 < *(s32 *)(D_003876FC + 4));
    }
}
