#include "m2c_macros.h"

s32 EftShot_TestBits(s32, s32);
void func_00153730(void *);
s32 func_00191728(s32);

// Shot effect update over the object at arg0+0x38: sets flag 0x200 in its word at +0 when EftShot_TestBits passes (and calls func_00153730); then tests four slots of 8 bytes at +0xAA0 with func_00191728, clearing the slot when it returns 0 and returning 1 when any slot is still live.
s32 func_001539D8(void *arg0) {
    s32 var_s1;
    s32 var_s2;
    s32 *temp_s0;
    s32 *var_s0;

    var_s2 = 0;
    temp_s0 = (s32 *) ((s32 **) arg0)[0xE];
    if (EftShot_TestBits(*(s32 *) (*(s32 **)((u8 *) temp_s0 + 0xA0)), 4) != 0) {
        func_00153730(arg0);
        *temp_s0 = *temp_s0 | 0x200;
    }
    var_s0 = (s32 *) ((u8 *) temp_s0 + 0xAA0);
    var_s1 = 4;
    do {
        if (func_00191728(var_s0[1]) != 0) {
            var_s2 = 1;
        } else {
            var_s0[1] = 0;
        }
        var_s1 -= 1;
        var_s0 += 2;
    } while (var_s1 >= 0);
    return var_s2;
}
