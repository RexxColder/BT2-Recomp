#include "common.h"

s64 EftVram_AddTex(u8 *arg0, s32 arg1, s32 arg2);
void func_00144200(void *arg0, void *arg1);
void func_00144258(void *arg0, void *arg1);
extern u8 *gEftBound;

void func_00145760(u8 *arg0) {
    s32 var_s2;
    u8 *temp_s1;
    u8 *temp_s0;
    u8 *var_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    func_00144200(temp_s0, temp_s0);
    func_00144258(temp_s0, temp_s0);
    if (*gEftBound == 0) {
        temp_s1 = gEftBound + 0x10;
        if (temp_s0[0x30] != 0 || temp_s0[0x840] != 0) {
            var_s2 = 0;
            if (*(s32 *)(temp_s1 + 0x200) > 0) {
                var_s0 = temp_s1;
                do {
                    var_s2 += 1;
                    *(s64 *)var_s0 = EftVram_AddTex(var_s0, 1, 0);
                    var_s0 += 0x10;
                } while (var_s2 < *(s32 *)(temp_s1 + 0x200));
            }
            *gEftBound = 1;
        }
    }
}
