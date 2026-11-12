#include "m2c_macros.h"

M2C_UNK func_001247B0(void *);                      /* extern */
M2C_UNK func_00125750(void *);                      /* extern */
M2C_UNK func_001259A0();                            /* extern */
s32 func_00125B98(s32);                             /* extern */
s32 func_00126040(void *);                          /* extern */

void func_00124768(void *arg0) {
    func_001259A0(arg0);
    func_00125750(arg0);
    func_001247B0(arg0);
    M2C_FIELD(arg0, s32 *, 0x11B0) = func_00125B98(func_00126040(arg0));
}
