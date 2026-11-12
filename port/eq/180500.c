#include "common.h"

void func_00180500(void **arg0, f32 farg0) {
    s32 var_v1;
    void **var_a0;
    void *temp_v0;

    var_a0 = arg0;
    var_v1 = 0x1D;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        if (temp_v0 != NULL) {
            *(f32 *)((u8 *)*(void **)((u8 *)temp_v0 + 0x38) + 0x28) = farg0;
        }
        var_v1 -= 1;
    } while (var_v1 >= 0);
}
