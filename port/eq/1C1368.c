#include "common.h"

void func_001C1368(u8 *arg0, u8 *arg1) {
    s64 sp[74];
    u8 *var_a1;
    u8 *var_a0;
    u8 *var_v0;
    u8 *temp_a0;
    u8 *temp_v1;

    var_a1 = arg1;
    temp_v1 = arg1 + 0x240;
    var_v0 = (u8 *)sp;
    do {
        *(s64 *)(var_v0 + 0x00) = *(s64 *)(var_a1 + 0x00);
        *(s64 *)(var_v0 + 0x08) = *(s64 *)(var_a1 + 0x08);
        *(s64 *)(var_v0 + 0x10) = *(s64 *)(var_a1 + 0x10);
        *(s64 *)(var_v0 + 0x18) = *(s64 *)(var_a1 + 0x18);
        var_a1 += 0x20;
        var_v0 += 0x20;
    } while (var_a1 != temp_v1);
    *(s64 *)(var_v0 + 0x00) = *(s64 *)(var_a1 + 0x00);
    *(s64 *)(var_v0 + 0x08) = *(s64 *)(var_a1 + 0x08);
    if (arg0 != NULL) {
        temp_a0 = *(u8 **)(arg0 + 0x38);
        var_a0 = temp_a0 + 0x820;
        if (temp_a0 != NULL) {
            var_v0 = (u8 *)sp;
            do {
                *(s64 *)(var_a0 + 0x00) = *(s64 *)(var_v0 + 0x00);
                *(s64 *)(var_a0 + 0x08) = *(s64 *)(var_v0 + 0x08);
                *(s64 *)(var_a0 + 0x10) = *(s64 *)(var_v0 + 0x10);
                *(s64 *)(var_a0 + 0x18) = *(s64 *)(var_v0 + 0x18);
                var_v0 += 0x20;
                var_a0 += 0x20;
            } while (var_v0 != (u8 *)sp + 0x240);
            *(s64 *)(var_a0 + 0x00) = *(s64 *)(var_v0 + 0x00);
            *(s64 *)(var_a0 + 0x08) = *(s64 *)(var_v0 + 0x08);
        }
    }
}
