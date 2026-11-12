#include "common.h"

s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
f32 func_00207F38(s32 arg0);
void func_00121050(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);
s32 func_00126040(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
f32 func_001216C0(s32 arg0);
void func_00122708(s32 arg0, s32 arg1);
void func_00122728(s32 arg0, s32 arg1);
f32 func_00121648(s32 arg0, s32 arg1);
void func_001226F0(s32 arg0, s32 arg1);
s32 func_00217488(s32 arg0);
extern f32 D_0038410C;

void func_001227D8(u8 *arg0) {
    u8 sp[16];
    u8 *s1;
    s32 p;
    s32 pos;
    s32 v0;
    f32 f0;
    f32 f1;
    f32 f20;

    p = (s32)arg0;
    s1 = arg0 + 0xFE0;
    func_00208DE8(*(s32 *)arg0, (s32)sp, 3);
    f20 = func_00207F38(*(s32 *)arg0);
    func_00121050(p, (s32)(arg0 + 0x1050), 10.0f, D_0038410C);
    if (func_00126058(p, 0, 2) == 0) {
        if (func_00126058(p, 0, 4) == 0) {
            if (*(f32 *)(sp + 4) < *(f32 *)(s1 + 0x40)) {
                pos = BtlChar_GetPos(func_00126040(p));
                if (0.0f < *(f32 *)((u8 *)pos + 0xC4)) {
                    if (*(f32 *)(s1 + 0x40) < *(f32 *)(sp + 4) + func_001216C0(p)) {
                        func_00122708(p, 0x800);
                    }
                }
                f0 = func_00121648((s32)(s1 + 0x60), (s32)sp);
                f1 = 150.0f;
            } else {
                pos = BtlChar_GetPos(func_00126040(p));
                f1 = 0.0f;
                f0 = *(f32 *)((u8 *)pos + 0xC4);
            }
            if (f1 < f0) {
                func_00122708(p, 0x800);
            }
        } else {
            func_00122708(p, 0x800);
        }
    } else if (func_00217488(func_00126040(p)) == 0x11) {
        func_00122728(p, 0x800);
    } else {
        v0 = *(s32 *)(s1 + 0x20) + 1;
        *(s32 *)(s1 + 0x20) = v0;
        if (v0 & 1) {
            func_00122728(p, 0x800);
        }
    }
    if (*(f32 *)(sp + 4) < (*(f32 *)(s1 + 0x40) + func_001216C0(p)) - f20) {
        if (func_00126058(p, 0, 2) != 0) {
            func_001226F0(p, 0);
        }
    }
    if (*(s32 *)(s1 + 0x28) & 4) {
        if (*(f32 *)(sp + 4) < *(f32 *)(s1 + 0x40)) {
            func_00217488(func_00126040(p));
        }
    }
}
