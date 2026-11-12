#include "m2c_macros.h"

s32 _fwalk(s32 arg0, s32 (*arg1)(void *)) {
    s32 (*var_s4)(void *);
    s32 var_s0;
    s32 var_s3;
    void *var_s1;
    void *var_s2;

    var_s2 = arg0 + 0x1D8;
    var_s3 = 0;
    var_s4 = arg1;
    if (var_s2 != NULL) {
        do {
            var_s0 = M2C_FIELD(var_s2, s32 *, 4);
            var_s0 -= 1;
            var_s1 = M2C_FIELD(var_s2, void **, 8);
            if (var_s0 >= 0) {
                do {
                    if (M2C_FIELD(var_s1, s16 *, 0xC) != 0) {
                        var_s3 |= var_s4(var_s1);
                    }
                    var_s0 -= 1;
                    var_s1 += 0x58;
                } while (var_s0 >= 0);
            }
            var_s2 = M2C_FIELD(var_s2, void **, 0);
        } while (var_s2 != NULL);
    }
    return var_s3;
}
