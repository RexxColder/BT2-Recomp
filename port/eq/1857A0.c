#include "common.h"

void Mtx_StoreIdentity(s32 arg0);
void Vu0Screen_StoreMtx(s32 arg0);
s32 func_00126598(s32 arg0);
void func_001862D0(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);
void func_001866A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2, s32 t3);

void func_001857A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    s32 mtx[16];
    s32 mtx2[16];
    f32 vb[8];
    s32 s0;
    s32 s1;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 idx;
    s32 base;
    f32 f1;

    s4 = 0;
    if ((*(s32 *)(arg0 + 0x19C) & 0x200) != 0) {
        s4 = 1;
        if (func_00126598(*(s32 *)(arg0 + 0x94)) == 0) {
            return;
        }
    }

    Vu0Screen_StoreMtx((s32)mtx);
    s5 = *(s32 *)arg0 + ((*(u8 *)(arg0 + 0x198)) * 0x10);
    Mtx_StoreIdentity((s32)mtx2);
    s0 = *(s32 *)(arg0 + 0x1A4);
    s1 = arg0 + 8;
    s6 = arg3 & 0xFF;
    s7 = arg2 & 0xFF;

    if (s0 != 0) {
        do {
            if (s7 == 0) {
                func_001862D0(s0, (s32)mtx2, arg0 + 0x40, *(f32 *)(arg0 + 0x80), farg0, farg1);
            }
            f1 = *(f32 *)(s0 + 0xA8);
            idx = *(u8 *)(s0 + 0xBD);
            base = s1 + idx * 0x10;
            if (f1 < 0.0f && s6 != 0) {
                vb[0] = *(f32 *)(base + 0x90);
                vb[1] = *(f32 *)(base + 0x94);
                vb[2] = *(f32 *)(base + 0x90);
                vb[3] = *(f32 *)(base + 0x9C);
                vb[4] = *(f32 *)(base + 0x98);
                vb[5] = *(f32 *)(base + 0x94);
                vb[6] = *(f32 *)(base + 0x98);
                vb[7] = *(f32 *)(base + 0x9C);
            } else {
                vb[0] = *(f32 *)(base + 0x98);
                vb[1] = *(f32 *)(base + 0x94);
                vb[2] = *(f32 *)(base + 0x98);
                vb[3] = *(f32 *)(base + 0x9C);
                vb[4] = *(f32 *)(base + 0x90);
                vb[5] = *(f32 *)(base + 0x94);
                vb[6] = *(f32 *)(base + 0x90);
                vb[7] = *(f32 *)(base + 0x9C);
            }
            func_001866A8(s0 + 0x40, (s32)mtx, (s32)&vb[0], (s32)&vb[4], s0 + 0x20, arg1, s4, s5);
            s0 = *(s32 *)(s0 + 0xC0);
        } while (s0 != 0);
    }
}
