#include "m2c_macros.h"

/* Copies the fields at +0x3EC and +0x3F4 of the object to the two out pointers, when given. */
void func_002DE370(void *arg0, s32 *arg1, s32 *arg2) {
    arg0 = (u8 *) arg0 + 0x3EC;
    if (arg1 != NULL) {
        *arg1 = M2C_FIELD(arg0, s32 *, 0);
    }
    if (arg2 != NULL) {
        *arg2 = M2C_FIELD(arg0, s32 *, 8);
    }
}
