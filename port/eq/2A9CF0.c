#include "common.h"

void func_00259E48(void);
void func_00259E78(void);
void func_00259EA0(s32 arg0, s32 arg1, s32 arg2);
void func_00259EE0(void);
void func_00259F40(void);
void func_00259F68(void);
s32 func_00272E88(void);
void func_002A99B8(u8 *arg0);
void func_002ADCB0(void);
extern void *D_003876A0;
extern u8 D_003B2654[] __attribute__((section(".data")));

void func_002A9CF0(void) {
    u8 *s0;
    s32 v;
    s32 a1;

    s0 = D_003B2654 + 0x3B8;
    if ((*(s64 *)((u8 *)D_003876A0 + 0x4D8) & 0x100) == 0) {
        func_002A99B8(D_003876A0);
        func_002ADCB0();
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
                func_00259EE0();
                s0[1] = 0;
            }
        } else {
            if (s0[0] == 0) {
                func_00259E48();
                func_00259F68();
                s0[0] = 1;
            }
            if (s0[1] == 0) {
                v = func_00272E88();
                a1 = ((*(s32 *)(D_003B2654 + 0x3C) ^ 1) == 0) ? 2 : 1;
                if (v == 0x9B4) {
                    func_00259EA0(0x17, 1, v);
                } else if (v == 0x9B5) {
                    func_00259EA0(0x18, 1, v);
                } else {
                    func_00259EA0(*(s32 *)(D_003B2654 + 0x4C), a1, v);
                }
                s0[1] = 1;
            }
        }
    }
}
