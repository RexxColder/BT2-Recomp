#include "common.h"

void func_00129B28(void *a0, void *a1, void *a2);
extern f32 D_003854D0;
extern u8 *D_00387E9C;

void func_001D4A50(void *arg0) {
    u8 *s1;
    u8 *s0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f8;
    f32 var_f0;

    f32 f1;
    f32 f2;
    s32 run_state1;
    s32 var_v0;

    s1 = arg0;
    run_state1 = 0;
    if (s1[0x8C] == 0) {
        temp_f0 = *(f32 *)(s1 + 0x84) - 1.0f;
        *(f32 *)(s1 + 0x84) = temp_f0;
        if (temp_f0 <= 0.0f) {
            *(f32 *)(s1 + 0x84) = 0.0f;
            s1[0x91] = 1;
            s1[0x8C] = 1;
            run_state1 = 1;
        }
    } else if (s1[0x8C] == 1) {
        run_state1 = 1;
    }

    if (run_state1) {
        temp_f0_2 = *(f32 *)(s1 + 0x60);
        temp_f8 = *(f32 *)(s1 + 0x68);
        *(f32 *)(s1 + 0x10) = *(f32 *)(s1 + 0x10) + (*(f32 *)(s1 + 0x20) * temp_f0_2);
        *(f32 *)(s1 + 0x14) = *(f32 *)(s1 + 0x14) + (*(f32 *)(s1 + 0x24) * temp_f0_2);
        *(f32 *)(s1 + 0x18) = *(f32 *)(s1 + 0x18) + (*(f32 *)(s1 + 0x28) * temp_f0_2);
        *(f32 *)(s1 + 0x60) = temp_f0_2 + (temp_f0_2 * *(f32 *)(s1 + 0x64));
        if (*(f32 *)(s1 + 0x70) < temp_f8) {
            var_f0 = *(f32 *)(s1 + 0x6C) * D_003854D0;
        } else {
            var_f0 = *(f32 *)(s1 + 0x6C);
        }
        *(f32 *)(s1 + 0x68) = temp_f8 + var_f0;
        s0 = s1 + 0x30;
        *(f32 *)(s1 + 0x74) = *(f32 *)(s1 + 0x74) + *(f32 *)(s1 + 0x78);
        func_00129B28(s0, s0, s1 + 0x50);
        var_v0 = 2;
        do {
            f1 = *(f32 *)(s0 + 0x10);
            if (0.0f < *(f32 *)(s0 + 0x20)) {
                if (f1 <= *(f32 *)(s0 + 0x0)) {
                    *(f32 *)(s0 + 0x0) = f1;
                }
            } else {
                if (*(f32 *)(s0 + 0x0) <= f1) {
                    *(f32 *)(s0 + 0x0) = f1;
                }
            }
            var_v0 -= 1;
            s0 += 4;
        } while (var_v0 >= 0);
        f2 = *(f32 *)(s1 + 0x4C);
        if (f2 <= *(f32 *)(s1 + 0x3C)) {
            *(f32 *)(s1 + 0x3C) = f2;
            *(f32 *)(s1 + 0x5C) = (-f2) / *(f32 *)(s1 + 0x80);
        }
        *(f32 *)(s1 + 0x14) = *(f32 *)(s1 + 0x14) + *(f32 *)(s1 + 0x7C);
    }

    if ((s1[0x91] != 0) && (*(f32 *)(s1 + 0x3C) <= 0.0f)) {
        *(f32 *)(s1 + 0x3C) = 0.0f;
        s1[0x91] = 0;
        s1[0x90] = 0;
        *(s32 *)(D_00387E9C + 0x1428) = *(s32 *)(D_00387E9C + 0x1428) - 1;
    }
}
