#include "common.h"

void func_00312650(u8 *arg0, u8 *arg1, u8 *arg2);
f32 sceVu0InnerProduct(u8 *arg0, u8 *arg1);
void sceVu0Normalize(u8 *arg0, u8 *arg1);
void EftTechEvt_RequestStop(s32 arg0);

s32 func_00127638(u8 *arg0, u8 *arg1) {
    f32 fr[12];
    u8 *sp;
    u8 *sp10;
    u8 *sp20;
    u8 *a1p;
    u8 *a3p;
    u32 t0;
    s32 s1;
    f32 f20;

    if (*(s32 *)(arg0 + 0x68) != 0) {
        return 1;
    }
    if (*(s32 *)(arg1 + 0x68) != 0) {
        return 2;
    }
    a1p = *(u8 **)(*(u8 **)(arg0 + 0x64) + 0x20);
    a3p = *(u8 **)(*(u8 **)(arg1 + 0x64) + 0x20);
    t0 = *(u32 *)(a1p + 8);
    if (t0 != *(u32 *)(a3p + 8)) {
        return 3;
    }
    if (!(t0 < 3U)) {
        return 3;
    }
    if (*(s32 *)(a1p + 0x30) & 0x100) {
        return 3;
    }
    if (*(s32 *)(a3p + 0x30) & 0x100) {
        return 3;
    }
    if (*(s16 *)(a1p + 0x34) >= 2) {
        return 3;
    }
    if (*(s16 *)(a3p + 0x34) >= 2) {
        return 3;
    }

    sp = (u8 *)fr;
    sp10 = sp + 0x10;
    sp20 = sp + 0x20;
    func_00312650(sp, arg0 + 0x20, arg0 + 0x30);
    func_00312650(sp10, arg1 + 0x20, arg1 + 0x30);
    func_00312650(sp20, arg1 + 0x30, arg0 + 0x30);

    if (0.0f < sceVu0InnerProduct(sp, sp20)) {
        if (sceVu0InnerProduct(sp, sp10) < 0.0f) {
            s1 = 4;
            EftTechEvt_RequestStop(0);
            EftTechEvt_RequestStop(1);
            return s1;
        }
    }

    s1 = 2;
    func_00312650(sp20, arg0 + 0x20, arg1 + 0x20);
    sceVu0Normalize(sp, sp);
    sceVu0Normalize(sp20, sp20);
    f20 = sceVu0InnerProduct(sp20, sp);
    func_00312650(sp20, arg1 + 0x20, arg0 + 0x20);
    sceVu0Normalize(sp10, sp10);
    sceVu0Normalize(sp20, sp20);
    if (!(f20 < sceVu0InnerProduct(sp20, sp10))) {
        s1 = 1;
    }
    return s1;
}
