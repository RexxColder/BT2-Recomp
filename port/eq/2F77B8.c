#include "common.h"

typedef void (*VFn1)(void *);
typedef void (*VFn3)(void *, s32, s32 *);
typedef void (*VFn4)(void *, s32, s32, s32 *);

s32 func_002F15A0(s32 a0);
s32 func_002F15B8(s32 a0);
s32 func_002F15E8(s32 a0);
void func_002F1480(s32 a0, s32 a1);
void func_002F1490(s32 a0, s32 a1);
void func_002F14A0(s32 a0, s32 a1);
void func_002F1350(s32 a0, s32 a1);
void func_002F1788(s32 a0);
void func_002EA050(void *a0);
extern u8 D_0037CFF0[] __attribute__((section(".data")));

void func_002F77B8(u8 *arg0) {
    s32 sp[4];
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 a1;
    u8 *s0;

    s2 = *(s32 *)(arg0 + 4);
    s0 = *(u8 **)(arg0 + 0x14);
    s3 = func_002F15A0(s2);
    s5 = func_002F15B8(s2);
    s4 = func_002F15E8(s2);
    if (((u32)arg0[2] - 2U < 2U) && (*(s8 *)(arg0 + 0x6C) == 0)) {
        func_002F1480(*(s32 *)(arg0 + 4), -1);
        return;
    }
    (*(VFn4 *)(*(u8 **)s0 + 0x18))(s0, 1, *(s32 *)(arg0 + 0x50), sp);
    if (sp[1] < *(s32 *)(arg0 + 0x50)) {
        func_002EA050(D_0037CFF0);
    }
    (*(VFn3 *)(*(u8 **)s0 + 0x20))(s0, 0, sp);
    func_002F1490(s2, 0);
    a1 = s4 - s3;
    *(s32 *)(arg0 + 0x90) = a1;
    func_002F1480(s2, a1);
    func_002F14A0(s2, s5);
    func_002F1350(s2, s3);
    if ((s8)arg0[2] == 2) {
        (*(VFn1 *)(*(u8 **)s0 + 0x14))(s0);
        (*(VFn4 *)(*(u8 **)s0 + 0x18))(s0, 1, s5, sp);
        (*(VFn3 *)(*(u8 **)s0 + 0x20))(s0, 0, sp);
    }
    func_002F1788(s2);
    *(s32 *)(arg0 + 0x4C) += 1;
}
