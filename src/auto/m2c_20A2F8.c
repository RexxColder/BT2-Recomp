#include "m2c_macros.h"

f32 func_0020A3B8(u32);                             /* extern */
s32 func_0020A758(u32);                             /* extern */
void *func_00211288();                              /* extern */
s32 func_00212560(void *);                          /* extern */
extern s32 D_00387930;

f32 func_0020A2F8(u32 arg0) {
    f32 *var_a0;
    f32 temp_f0;
    f32 var_f1;
    s32 temp_v0;
    s32 var_v0;
    void *temp_s1;

    if ((D_00387930 != 0) && (arg0 < 2U)) {
        temp_s1 = func_00211288(arg0);
        if (func_0020A758(arg0) == 0) {
            return func_0020A3B8(arg0);
        }
        temp_v0 = func_00212560(temp_s1);
        var_f1 = M2C_FIELD(M2C_FIELD(temp_s1, void **, 0x1530), f32 *, 0xBE0);
        if (temp_v0 > 0) {
            var_a0 = temp_s1 + 0xA94;
            var_v0 = temp_v0;
            do {
                temp_f0 = *var_a0;
                var_a0 += 1;
                var_v0 -= 1;
                var_f1 += temp_f0 + 1.0f;
            } while (var_v0 != 0);
        }
        return var_f1;
    }
    return 0.0f;
}
