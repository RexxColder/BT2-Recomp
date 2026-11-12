#include "m2c_macros.h"

s32 fflush();                                       /* extern */

s32 lflush(void *arg0) {
    if ((M2C_FIELD(arg0, u16 *, 0xC) & 9) == 9) {
        return fflush();
    }
    return 0;
}
