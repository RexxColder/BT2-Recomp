#include "m2c_macros.h"

M2C_UNK func_001AF780(s32, void *);                 /* extern */
M2C_UNK func_001AFCA8();                            /* extern */

void func_001AF250(void *arg0) {
    func_001AFCA8(arg0);
    func_001AF780(M2C_FIELD(arg0, s32 *, 0x1C0), arg0);
}
