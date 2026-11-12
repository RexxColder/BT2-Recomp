#include "common.h"

s32 func_0020C8E8(void);
s32 func_0020C918(void);
void func_00259E48(void);
void func_00259E78(void);
void func_00259EA0(s32 arg0, s32 arg1);
void func_00259EE0(s32 arg0);
void func_00259F20(s32 arg0);
void func_00259F40(void);
void func_002ADCB0(void);
extern u8 *D_003876A0;
extern u8 D_003B2A0C[] __attribute__((section(".data")));

void func_002AD6E8(void) {
    u8 *s0;
    s32 v;
    s32 r;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    func_002ADCB0();
    s0 = D_003B2A0C;
    if (s0[4] != 0) {
        if (s0[0] != 0) {
            func_00259E78();
            s0[0] = 0;
        }
        if (s0[2] != 0) {
            func_00259F40();
            s0[2] = 0;
        }
        if (s0[1] != 0) {
            func_00259EE0(0);
            s0[1] = 0;
        }
        if (s0[3] != 0) {
            s0[3] = 0;
        }
        return;
    }
    if (s0[0] == 0) {
        func_00259E48();
        s0[0] = 1;
    }
    if (s0[3] == 0) {
        s0[3] = 1;
    }
    v = func_0020C8E8();
    *(s32 *)(s0 + 8) = v;
    if (v != *(s32 *)(s0 + 0x10)) {
        if (v != -1) {
            if (s0[2] == 0) {
                func_00259F20(0);
                s0[2] = 1;
            }
        } else if (s0[2] == 1) {
            func_00259F40();
            s0[2] = 0;
        }
        *(s32 *)(s0 + 0x10) = *(s32 *)(s0 + 8);
    }
    r = func_0020C918();
    *(s32 *)(s0 + 0xC) = r;
    if (r != *(s32 *)(s0 + 0x14)) {
        if (r != -1) {
            if (s0[1] == 0) {
                func_00259EA0(r, 0);
                s0[1] = 1;
            } else {
                func_00259EA0(r, 0);
            }
        } else if (s0[1] == 1) {
            func_00259EE0(r);
            s0[1] = 0;
        }
        *(s32 *)(s0 + 0x14) = *(s32 *)(s0 + 0xC);
    }
}
