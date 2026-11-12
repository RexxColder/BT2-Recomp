#include "common.h"

void func_0028BB60(s32 arg0);
extern u8 *D_00387A44;

void func_00269708(void) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = 6;
    do {
        var_s1 -= 1;
        func_0028BB60(*(s32 *)(D_00387A44 + var_s0));
        func_0028BB60(*(s32 *)(D_00387A44 + var_s0 + 4));
        var_s0 += 0x20C0;
    } while (var_s1 >= 0);
    func_0028BB60((s32)D_00387A44);
    D_00387A44 = NULL;
}
