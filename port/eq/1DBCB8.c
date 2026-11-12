#include "common.h"

void Mtx_InverseRT(u8 *arg0, s32 arg1);
void func_00129B28(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129C50(u8 *arg0, u8 *arg1, u8 *arg2);
void func_001DBC10(u8 **arg0, s32 arg1, s32 arg2);
f32 func_001DBC80(u8 *arg0, u8 *arg1, u8 *arg2);
extern u8 *D_00387E9C;
extern s32 gBtlCamView;

void func_001DBCB8(void) {
    u8 buf[0xE0];
    u8 **list;
    u8 *s0;
    s32 s1;
    s32 s2;
    s32 i;
    f32 v;

    s1 = 0x1D;
    s2 = 0;
    Mtx_InverseRT(buf, gBtlCamView);
    s0 = *(u8 **)(D_00387E9C + 0x1410);
    list = (u8 **)(buf + 0x60);
    do {
        *(f32 *)(s0 + 0x88) = -1.0f;
        if (*(u8 *)(s0 + 0x90) != 0) {
            s2 += 1;
            func_00129C50(buf + 0x50, D_00387E9C + 0x1450, s0 + 0x10);
            func_00129B28(buf + 0x40, s0, buf + 0x50);
            v = func_001DBC80(buf + 0x20, buf + 0x30, buf + 0x40);
            *(f32 *)(s0 + 0x88) = v;
            *list = s0;
            list += 1;
        }
        s1 -= 1;
        s0 += 0xA0;
    } while (s1 >= 0);

    if (s2 >= 7) {
        func_001DBC10((u8 **)(buf + 0x60), 0, s2 - 1);
        i = 0;
        if (s2 > 0) {
            u8 **a0 = (u8 **)(buf + 0x60);
            s32 cond = 0 < 7;
            do {
                u8 *t;
                i += 1;
                t = *a0;
                a0 += 1;
                if (cond == 0) {
                    *(f32 *)(t + 0x5C) = *(f32 *)(t + 0x5C) * 1.5f;
                }
                cond = i < 7;
            } while (i < s2);
        }
    }
}
