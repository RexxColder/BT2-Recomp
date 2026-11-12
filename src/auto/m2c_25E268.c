#include "m2c_macros.h"

M2C_UNK func_0025CD70(s32);                         /* extern */
M2C_UNK func_0025D0A8(void *);                      /* extern */
M2C_UNK func_0025D190(void *);                      /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_0025E268(s32 arg0, void *arg1, s32 arg2) {
    func_0025CD70(M2C_FIELD(arg1, s32 *, 0xAF4));
    func_0025D0A8(arg1);
    memset(arg1, 0, 0x1520);
    M2C_FIELD(arg1, s32 *, 0) = arg0;
    M2C_FIELD(arg1, s32 *, 0x18) = arg2;
    func_0025D190(arg1);
}
