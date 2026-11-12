#include "m2c_macros.h"

M2C_UNK func_002FC550(M2C_UNK);                     /* extern */
s32 func_00307B90(s32 *);                           /* extern */
s32 sceCdGetError();                                /* extern */
s32 sceCdSeek(s32);                                 /* extern */
extern s32 D_00355374 __attribute__((section(".data")));

s32 func_002FC6A8(s32 arg0) {
    s32 temp_s0;
    s32 var_s1;
    s32 var_v0;

    var_v0 = func_00307B90(&D_00355374);
    var_s1 = 0;
    if (var_v0 != 0) {
        func_002FC550(0x9600);
        temp_s0 = sceCdSeek(arg0);
        func_002FC550(0x9601);
        if (temp_s0 == 0) {
            var_s1 = sceCdGetError();
        }
        D_00355374 = 0;
        var_v0 = var_s1;
    }
    return var_v0;
}
