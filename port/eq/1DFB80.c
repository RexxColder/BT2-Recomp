#include "common.h"

void func_001E1060(f32 farg0, u8 *arg1, u8 *arg2);
void func_001E1E28(u8 *arg0, u8 *arg1);

s32 func_001DFB80(u8 *arg0) {
    f32 temp_f0;
    s32 var_s3;
    s32 var_v0;
    u8 *temp_a1;
    u8 *var_a0;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;

    var_s0 = arg0;
    var_v0 = 0;
    if (*(u8 *)(var_s0 + 0x21DA) != 0) {
        var_s3 = 0;
        if (*(u8 *)(var_s0 + 0x21CC) != 0) {
            var_s1 = var_s0;
            do {
                var_s3 += 1;
                func_001E1060(*(f32 *)(var_s0 + 0x21C8), var_s1, var_s0);
                var_s1 += 0x1B0;
            } while (var_s3 < (s32)*(u8 *)(var_s0 + 0x21CC));
        }
        temp_f0 = *(f32 *)(var_s0 + 0x21C8) + 1.0f;
        *(f32 *)(var_s0 + 0x21C8) = temp_f0;
        if (*(f32 *)(var_s0 + 0x21C4) < temp_f0) {
            if (*(u8 *)(var_s0 + 0x21D9) == 0) {
                *(u8 *)(var_s0 + 0x21DA) = 0;
                return 0;
            }
            var_s3 = 0;
            if (*(u8 *)(var_s0 + 0x21CC) != 0) {
                var_s2 = var_s0 + 0x60;
                var_s1 = var_s0 + 0x10;
                var_a0 = var_s1;
                do {
                    var_s1 += 0x1B0;
                    temp_a1 = var_s2;
                    var_s2 += 0x1B0;
                    func_001E1E28(var_a0, temp_a1);
                    var_s3 += 1;
                    var_a0 = var_s1;
                } while (var_s3 < (s32)*(u8 *)(var_s0 + 0x21CC));
            }
            *(f32 *)(var_s0 + 0x21C8) = 0.0f;
        }
        var_v0 = 1;
        *(u8 *)(var_s0 + 0x21DA) = 1;
        return var_v0;
    }
    return var_v0;
}
