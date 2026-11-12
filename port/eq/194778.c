#include "common.h"

void func_001940F0(f32 farg0, f32 farg1, void *arg0, void *arg1, void *arg2, s64 arg3);

void func_00194778(void *arg0) {
    u8 *temp_v0;
    u8 *var_s0;

    var_s0 = *(u8 **)arg0;
    if (var_s0 != NULL) {
        do {
            func_001940F0(*(f32 *)(var_s0 + 0x3C), *(f32 *)(var_s0 + 0x40), arg0, var_s0, var_s0 + 0x110,
                          *(s64 *)((u8 *)arg0 + 0x1E8));
            temp_v0 = *(u8 **)(var_s0 + 0x140);
            var_s0 = temp_v0;
        } while (temp_v0 != NULL);
    }
}
