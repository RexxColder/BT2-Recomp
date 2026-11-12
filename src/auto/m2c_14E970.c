#include "m2c_macros.h"

void func_0014E970(void *arg0) {
    s32 *var_v1;
    s32 var_a2;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0);
    if ((M2C_FIELD(temp_a1, u8 *, 0) != 0) && (M2C_FIELD(temp_a1, u8 *, 1) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x54) = 0;
    }
    if ((M2C_FIELD(temp_a1, u8 *, 0x110) != 0) && (M2C_FIELD(temp_a1, u8 *, 0x111) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x174) = 0;
    }
    if ((M2C_FIELD(temp_a1, u8 *, 0x220) != 0) && (M2C_FIELD(temp_a1, u8 *, 0x221) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x2CC) = 0;
    }
    if ((M2C_FIELD(temp_a1, u8 *, 0x330) != 0) && (M2C_FIELD(temp_a1, u8 *, 0x331) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x3EC) = 0;
    }
    if ((M2C_FIELD(temp_a1, u8 *, 0x440) != 0) && (M2C_FIELD(temp_a1, u8 *, 0x441) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x60C) = 0;
    }
    if (M2C_FIELD(temp_a1, u8 *, 0x550) != 0) {
        var_a2 = 0;
        if (M2C_FIELD(temp_a1, u8 *, 0x551) != 0) {
            var_v1 = arg0 + 0x884;
            do {
                *var_v1 = 0;
                var_a2 += 1;
                var_v1 += 134;
            } while (var_a2 < (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x551));
        }
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x660) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x661) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x15CC) = 0;
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x770) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0x771) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x170C) = 0;
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xAA0) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xAA1) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x190C) = 0;
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xBB0) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xBB1) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x1A64) = 0;
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xCC0) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xCC1) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x1BBC) = 0;
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xDD0) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xDD1) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x1CF4) = 0;
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xEE0) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0), u8 *, 0xEE1) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x1E4C) = 0;
    }
}
