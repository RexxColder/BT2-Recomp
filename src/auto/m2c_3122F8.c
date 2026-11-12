#include "m2c_macros.h"

M2C_UNK WaitDma();                                  /* extern */

s32 sceDmaSync(u32 *arg0, s32 arg1) {
    if (arg1 == 1) {
        return ((u32) *arg0 >> 8) & 1;
    }
    WaitDma();
    return 0;
}
