#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0016F2E8(u8 *arg0);
void func_0016F438(u8 *arg0);
void func_00191688(s32 arg0);
s32 func_00191728(s32 arg0);

s32 func_0016F7B0(u8 *arg0) {
    u8 *var_s0;
    u8 *temp_s0;
    s32 var_s1;
    s32 var_s4;
    u8 *var_s2;
    u8 *var_s3;

    var_s3 = arg0;
    var_s4 = 0;
    var_s2 = *(u8 **)(var_s3 + 0x38);
    temp_s0 = *(u8 **)(var_s2 + 0xB0);
    if (EftShot_TestBits(*(s32 *)temp_s0, 0x40) != 0) {
        func_0016F2E8(var_s3);
    }
    if (EftShot_TestBits(*(s32 *)temp_s0, 4) != 0) {
        *(s32 *)(var_s2 + 0x10) = *(s32 *)(var_s2 + 0x10) + 1;
        if (!(*(s32 *)(var_s2 + 0) & 0x200)) {
            var_s0 = var_s2 + 0xAB0;
            var_s1 = 0x18;
            do {
                if (*(s32 *)(var_s0 + 0) & 1) {
                    func_00191688(*(s32 *)(var_s0 + 0x260));
                }
                var_s1 -= 1;
                var_s0 += 0x270;
            } while (var_s1 >= 0);
            *(s32 *)(var_s2 + 0) = *(s32 *)(var_s2 + 0) | 0x200;
        }
        func_0016F438(var_s3);
    }
    var_s0 = var_s2 + 0xAB0;
    var_s1 = 0x18;
    do {
        if (func_00191728(*(s32 *)(var_s0 + 0x260)) == 0) {
            *(s32 *)(var_s0 + 0x260) = 0;
        } else {
            var_s4 = 1;
        }
        var_s1 -= 1;
        var_s0 += 0x270;
    } while (var_s1 >= 0);
    return var_s4;
}
