#include "common.h"

s32 func_0010B078(void);
s32 func_0010B080(void);
void func_00112B28(s32 arg0);
void func_00119E90(s32 arg0);
extern u8 *D_003876A0;

void Game_Main(void) {
    u8 *temp_s0;
    u8 *temp_s3;
    u8 *var_s0;
    s32 temp_s2;
    s32 var_s1;
    s32 var_v0;

    var_s1 = 0;
    temp_s0 = (u8 *)func_0010B080();
    temp_s3 = (u8 *)func_0010B078();
    temp_s2 = ((*(s64 *)(D_003876A0 + 0x4D8) & 2) != 0) ? 2 : 1;
    func_00112B28(*(s32 *)(temp_s0 + 0xC));
    if (temp_s2 != 0) {
        var_s0 = temp_s3 + 0x10C8;
        var_v0 = *(s32 *)(temp_s3 + 0x10C8);
        do {
            var_s0 += 0x38;
            if (var_v0 != 0) {
                func_00119E90(var_s1);
            }
            var_s1 += 1;
            if (var_s1 < temp_s2) {
                var_v0 = *(s32 *)var_s0;
            }
        } while (var_s1 < temp_s2);
    }
}
