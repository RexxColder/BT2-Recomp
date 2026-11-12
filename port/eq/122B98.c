#include "common.h"

extern f32 D_00384114;

s32 func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_003126C8(void *arg0, void *arg1, void *arg2);
void func_00121050(void *arg0, void *arg1, f32 farg0, f32 farg1);
void func_001226F0(void *arg0, s32 arg1);
void func_00122708(void *arg0, s32 arg1);
s32 func_00126040(void *arg0);
s32 func_00217488(s32 arg0);
s32 func_001216B8(void *arg0);
f32 func_00121648(void *arg0, void *arg1);
s32 EftObj_UpdateMtx(void *arg0);

void func_00122B98(void *arg0) {
    u8 *s0 = arg0;
    s32 *s1 = (s32 *)(s0 + 0xFE0);
    u8 sp[0x20];
    u8 *A;
    u8 *a1;
    u8 *a2;
    s32 idx;
    s32 v;
    s32 mode;
    s32 flags;
    s32 r1;
    s32 r2;
    f32 f0;

    func_00208DE8(*(s32 *)s0, sp + 0x10, 3);
    A = s0 + 0xBE0;
    idx = s1[2];
    a2 = A + idx;
    v = (signed char)a2[0x3E0];
    a1 = A + ((idx - v) << 4) + 0x20;
    func_003126C8(sp, a1, a2);
    func_00121050(s0, sp, 10.0f, D_00384114);

    mode = s1[12];
    if (mode == 1) goto c78;
    if (mode >= 2) {
        if (mode == 2) goto cf0;
        if (mode == 3) goto dd0;
        return;
    }
    if (mode != 0) return;
    v = s1[13] + 1;
    s1[13] = v;
    if (v >= 0x1F) {
        func_001226F0(s0, 0);
    }
    s1[12] = 1;
    s1[13] = 0;
    return;

c78:
    func_00122708(s0, 0x4000);
    v = s1[13] + 1;
    s1[13] = v;
    if (v >= 0x1F) {
        func_001226F0(s0, 0);
    }
    r1 = func_00126040(s0);
    r2 = func_00217488(r1);
    if (r2 != 0xD) {
        r1 = func_00126040(s0);
        r2 = func_00217488(r1);
        if (r2 != 0xE) return;
    }
    s1[13] = 0;
    s1[12] = 2;
    return;

cf0:
    r1 = func_001216B8(s0);
    if (r1 != 0) {
        f0 = func_00121648(sp + 0x10, s0 + 0x1040);
        if (50.0f < f0) {
            func_00122708(s0, 0x4000);
        }
        if (s1[14] >= 0x10) {
            func_00122708(s0, 0x4000);
        }
    }
    r1 = EftObj_UpdateMtx(s0);
    if (r1 == 0x20) {
        s1[12] = 3;
        return;
    }
    flags = s1[10];
    if (flags & 1) {
        func_001226F0(s0, 1);
        return;
    }
    if (flags & 2) {
        func_001226F0(s0, 2);
        return;
    }
    goto chain;

dd0:
    flags = s1[10];
    if (flags & 1) {
        func_001226F0(s0, 1);
        return;
    }
    if (flags & 2) {
        func_001226F0(s0, 2);
        return;
    }
    r1 = EftObj_UpdateMtx(s0);
    if (r1 == 0x20) goto chain;
    goto tail4;

chain:
    r1 = func_00126040(s0);
    r2 = func_00217488(r1);
    if (r2 == 0xD) return;
    r1 = func_00126040(s0);
    r2 = func_00217488(r1);
    if (r2 == 0xE) return;

tail4:
    if ((s1[10] & 4) == 0) {
        func_001226F0(s0, 0);
    } else {
        s1[12] = 0;
    }
    return;
}
