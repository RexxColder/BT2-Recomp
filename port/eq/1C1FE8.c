#include "common.h"

void func_001EBD08(s32 arg0, s32 arg1);
extern u8 *D_00387898;

void func_001C1FE8(void *arg0) {
    u8 *a;
    s32 temp_s4;
    s32 var_a0;
    s32 var_s1;
    u8 *var_s2;
    u8 *var_s3;
    u8 *var_v1;
    u8 *temp_v0;

    a = (u8 *)arg0;
    var_s1 = *(u8 *)(a + 0xD0) - 1;
    temp_s4 = *(s32 *)(*(u8 **)(D_00387898 + 4) + 0x38);
    if (var_s1 >= 0) {
        temp_v0 = a + var_s1 * 4;
        var_s3 = temp_v0;
        var_s2 = temp_v0 + 0x30;
        do {
            func_001EBD08(temp_s4 + 0x20D48, *(s32 *)var_s2);
            var_a0 = var_s1;
            if (var_s1 < (s32)*(u8 *)(a + 0xD0) - 1) {
                var_v1 = var_s3 + 0x30;
                do {
                    var_a0 += 1;
                    *(s32 *)var_v1 = *(s32 *)(var_v1 + 4);
                    var_v1 += 4;
                } while (var_a0 < (s32)*(u8 *)(a + 0xD0) - 1);
            }
            var_s1 -= 1;
            var_s2 -= 4;
            *(s32 *)(a + var_a0 * 4 + 0x30) = 0;
            var_s3 -= 4;
            *(u8 *)(a + 0xD0) = (u8)(*(u8 *)(a + 0xD0) + 0xFF);
        } while (var_s1 >= 0);
    }
    func_001EBD08(temp_s4 + 0xF400, (s32)a);
}
