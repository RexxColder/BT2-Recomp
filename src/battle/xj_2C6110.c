#include "m2c_macros.h"

/* Sets the flag at +0xE48 to 1 unless the field at +0xE48+0x24 is 0x7FFFFFFF. */
void func_002C6110(void *arg0) {
    arg0 = (void *) ((s32) arg0 + 0xE48);
    if (M2C_FIELD(arg0, s32 *, 0x24) != 0x7FFFFFFF) {
        M2C_FIELD(arg0, s32 *, 0x0) = 1;
    }
}
