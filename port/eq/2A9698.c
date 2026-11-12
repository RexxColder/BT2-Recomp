#include "common.h"

void func_002A8EF0(u8 *arg0, u8 *arg1);
void func_002A8FD0(u8 *arg0);
void func_002A9278(u8 *arg0);
extern u8 *D_003876A0;
extern u8 *D_00387A40;

void func_002A9698(void) {
    s32 var_s1;
    s32 var_s2;
    u8 *var_v0;
    u8 *temp_s0;

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        var_s2 = 0;
        if (*(s32 *)(D_00387A40 + 0xC) > 0) {
            var_s1 = 0;
            var_v0 = *(u8 **)(D_00387A40 + 8);
loop_3:
            temp_s0 = var_v0 + var_s1;
            var_s1 += 0x1520;
            if (*(s32 *)(temp_s0 + 0xC) != 0) {
                func_002A8EF0(temp_s0, D_00387A40);
                func_002A8FD0(temp_s0);
                func_002A9278(temp_s0);
            }
            var_s2 += 1;
            if (var_s2 < *(s32 *)(D_00387A40 + 0xC)) {
                var_v0 = *(u8 **)(D_00387A40 + 8);
                goto loop_3;
            }
        }
    }
}
