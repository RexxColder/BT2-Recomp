#include "common.h"

void func_00312FB0(s32 arg0, s32 arg1, f32 farg0);
void func_001E0EA0(s32 arg0);
void func_001E1E28(s32 arg0, s32 arg1);

void func_001E0A70(s32 arg0, f32 farg0) {
    s32 var_s2;
    u8 *var_s0;
    u8 *var_a0;
    u8 *p;
    u8 *a0v;
    u8 *a1v;

    var_s2 = 0;
    var_s0 = (u8 *)arg0 + 0x10;
    if (*(s32 *)((u8 *)arg0 + 0x1B0) > 0) {
        var_a0 = var_s0 + 0x110;
        do {
            var_s2 += 1;
            func_00312FB0((s32)var_a0, (s32)var_a0, farg0);
            p = var_s0 + 0x120;
            func_00312FB0((s32)p, (s32)p, farg0);
            p = var_s0 + 0x130;
            func_00312FB0((s32)p, (s32)p, farg0);
            p = var_s0 + 0x140;
            func_00312FB0((s32)p, (s32)p, farg0);
            func_001E0EA0((s32)var_s0);
            a0v = var_s0 + 0x10;
            a1v = var_s0 + 0x60;
            var_s0 += 0x1B0;
            func_001E1E28((s32)a0v, (s32)a1v);
            var_a0 = var_s0 + 0x110;
        } while (var_s2 < *(s32 *)((u8 *)arg0 + 0x1B0));
    }
}
